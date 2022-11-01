#ifndef EFFECT_H
#define EFFECT_H

#include "IEffect.h"

// Again, adding a template here avoids dynamic casts.
template <class Particle = Particle>
/// <summary>
/// Abstract base class for managing a particle effect.
/// </summary>
class Effect : public IEffect
{

private:

	/// <summary>
	/// Actual particle pool array.
	/// </summary>
	Particle* particles;

	/// <summary>
	/// Position of the particle origin.
	/// </summary>
	sf::Vector2f origin;

protected:

	/// <summary>
	/// Particle pool array length.
	/// </summary>
	int capacity;

public:

	/// <summary>
	/// Creates the effect.
	/// </summary>
	Effect();

	// Unloads the particle pool.
	virtual ~Effect();

	/// <summary>
	/// Invoked once to allocate the particle array.
	/// </summary>
	virtual Particle* MakeParticles(int capacity) = 0;

	/// <summary>
	/// Invoked to actually reset the given particles.
	/// </summary>
	virtual void EmitParticles(Particle* const particles) = 0;

	/// <summary>
	/// Starts the effect emission at the given origin.
	/// </summary>
	/// <param name="origin">Particle effect origin point in screen space.</param>
	virtual void Start(const sf::Vector2f& origin);

	/// <summary>
	/// Increments all particles.
	/// </summary>
	virtual void Update(const sf::Time& delta);

	/// <summary>
	/// Renders all particles.
	/// </summary>
	virtual void Render(sf::RenderWindow& canvas) const;

	/// <summary>
	/// Returns the particle effect origin position in screen space.
	/// </summary>
	virtual const sf::Vector2f& GetOrigin() const;

	/// <summary>
	/// Checks if all particles have expired.
	/// </summary>
	virtual bool IsAlive() const;
};

// TEMPLATE CPP INCLUDE (YUCK)
#include "Effect.cpp"

#endif
