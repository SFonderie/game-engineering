#ifndef I_EFFECT_H
#define I_EFFECT_H

#include "Particle.h"

/// <summary>
/// Interface for managing a particle effect.
/// </summary>
class IEffect
{

public:

	/// <summary>
	/// Select a random base color.
	/// </summary>
	static sf::Color PickColor();

	/// <summary>
	/// Returns a standard gravity value.
	/// </summary>
	static sf::Vector2f GetGravity();

	/// <summary>
	/// Starts the effect emission at the given origin.
	/// </summary>
	/// <param name="origin">Particle effect origin point in screen space.</param>
	virtual void Start(const sf::Vector2f& origin) = 0;

	/// <summary>
	/// Increments all particles.
	/// </summary>
	virtual void Update(const sf::Time& delta) = 0;

	/// <summary>
	/// Renders all particles.
	/// </summary>
	virtual void Render(sf::RenderWindow& canvas) const = 0;

	/// <summary>
	/// Returns the particle effect origin position in screen space.
	/// </summary>
	virtual const sf::Vector2f& GetOrigin() const = 0;

	/// <summary>
	/// Checks if all particles have expired.
	/// </summary>
	virtual bool IsAlive() const = 0;
};

#endif
