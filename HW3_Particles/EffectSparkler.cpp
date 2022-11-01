#include "EffectSparkler.h"

EffectSparkler::EffectSparkler(float lifespan, float delay, int emission) : EffectLooping(lifespan, delay, emission) {  }

ParticlePolygon* EffectSparkler::MakeParticles(int capacity)
{
	return new ParticlePolygon[capacity];
}

void EffectSparkler::Emit(ParticlePolygon* const particles, int count)
{
	for (int i = 0; i < count; i++)
	{
		// Generate a random offset angle to get some variation in the particles.
		float angle = -Random::Range((float)(M_PI_2 - M_PI / 6), (float)(M_PI_2 + M_PI / 6));

		float c = cos(angle);
		float s = sin(angle);

		// Generate a random velocity value.
		int velocity = Random::Range(200, 300);

		ParticlePolygon& particle = particles[i];
		particle.Start(this->GetOrigin(), this->lifespan, 5, 5);
		particle.SetVelocity(sf::Vector2f(velocity * c, velocity * s));
		particle.SetForce(IEffect::GetGravity());

		// We only want a half shift at most.
		float shift = Random::Range(0.0f, 0.5f);

		// White-shift the hue to add some harmonious color variation.
		unsigned int r = (unsigned int)(this->color.r + (255 - this->color.r) * shift);
		unsigned int g = (unsigned int)(this->color.g + (255 - this->color.g) * shift);
		unsigned int b = (unsigned int)(this->color.b + (255 - this->color.b) * shift);

		// Fireworks color logic... again.
		particle.SetColor(sf::Color(r, g, b), true);
	}
}

void EffectSparkler::Start(const sf::Vector2f& origin)
{
	this->color = IEffect::PickColor();
	Effect::Start(origin);
}
