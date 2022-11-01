#include "ParticleRectangle.h"

void ParticleRectangle::Start(const sf::Vector2f& position, float lifespan, const sf::Vector2f& size)
{
	// Invoke base start method.
	ParticleShape::Start(position, lifespan);

	// Set the shape size value.
	this->GetShape().setSize(size);
}
