#ifndef PLAYER_H
#define PLAYER_H

#include "RectangleObject.h"

/// <summary>
/// Player paddle class.
/// </summary>
class Player : public RectangleObject
{

protected:

	/// <summary>
	/// Width of the screen.
	/// </summary>
	int width;

	/// <summary>
	/// Height of the screen.
	/// </summary>
	int height;

	/// <summary>
	/// Player maximum speed.
	/// </summary>
	float speed;

	/// <summary>
	/// Should the player move up?
	/// </summary>
	bool leftward = false;

	/// <summary>
	/// Should the player move down?
	/// </summary>
	bool rightward = false;

	/// <summary>
	/// Player score.
	/// </summary>
	int score = 0;

public:

	/// <summary>
	/// Creates the player on the left side of the screen.
	/// </summary>
	Player(Object* parent, int width, int height, float speed);

	/// <summary>
	/// Invoked to ensure the player's position remains bounded.
	/// </summary>
	virtual void Update(const sf::Time& delta);

	/// <summary>
	/// Resets the player's position.
	/// </summary>
	virtual void Reset();

	/// <summary>
	/// Causes the player to start moving left.
	/// </summary>
	void MoveLeft(bool press);

	/// <summary>
	/// Causes the player to start moving right.
	/// </summary>
	void MoveRight(bool press);
};

#endif
