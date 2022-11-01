#ifndef EFFECT_LOOP_H
#define EFFECT_LOOP_H

#include "Effect.h"

template <class Particle>
class EffectLooping : public Effect<Particle>
{

private:

	/// <summary>
	/// 
	/// </summary>
	Particle* particles;

protected:

	/// <summary>
	/// Duration of a particle cycle in seconds.
	/// </summary>
	float lifespan;

	/// <summary>
	/// Time in seconds between each emission.
	/// </summary>
	float delay;

	/// <summary>
	/// Number of particles released per emission.
	/// </summary>
	int emission;

	/// <summary>
	/// Current emission timer.
	/// </summary>
	float time;

	/// <summary>
	/// Current emission index.
	/// </summary>
	int index;

public:

	EffectLooping(float lifespan, float delay, int emission);

	/// <summary>
	/// Invoked to emit a set of particles.
	/// </summary>
	virtual void Emit(Particle* const particles, int count) = 0;

	/// <summary>
	/// Invoked to actually reset the given particles.
	/// </summary>
	virtual void EmitParticles(Particle* const particles);

	/// <summary>
	/// Increments all particles and handles emission.
	/// </summary>
	virtual void Update(const sf::Time& delta);
};

#include "EffectLooping.cpp"

#endif
