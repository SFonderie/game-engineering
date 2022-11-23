#include "RectangleObject.h"

RectangleObject::RectangleObject(Object* parent, const sf::Color& color) : ShapeObject(parent, color)
{
	this->GetShape().setSize(sf::Vector2f(1, 1));
}

RectangleObject::RectangleObject(const sf::Color& color) : RectangleObject(nullptr, color)
{
	// Default constructor doesn't do anything!
}
