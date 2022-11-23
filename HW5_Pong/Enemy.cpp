#include "Enemy.h"

Enemy::Enemy(Object* parent, Ball* ball, int width, int height, float speed) : Player(parent, width, height, speed), ball(ball)
{
	// Default constructor doesn't do anything!
}

void Enemy::Update(const sf::Time& delta)
{
	// Parent update. Always!
	Player::Update(delta);

	sf::Vector2f difference = this->ball->GetPosition() - this->GetPosition();

	// If the ball is lower on the screen than us.
	if (difference.y > 0)
	{
		this->MoveDown(true);
		this->MoveUp(false);
	}
	else
	{
		this->MoveUp(true);
		this->MoveDown(false);
	}
}

void Enemy::Reset()
{
	// Automatically drops the enemy in the middle of the screen.
	this->SetPosition(sf::Vector2f((float)(this->width / 10 * 9), (float)(this->height / 2)));
	this->SetScale(sf::Vector2f((float)(this->width / 50), (float)(this->height / 8)));
}
