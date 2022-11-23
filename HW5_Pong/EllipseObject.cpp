#include "EllipseObject.h"

EllipseObject::EllipseObject(Object* parent, const sf::Color& color) : ShapeObject(parent, color)
{
	// Base diameter needs to be 1.
	this->GetShape().setRadius(0.5f);
}

EllipseObject::EllipseObject(const sf::Color& color) : EllipseObject(nullptr, color)
{
	// Default constructor doesn't do anything!
}
