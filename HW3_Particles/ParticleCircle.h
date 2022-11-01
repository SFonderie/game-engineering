#ifndef PARTICLE_CIRCLE_H
#define PARTICLE_CIRCLE_H

#include "ParticleShape.h"

/// <summary>
/// Manages a circular particle.
/// </summary>
class ParticleCircle : public ParticleShape<sf::CircleShape>
{

public:

	/// <summary>
	/// Actually initializes the particle with a position, lifespan, and radius.
	/// </summary>
	/// <param name="position">Particle position in screen space.</param>
	/// <param name="lifespan">Particle lifespan in seconds.</param>
	/// <param name="radius">Particle shape radius in pixels.</param>
	void Start(const sf::Vector2f& position, float lifespan, float radius);
};

#endif
