#ifndef PARTICLE_RECTANGLE_H
#define PARTICLE_RECTANGLE_H

#include "ParticleShape.h"

/// <summary>
/// Manages a rectangular particle.
/// </summary>
class ParticleRectangle : public ParticleShape<sf::RectangleShape>
{

public:

	/// <summary>
	/// Actually initializes the particle with a position, lifespan, width, and height.
	/// </summary>
	/// <param name="position">Particle position in screen space.</param>
	/// <param name="lifespan">Particle lifespan in seconds.</param>
	/// <param name="size">Particle size Vector2 in pixels.</param>
	void Start(const sf::Vector2f& position, float lifespan, const sf::Vector2f& size);
};

#endif
