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
	float horizontal = 0;

	// I needed to use booleans because key events are weird.
	if (this->leftward) horizontal += -this->speed;
	if (this->rightward) horizontal += this->speed;

	// Set the speed each frame.
	this->SetVelocity(sf::Vector2f(horizontal, 0));

	// Now do the regular update.
	RectangleObject::Update(delta);

	// Get the player's current position.
	sf::Vector2f position = this->GetPosition();

	// Define some bounds using screen space.
	// The player can touch the top and bottom.
	int left = this->width / 16 * 2;
	int right = this->width / 16 * 14;

	// Actually implement the bounded movement.
	if (position.x <= left) position.x = (float) left;
	if (position.x >= right) position.x = (float) right;

	// And locked!
	this->SetPosition(position);
}

void Player::Reset()
{
	// Automatically drops the player in the middle of the bottom of the screen
	this->SetPosition(sf::Vector2f((float) (this->width / 2), (float) (this->height / 10 * 9)));
	this->SetScale(sf::Vector2f((float) (this->width / 8), (float) (this->height / 40)));
}

void Player::MoveLeft(bool press)
{
	this->leftward = press;
}

void Player::MoveRight(bool press)
{
	this->rightward = press;
}
