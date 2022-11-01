#ifndef EFFECT_CPP
#define EFFECT_CPP

#include "Effect.h"

template <class Particle>
Effect<Particle>::Effect()
{
	// Set the physical values.
	this->origin = sf::Vector2f(0, 0);

	// Default the particle pool.
	this->particles = nullptr;
	this->capacity = 0;
}

template <class Particle>
Effect<Particle>::~Effect()
{
	if (this->particles) delete[] this->particles;
}

template <class Particle>
void Effect<Particle>::Start(const sf::Vector2f& origin)
{
	// Set the basic values.
	this->origin = origin;

	// Escape if the capacity is invalid.
	if (this->capacity <= 0) return;

	// Allocate for the particle array if it doesn't exist yet.
	if (!this->particles) this->particles = this->MakeParticles(this->capacity);

	// Actually emit the particles.
	this->EmitParticles(this->particles);
}

template <class Particle>
void Effect<Particle>::Update(const sf::Time& delta)
{
	if (this->particles)
	{
		for (int i = 0; i < this->capacity; i++)
		{
			if (this->particles[i].IsAlive())
			{
				this->particles[i].Update(delta);
			}
		}
	}
}

template <class Particle>
void Effect<Particle>::Render(sf::RenderWindow& canvas) const
{
	if (this->particles)
	{
		for (int i = 0; i < this->capacity; i++)
		{
			if (this->particles[i].IsAlive())
			{
				this->particles[i].Render(canvas);
			}
		}
	}
}

template <class Particle>
const sf::Vector2f& Effect<Particle>::GetOrigin() const
{
	return this->origin;
}

template <class Particle>
bool Effect<Particle>::IsAlive() const
{
	bool alive = false;

	if (this->particles)
	{
		for (int i = 0; i < this->capacity; i++)
		{
			alive = alive || this->particles[i].IsAlive();
		}
	}

	return alive;
}

#endif
