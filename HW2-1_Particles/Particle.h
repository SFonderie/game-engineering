#ifndef PARTICLE_H
#define PARTICLE_H

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>

#include "Random.h"

class Particle
{

private:

	const int SCALE_MIN = 20;
	const int SCALE_MAX = 32;

	const float LIFE_MIN = 0.75f;
	const float LIFE_MAX = 1.25f;

	// Holds the particle's shape.
	sf::Shape* shape;

	// Holds the particle's starting position.
	sf::Vector2f position;

	// Holds the particle's velocity vector.
	sf::Vector2f velocity;

	// Holds the particle's starting color.
	sf::Color color;

	// Holds the particle's lifespan in seconds.
	float lifespan;

	// Tracks the particle's current life in seconds.
	float life;

	// Late initialization flag.
	bool valid;

public:

	/// <summary>
	/// Creates but does not initialize the particle.
	/// </summary>
	Particle();

	// Unloads the particle shape.
	~Particle();

	/// <summary>
	/// Actually initializes the particle and allows it to update.
	/// </summary>
	/// <param name="position">Particle start position.</param>
	/// <param name="velocity">Particle velocity vector.</param>
	/// <param name="color">Particle overlay color.</param>
	void Generate(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Color& color);

	/// <summary>
	/// Calculates the particle's current position.
	/// </summary>
	sf::Vector2f GetPosition() const;

	/// <summary>
	/// Calculates the particle's current color.
	/// </summary>
	sf::Color GetColor() const;

	/// <summary>
	/// Determines whether the particle has exceeded its lifespan.
	/// </summary>
	bool IsAlive() const;

	/// <summary>
	/// Updates the particle.
	/// </summary>
	/// <param name="delta">Time since last update.</param>
	void Update(const sf::Time& delta);

	/// <summary>
	/// Renders the particle.
	/// </summary>
	/// <param name="canvas">Render to this object.</param>
	void Render(sf::RenderWindow& canvas);
};

#endif
