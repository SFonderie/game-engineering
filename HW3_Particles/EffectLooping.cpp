#ifndef EFFECT_LOOPING_CPP
#define EFFECT_LOOPING_CPP

#include "EffectLooping.h"

template <class Particle>
EffectLooping<Particle>::EffectLooping(float lifespan, float delay, int emission)
{
	this->particles = nullptr;
	this->lifespan = lifespan;
	this->delay = delay;
	this->emission = emission;
	this->time = 0;
	this->index = 0;

	// Calculate a capacity based on time and the emission count. Overallocate.
	this->capacity = ((int)(this->lifespan / this->delay) + 1) * this->emission;
}

template <class Particle>
void EffectLooping<Particle>::EmitParticles(Particle* const particles)
{
	this->particles = particles;
	this->time = 0;
	this->index = 0;
}

template <class Particle>
void EffectLooping<Particle>::Update(const sf::Time& delta)
{
	this->time += delta.asSeconds();

	// Release some particles if we can.
	if (this->time >= this->delay)
	{
		// Emit a number of particles by passing in the array and a virtual length.
		this->Emit(this->particles + (this->index * this->emission), this->emission);
		this->time -= this->delay;
		this->index++;
	}

	// Reset the index when we elapse.
	if (this->index >= (int)(this->lifespan / this->delay))
	{
		this->index = 0;
	}

	Effect<Particle>::Update(delta);
}

#endif
