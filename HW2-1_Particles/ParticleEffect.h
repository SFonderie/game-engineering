#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#include "Particle.h"

class ParticleEffect
{
private:

	const int SPEED_MIN = 40;
	const int SPEED_MAX = 64;

	// Particle array head.
	Particle* particles;

	// Generator center.
	sf::Vector2f origin;

	// Particle count.
	int count;

	// Randomly select a color.
	static sf::Color PickColor();

public:

	/// <summary>
	/// Creates and initializes a radial particle generator.
	/// </summary>
	/// <param name="origin">Center of the particle effect.</param>
	/// <param name="count">Number of particles to be generated.</param>
	ParticleEffect(const sf::Vector2f& origin, int count);

	// Unload particles.
	~ParticleEffect();

	/// <summary>
	/// Determines the generator's center.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetOrigin() const;

	/// <summary>
	/// Determines whether all generated particles have exceeded their lifespans.
	/// </summary>
	bool IsAlive() const;

	/// <summary>
	/// Updates all generated particles.
	/// </summary>
	void Update(const sf::Time& delta);

	/// <summary>
	/// Renders all generated particles.
	/// </summary>
	void Render(sf::RenderWindow& canvas);
};

#endif
