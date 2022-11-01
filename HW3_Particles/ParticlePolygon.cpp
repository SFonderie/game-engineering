#include "ParticlePolygon.h"

void ParticlePolygon::Start(const sf::Vector2f& position, float lifespan, unsigned int count, float radius)
{
	// Invoke base start method.
	ParticleShape::Start(position, lifespan);

	// Set the number of points.
	this->GetShape().setPointCount(count);

	// Calculate some angles for later.
	float angle = (float)(2 * M_PI / count);
	float offset = Random::Range(0.f, angle);

	// Now actually set the polygon points using *math*.
	for (unsigned int i = 0; i < count; i++)
	{
		// Calculate the point positions.
		float theta = i * angle + offset;
		float x = (float)cos(theta) * radius;
		float y = (float)sin(theta) * radius;

		// Set the point positions.
		this->GetShape().setPoint(i, sf::Vector2f(x, y));
	}
}
