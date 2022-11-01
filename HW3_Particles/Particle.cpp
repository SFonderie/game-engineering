#include "Particle.h"

Particle::Particle()
{
	// Default the physics.
	this->position = sf::Vector2f(0, 0);
	this->velocity = sf::Vector2f(0, 0);
	this->force = sf::Vector2f(0, 0);

	// Default the colors.
	this->color = sf::Color::Red;
	this->fade = false;

	// Default the timer.
	this->lifespan = 0;
	this->time = 0;

	// Particle is not ready.
	this->valid = false;
}

void Particle::Start(const sf::Vector2f& position, float lifespan)
{
	this->position = position;
	this->lifespan = lifespan;
	this->time = 0;

	// Activate the particle.
	this->valid = true;
}

void Particle::Update(const sf::Time& delta)
{
	// Ignore if invalid.
	if (!this->valid) return;

	// Extract delta for easy access.
	float deltaTime = delta.asSeconds();

	// Increment the timer.
	this->time += deltaTime;

	// Clamp the particle timer to the lifespan for consistency.
	if (this->time > this->lifespan) this->time = this->lifespan;

	// Update the physics of the particle.
	this->velocity += this->force * deltaTime;
	this->position += this->velocity * deltaTime;

	// Enable or disable the color fade using a ternary and some inverse math.
	this->color.a = (unsigned int)((this->fade ? 1 - (this->time / this->lifespan) : 1) * 255);
}

// Calculates the particle position 
const sf::Vector2f& Particle::GetPosition() const
{
	return this->position;
}

const sf::Vector2f& Particle::GetVelocity() const
{
	return this->velocity;
}

const sf::Vector2f& Particle::GetForce() const
{
	return this->force;
}

const sf::Color& Particle::GetColor() const
{
	return this->color;
}

bool Particle::IsValid() const
{
	return this->valid;
}

bool Particle::IsAlive() const
{
	return this->time < this->lifespan;
}

void Particle::SetPosition(const sf::Vector2f& position)
{
	this->position = position;
}

void Particle::SetVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

void Particle::SetForce(const sf::Vector2f& force)
{
	this->force = force;
}

void Particle::SetColor(const sf::Color& color, bool fade)
{
	this->color = color;
	this->fade = fade;
}

void Particle::End()
{
	this->time = this->lifespan;
}
