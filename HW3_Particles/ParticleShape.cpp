#ifndef PARTICLE_SHAPE_CPP
#define PARTICLE_SHAPE_CPP

#include "ParticleShape.h"

template <class Shape>
Shape& ParticleShape<Shape>::GetShape()
{
	return *(this->shape);
}

template <class Shape>
ParticleShape<Shape>::ParticleShape()
{
	this->shape = nullptr;
}

template <class Shape>
ParticleShape<Shape>::~ParticleShape()
{
	if (this->shape) delete this->shape;
}

template <class Shape>
void ParticleShape<Shape>::Start(const sf::Vector2f& position, float lifespan)
{
	Particle::Start(position, lifespan);

	// Allocate for the shape if it doesn't exist.
	if (!this->shape) this->shape = new Shape;
}

template <class Shape>
void ParticleShape<Shape>::Update(const sf::Time& delta)
{
	Particle::Update(delta);

	// Update the shape, if it exists.
	if (this->shape)
	{
		this->shape->setPosition(this->GetPosition());
		this->shape->setFillColor(this->GetColor());
	}
}

template <class Shape>
void ParticleShape<Shape>::Render(sf::RenderWindow& canvas) const
{
	if (this->shape) canvas.draw(*(this->shape));
}

#endif
