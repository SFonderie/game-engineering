#ifndef PARTICLE_SHAPE_H
#define PARTICLE_SHAPE_H

#include "Particle.h"

// So, this template requires some explanation... basically, I really didn't like the idea of
// re-implementing the Render method for each type of shape to get around virtual function limits.
// Instead, I'm using this template variable to outsource the cast type to the child class.
template <class Shape = sf::Shape>
/// <summary>
/// Abstract base class for managing a shaped particle.
/// </summary>
class ParticleShape : public Particle
{

private:

	/// <summary>
	/// Particle shape pointer.
	/// </summary>
	Shape* shape;

protected:

	/// <summary>
	/// Access the particle shape. Calling prior to Start causes a null pointer exception.
	/// </summary>
	Shape& GetShape();

public:

	/// <summary>
	/// Instantiates the particle.
	/// </summary>
	ParticleShape();

	/// <summary>
	/// Unloads the particle shape.
	/// </summary>
	virtual ~ParticleShape();

	/// <summary>
	/// Actually initializes the particle with a position and lifespan, and allocates the particle shape.
	/// </summary>
	/// <param name="position">Particle position in screen space.</param>
	/// <param name="lifespan">Particle lifespan in seconds.</param>
	virtual void Start(const sf::Vector2f& position, float lifespan);

	/// <summary>
	/// Increments the particle's timer, position, and velocity. Updates the particle shape.
	/// </summary>
	void Update(const sf::Time& delta);

	/// <summary>
	/// Renders the particle shape if the particle is alive.
	/// </summary>
	void Render(sf::RenderWindow& canvas) const;
};

// TEMPLATE CPP INCLUDE (YUCK)
#include "ParticleShape.cpp"

#endif
