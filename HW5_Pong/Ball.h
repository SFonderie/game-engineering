#ifndef BALL_H
#define BALL_H

#include "EllipseObject.h"
#include "Sounds.h"
#include "Random.h"

/// <summary>
/// Ball object. Handles collision and speeding itself up.
/// </summary>
class Ball : public EllipseObject
{

private:

	/// <summary>
	/// Game sounds object.
	/// </summary>
	Sounds& sounds;

	/// <summary>
	/// Width of the screen.
	/// </summary>
	int width;

	/// <summary>
	/// Height of the screen.
	/// </summary>
	int height;

	/// <summary>
	/// Initial speed of the ball.
	/// </summary>
	float speed;

	/// <summary>
	/// Tracks the ball's lifespan.
	/// </summary>
	float life = 0;

	/// <summary>
	/// Has the ball launched yet?
	/// </summary>
	bool launched = false;

public:

	/// <summary>
	/// Creates the ball at the middle of the screen.
	/// </summary>
	Ball(Object* parent, Sounds& sounds, int width, int height, float speed);

	/// <summary>
	/// Updates the ball by moving it, and then checks collisions.
	/// </summary>
	virtual void Update(const sf::Time& delta);

	/// <summary>
	/// Resets the ball to the center of the screen.
	/// </summary>
	void Reset();

	/// <summary>
	/// Launches the ball in a random direction.
	/// </summary>
	void Launch();

	/// <summary>
	/// Returns the ball's current lifespan.
	/// </summary>
	float GetTime() const;

private:

	/// <summary>
	/// Checks for collision with the given object.
	/// Returns the collision result and outputs the time until collision and the collision plane.
	/// </summary>
	bool CheckCollision(const Object* object, float& OutTime, sf::Vector2f& OutNormal);
};

#endif
