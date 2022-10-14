#include "Particle.h"
#include <iostream>

Particle::Particle()
{
	this->shape = nullptr;
	this->position = sf::Vector2f(0, 0);
	this->velocity = sf::Vector2f(0, 0);
	this->color = sf::Color::Black;
	this->lifespan = 0;
	this->life = 0;

	this->valid = false;
}

Particle::~Particle()
{
	if (shape) delete shape;
}

void Particle::Generate(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Color& color)
{
	this->position = position;
	this->velocity = velocity;
	this->color = color;

	float xSize = (float)Random::Range(SCALE_MIN, SCALE_MAX);
	float ySize = (float)Random::Range(SCALE_MIN, SCALE_MAX);

	this->shape = new sf::RectangleShape(sf::Vector2f(xSize, ySize));

	this->lifespan = Random::Range(LIFE_MIN, LIFE_MAX);
	this->life = 0;

	this->valid = true;
}

sf::Vector2f Particle::GetPosition() const
{
	return position + (velocity * life);
}

sf::Color Particle::GetColor() const
{
	return color - sf::Color(0, 0, 0, (unsigned int)(life / lifespan * 255));
}

bool Particle::IsAlive() const
{
	return life < lifespan;
}

void Particle::Update(const sf::Time& delta)
{
	// Ignore if invalid.
	if (!valid) return;

	// Tick the particle.
	life += delta.asSeconds();

	// Clamp the life to avoid overflows.
	if (life > lifespan) life = lifespan;

	// Actually update the particle.
	shape->setPosition(GetPosition());
	shape->setFillColor(GetColor());
}

void Particle::Render(sf::RenderWindow& canvas)
{
	// Ignore if invalid.
	if (!valid) return;

	// Draw the particle if it is alive.
	if (IsAlive()) canvas.draw(*shape);
}
