#ifndef BRICK_H
#define BRICK_H

#include "RectangleObject.h"

/// <summary>
/// Defines a brick object.
/// </summary>
class Brick : public RectangleObject
{

private:

	/// <summary>
	/// Health of the brick.
	/// </summary>
	int health = 0;

	/// <summary>
	/// Damage taken by the brick.
	/// </summary>
	int damage = 0;

public:

	/// <summary>
	/// Create a brick with the given health.
	/// </summary>
	Brick(Object* parent, int health);

	/// <summary>
	/// Reduces brick health whenever something collides with the brick.
	/// </summary>
	virtual void OnCollision(const sf::Time& delta, const Object* object, float time, const sf::Vector2f& normal);

	/// <summary>
	/// Returns whether the player is alive.
	/// </summary>
	bool IsAlive() const;

	/// <summary>
	/// Updates the brick color using health.
	/// </summary>
	void UpdateColor();

	/// <summary>
	/// Resets the brick for the level.
	/// </summary>
	void Reset();
};

#endif
