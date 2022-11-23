#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "Ball.h"

/// <summary>
/// Enemy paddle class.
/// </summary>
class Enemy : public Player
{

private:

	/// <summary>
	/// Enemy tracks this ball.
	/// </summary>
	Ball* ball = nullptr;

public:

	/// <summary>
	/// Creates the enemy on the right side of the screen.
	/// </summary>
	Enemy(Object* parent, Ball* ball, int width, int height, float speed);

	/// <summary>
	/// Used to track the ball.
	/// </summary>
	virtual void Update(const sf::Time& delta);

	/// <summary>
	/// Resets the enemy's position.
	/// </summary>
	virtual void Reset();
};

#endif
