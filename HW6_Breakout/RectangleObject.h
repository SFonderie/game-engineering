#ifndef RECTANGLE_OBJECT_H
#define RECTANGLE_OBJECT_H

#include "ShapeObject.h"

/// <summary>
/// Object representing a rectangular object.
/// </summary>
class RectangleObject : public ShapeObject<sf::RectangleShape>
{

public:

	/// <summary>
	/// Initializes the rectangle object at the local zero on the given parent.
	/// </summary>
	explicit RectangleObject(Object* parent, const sf::Color& color = sf::Color::White);

	/// <summary>
	/// Initializes the rectangle object at the world zero.
	/// </summary>
	explicit RectangleObject(const sf::Color& color = sf::Color::White);
};

#endif
