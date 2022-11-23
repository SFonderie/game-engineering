#include "Player.h"

Player::Player(Object* parent, int width, int height, float speed) : RectangleObject(parent)
{
	this->width = width;
	this->height = height;
	this->speed = speed;

	// Paddles are entities.
	this->SetEntity(true);
}

void Player::Update(const sf::Time& delta)
{
	// Handle the player's movement.
	float vertical = 0;

	// I needed to use booleans because key events are weird.
	if (this->upward) vertical += -this->speed;
	if (this->downward) vertical += this->speed;

	// Set the speed each frame.
	this->SetVelocity(sf::Vector2f(0, vertical));

	// Now do the regular update.
	RectangleObject::Update(delta);

	// Get the player's current position.
	sf::Vector2f position = this->GetPosition();

	// Define some bounds using screen space.
	// The player can touch the top and bottom.
	int upper = this->height / 16 * 2;
	int lower = this->height / 16 * 14;

	// Actually implement the bounded movement.
	if (position.y <= upper) position.y = (float)upper;
	if (position.y >= lower) position.y = (float)lower;

	// And locked!
	this->SetPosition(position);
}

void Player::Reset()
{
	// Automatically drops the player in the middle of the screen.
	this->SetPosition(sf::Vector2f((float)(this->width / 10), (float)(this->height / 2)));
	this->SetScale(sf::Vector2f((float)(this->width / 50), (float)(this->height / 8)));
}

void Player::MoveUp(bool press)
{
	this->upward = press;
}

void Player::MoveDown(bool press)
{
	this->downward = press;
}
