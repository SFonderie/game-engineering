#ifndef SHAPE_OBJECT_CPP
#define SHAPE_OBJECT_CPP

#include "ShapeObject.h"

template <class Shape>
ShapeObject<Shape>::ShapeObject(Object* parent, const sf::Color& color) : Object(parent)
{
	// Define the shape and color.
	this->shape = new Shape;
	this->color = color;
}

template <class Shape>
ShapeObject<Shape>::ShapeObject(const sf::Color& color) : ShapeObject(nullptr, color)
{
	// Default constructor doesn't do anything!
}

template <class Shape>
ShapeObject<Shape>::~ShapeObject()
{
	if (this->shape) delete this->shape;
}

template <class Shape>
void ShapeObject<Shape>::Update(const sf::Time& delta)
{
	if (!this->IsActive()) return;

	// First update everything.
	Object::Update(delta);

	// Update the shape.
	if (this->shape)
	{
		// Shapes render from their upper left corners.
		// I want them to render from their centers.
		sf::Vector2f scale = this->GetScale();
		float rotation = this->GetRotation();

		// We'll need these in a second.
		float rcos = cos(rotation * (float)M_PI / 180.f);
		float rsin = sin(rotation * (float)M_PI / 180.f);

		// To center the object, it needs to be offset by half its scale.
		// The scale also needs to shift between axes based on the rotation value.
		// That's what this trigonometric mess does.
		float xOffset = 0.5f * scale.x * rcos - 0.5f * scale.y * rsin;
		float yOffset = 0.5f * scale.y * rcos + 0.5f * scale.x * rsin;

		// Calculate the actual shape position by constructing an offset vector.
		sf::Vector2f position = this->GetPosition() - sf::Vector2f(xOffset, yOffset);

		// Now we can actually set the objects' stats.
		this->shape->setFillColor(this->GetColor());
		this->shape->setPosition(position);
		this->shape->setRotation(rotation);
		this->shape->setScale(scale);
	}
}

template <class Shape>
void ShapeObject<Shape>::Render(sf::RenderWindow& canvas)
{
	if (!this->IsVisible()) return;

	// If the shape exists, render ourselves.
	if (this->shape) canvas.draw(*(this->shape));

	// Now render children.
	Object::Render(canvas);
}

template <class Shape>
Shape& ShapeObject<Shape>::GetShape()
{
	return *this->shape;
}

template <class Shape>
sf::Color ShapeObject<Shape>::GetColor() const
{
	return this->color;
}

template <class Shape>
float ShapeObject<Shape>::GetRotation() const
{
	return this->rotation;
}

template <class Shape>
void ShapeObject<Shape>::SetColor(const sf::Color& color)
{
	this->color = color;
}

template <class Shape>
void ShapeObject<Shape>::SetRotation(float rotation)
{
	this->rotation = rotation;
}

#endif
