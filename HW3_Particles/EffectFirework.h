#ifndef EFFECT_FIREWORK_H
#define EFFECT_FIREWORK_H

#include "Effect.h"
#include "ParticleCircle.h"

/// <summary>
/// Creates a generic peony-style firework explosion.
/// </summary>
class EffectFirework : public Effect<ParticleCircle>
{

private:

	/// <summary>
	/// Number of layers in the explosion.
	/// </summary>
	int layers;

	/// <summary>
	/// Base particle count per layer.
	/// </summary>
	int density;

	/// <summary>
	/// Particle growth per layer. Doubled.
	/// </summary>
	int growth;

public:

	/// <summary>
	/// Initialize the fireworks with the given layer count, density, and growth factor.
	/// </summary>
	EffectFirework(int layers, int density, int growth);

	/// <summary>
	/// Creates the firework particles.
	/// </summary>
	virtual ParticleCircle* MakeParticles(int capacity);

	/// <summary>
	/// Actually positions the firework particles.
	/// </summary>
	virtual void EmitParticles(ParticleCircle* const particles);

	/// <summary>
	/// Starts the effect emission at the given origin.
	/// </summary>
	/// <param name="origin">Particle effect origin point in screen space.</param>
	virtual void Start(const sf::Vector2f& origin);

	/// <summary>
	/// Calculates the firework particle count.
	/// </summary>
	int GetCount() const;
};

#endif
