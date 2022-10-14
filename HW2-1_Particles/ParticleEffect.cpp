#include "ParticleEffect.h"

sf::Color ParticleEffect::PickColor()
{
	switch (Random::Range(0, 6))
	{
	case 0: return sf::Color(255, 000, 000); // Full Red
	case 1: return sf::Color(255, 128, 000); // Orange
	case 2: return sf::Color(255, 200, 000); // Yellow
	case 3: return sf::Color(000, 255, 000); // Green
	case 4: return sf::Color(000, 128, 255); // Blue
	case 5: return sf::Color(128, 000, 255); // Purple
	case 6: return sf::Color(255, 000, 255); // Magenta

	default: return sf::Color::White;
	}
}

ParticleEffect::ParticleEffect(const sf::Vector2f& origin, int count)
{
	this->origin = origin;
	this->count = count;

	// Why Particle uses late initialization:
	// Array-allocate for all of the particles.
	this->particles = new Particle[this->count];

	// Determine the angular range in radians.
	float slice = (float)(2 * M_PI / this->count);

	// Randomly pick a main color.
	sf::Color hue = PickColor();

	// Iterate through each particle.
	for (int i = 0; i < this->count; i++)
	{
		// Calculate the angle with a random range of half the total.
		float angle = slice * i + Random::Range(-slice / 4, slice / 4);

		// Determine a random speed for the velocity.
		int speed = Random::Range(SPEED_MIN, SPEED_MAX);

		// Actually combine the angle and speed to create a velocity vector.
		sf::Vector2f velocity(std::cos(angle) * speed, -std::sin(angle) * speed);

		// We only want a half shift at most.
		float shift = Random::Range(0.0f, 0.5f);

		// White-shift the hue to add some harmonious color variation.
		unsigned int r = (unsigned int)(hue.r + (255 - hue.r) * shift);
		unsigned int g = (unsigned int)(hue.g + (255 - hue.g) * shift);
		unsigned int b = (unsigned int)(hue.b + (255 - hue.b) * shift);

		// Actually initialize and generate the particle so it can start moving.
		this->particles[i].Generate(this->origin, velocity, sf::Color(r, g, b));
	}
}

ParticleEffect::~ParticleEffect()
{
	delete[] particles;
}

sf::Vector2f ParticleEffect::GetOrigin() const
{
	return origin;
}

bool ParticleEffect::IsAlive() const
{
	bool flag = false;

	for (int i = 0; i < count; i++)
	{
		flag = flag || particles[i].IsAlive();
	}

	return flag;
}

void ParticleEffect::Update(const sf::Time& delta)
{
	for (int i = 0; i < count; i++)
	{
		particles[i].Update(delta);
	}
}

void ParticleEffect::Render(sf::RenderWindow& canvas)
{
	for (int i = 0; i < count; i++)
	{
		particles[i].Render(canvas);
	}
}
