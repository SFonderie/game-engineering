#ifndef BALL_H
#define BALL_H

#include "EllipseObject.h"
#include "Player.h"
#include "Sounds.h"
#include "Random.h"

/// <summary>
/// Ball object. Handles collision and speeding itself up.
/// </summary>
class Ball : public EllipseObject
{

private:

	/// <summary>
	/// Used to manage collision with the player.
	/// </summary>
	const Player* player = nullptr;

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
	/// Has the ball launched yet?
	/// </summary>
	bool launched = false;

public:

	/// <summary>
	/// Creates the ball at the middle of the screen.
	/// </summary>
	Ball(Object* parent, const Player* player, Sounds& sounds, int width, int height, float speed);

	/// <summary>
	/// Updates the ball by moving it, and then checks collisions.
	/// </summary>
	virtual void Update(const sf::Time& delta);

	/// <summary>
	/// Handles ball bouncing.
	/// </summary>
	virtual void OnCollision(const sf::Time& delta, const Object* object, float time, const sf::Vector2f& normal);

	/// <summary>
	/// Resets the ball to the center of the screen.
	/// </summary>
	void Reset();

	/// <summary>
	/// Launches the ball in a random direction.
	/// </summary>
	void Launch(const sf::Vector2f& mouse);

	/// <summary>
	/// Returns whether the ball has launched.
	/// </summary>
	bool IsLaunched() const;

	/// <summary>
	/// Returns whether the ball is out of bounds.
	/// </summary>
	bool IsInRange() const;
};

#endif
