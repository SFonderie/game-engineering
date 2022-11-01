#include "EffectFirework.h"

EffectFirework::EffectFirework(int layers, int density, int growth)
{
	this->layers = layers;
	this->density = density;
	this->growth = growth;

	// Set the capacity to the count.
	this->capacity = this->GetCount();
}

ParticleCircle* EffectFirework::MakeParticles(int capacity)
{
	return new ParticleCircle[capacity];
}

void EffectFirework::EmitParticles(ParticleCircle* const particles)
{
	int range = Random::Range(80, 100);
	sf::Color hue = IEffect::PickColor();

	// Iterate through the firework layers.
	for (int i = 0; i < this->layers; i++)
	{
		// Calculate the angle for each particle, knowing 2Gi + D particles.
		float angle = (float)(2 * M_PI / (2 * this->growth * i + this->density));

		// Iterate through each particle (again, 2Gi + D particles).
		for (int p = 0; p < 2 * this->growth * i + this->density; p++)
		{
			// Create a slight random offset for visual interest.
			float offset = Random::Range(-angle / 16, angle / 16);

			// Some particles fade out faster than others.
			float lifespan = Random::Range(1.5f, 2.0f);

			// Calculate time factors.
			float v = (i + 1) * range / lifespan;
			float a = -v / lifespan;

			// Expensive; pre-calculate.
			float c = cos(p * angle + offset);
			float s = sin(p * angle + offset);

			// Extract the particle we will be emitting using some more summation math (with 2Gi + D).
			ParticleCircle& particle = particles[(i * (i - 1) * this->growth) + ((i + 1) * this->density) + p];

			// Actually set the particle values.
			particle.Start(this->GetOrigin(), lifespan, 5);
			particle.SetVelocity(sf::Vector2f(v * c, v * s) - IEffect::GetGravity());
			particle.SetForce(sf::Vector2f(a * c, a * s) + IEffect::GetGravity());

			// We only want a half shift at most.
			float shift = Random::Range(0.0f, 0.5f);

			// White-shift the hue to add some harmonious color variation.
			unsigned int r = (unsigned int)(hue.r + (255 - hue.r) * shift);
			unsigned int g = (unsigned int)(hue.g + (255 - hue.g) * shift);
			unsigned int b = (unsigned int)(hue.b + (255 - hue.b) * shift);

			// Actually set the hue.
			particle.SetColor(sf::Color(r, g, b), true);
		}
	}
}

void EffectFirework::Start(const sf::Vector2f& origin)
{
	Effect::Start(origin);
}

int EffectFirework::GetCount() const
{
	// Each layer contains 2Gi + D particles, where i = 0 at base.
	return (this->layers * (this->layers - 1) * this->growth) + ((this->layers + 1) * this->density);
}
