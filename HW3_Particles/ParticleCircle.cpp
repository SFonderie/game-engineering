#include "ParticleCircle.h"

void ParticleCircle::Start(const sf::Vector2f& position, float lifespan, float radius)
{
	// Invoke base start method.
	ParticleShape::Start(position, lifespan);

	// Set the shape radius value.
	this->GetShape().setRadius(radius);
}
