#include "Brick.h"

Brick::Brick(Object* parent, int health) : RectangleObject(parent), health(health)
{
	this->UpdateColor();
	this->SetEntity(true);
}

void Brick::OnCollision(const sf::Time& delta, const Object* object, float time, const sf::Vector2f& normal)
{
	this->damage++;

	this->SetActive(this->IsAlive());
	this->SetVisible(this->IsAlive());
	this->UpdateColor();
}

bool Brick::IsAlive() const
{
	return this->health > this->damage;
}

void Brick::UpdateColor()
{
	this->SetColor(sf::Color(255, 51 * (this->health - this->damage), 0));
}

void Brick::Reset()
{
	this->damage = 0;

	this->SetActive(this->IsAlive());
	this->SetVisible(this->IsAlive());
	this->UpdateColor();
}
