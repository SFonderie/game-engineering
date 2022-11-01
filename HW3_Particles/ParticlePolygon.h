#ifndef PARTICLE_POLYGON_H
#define PARTICLE_POLYGON_H

#include "ParticleShape.h"

/// <summary>
/// Manages a uniform polygonal particle.
/// </summary>
class ParticlePolygon : public ParticleShape<sf::ConvexShape>
{

public:

	/// <summary>
	/// Actually initializes the particle with a position, lifespan, point count, and radius
	/// </summary>
	/// <param name="position">Particle position in screen space.</param>
	/// <param name="lifespan">Particle lifespan in seconds.</param>
	/// <param name="count">Number of points in this polygon.</param>
	/// <param name="radius">Radius of the polygon.</param>
	void Start(const sf::Vector2f& position, float lifespan, unsigned int count, float radius);
};

#endif
