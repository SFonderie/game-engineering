#ifndef EFFECT_SPARKLER_H
#define EFFECT_SPARKLER_H

#include "EffectLooping.h"
#include "ParticlePolygon.h"

/// <summary>
/// Creates a continuous sparkler effect.
/// </summary>
class EffectSparkler : public EffectLooping<ParticlePolygon>
{

private:

	sf::Color color;

public:

	EffectSparkler(float lifespan, float delay, int emission);

	/// <summary>
	/// Invoked once to allocate the particle array.
	/// </summary>
	virtual ParticlePolygon* MakeParticles(int capacity);

	/// <summary>
	/// Invoked to emit a set of particles.
	/// </summary>
	virtual void Emit(ParticlePolygon* const particles, int count);

	/// <summary>
	/// Starts the effect emission at the given origin.
	/// </summary>
	virtual void Start(const sf::Vector2f& origin);
};

#endif
