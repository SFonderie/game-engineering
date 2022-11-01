#ifndef PARTICLE_H
#define PARTICLE_H

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include "Random.h"

/// <summary>
/// Abstract base class for managing a particle.
/// </summary>
class Particle
{

private:

	/// <summary>
	/// INITIAL particle position in screen space.
	/// </summary>
	sf::Vector2f position;

	/// <summary>
	/// INITIAL particle velocity in screen space. Defaults to the zero vector.
	/// </summary>
	sf::Vector2f velocity;

	/// <summary>
	/// INITIAL particle acceleration in screen space. Defaults to the zero vector.
	/// </summary>
	sf::Vector2f force;

	/// <summary>
	/// INITIAL particle color.
	/// </summary>
	sf::Color color;

	/// <summary>
	/// Particle lifespan in seconds.
	/// </summary>
	float lifespan;

	/// <summary>
	/// Particle time in seconds.
	/// </summary>
	float time;

	/// <summary>
	/// Gates update and render calls.
	/// </summary>
	bool valid;

	/// <summary>
	/// Causes the particle to fade out.
	/// </summary>
	bool fade;

public:

	/// <summary>
	/// Instantiates the particle.
	/// </summary>
	Particle();

	/// <summary>
	/// Actually initializes the particle with a position and lifespan.
	/// </summary>
	/// <param name="position">Particle position in screen space.</param>
	/// <param name="lifespan">Particle lifespan in seconds.</param>
	virtual void Start(const sf::Vector2f& position, float lifespan);

	/// <summary>
	/// Increments the particle's timer, position, and velocity.
	/// </summary>
	virtual void Update(const sf::Time& delta);

	/// <summary>
	/// Implement to render the particle.
	/// </summary>
	virtual void Render(sf::RenderWindow& canvas) const = 0;

	/// <summary>
	/// Returns the current particle position in screen space.
	/// </summary>
	const sf::Vector2f& GetPosition() const;

	/// <summary>
	/// Returns the current particle velocity.
	/// </summary>
	const sf::Vector2f& GetVelocity() const;

	/// <summary>
	/// Returns the current particle acceleration.
	/// </summary>
	const sf::Vector2f& GetForce() const;

	/// <summary>
	/// Returns the current particle color.
	/// </summary>
	const sf::Color& GetColor() const;

	/// <summary>
	/// Checks if the particle is valid.
	/// </summary>
	bool IsValid() const;

	/// <summary>
	/// Checks if the particle is alive.
	/// </summary>
	bool IsAlive() const;

	/// <summary>
	/// Sets the particle position in screen space.
	/// </summary>
	void SetPosition(const sf::Vector2f& position);

	/// <summary>
	/// Sets the particle velocity.
	/// </summary>
	void SetVelocity(const sf::Vector2f& velocity);

	/// <summary>
	/// Sets the particle acceleration.
	/// </summary>
	void SetForce(const sf::Vector2f& force);

	/// <summary>
	/// Sets the particle color.
	/// </summary>
	void SetColor(const sf::Color& color, bool fade);

	/// <summary>
	/// Force-ends the particle's timer.
	/// </summary>
	void End();
};

#endif
