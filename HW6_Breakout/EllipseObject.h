#ifndef ELLIPSE_OBJECT_H
#define ELLIPSE_OBJECT_H

#include "ShapeObject.h"

/// <summary>
/// Object representing an elliptical object.
/// </summary>
class EllipseObject : public ShapeObject<sf::CircleShape>
{

public:

	/// <summary>
	/// Initializes the ellipse object at the local zero on the given parent.
	/// </summary>
	explicit EllipseObject(Object* parent, const sf::Color& color = sf::Color::White);

	/// <summary>
	/// Initializes the ellipse object at the world zero.
	/// </summary>
	explicit EllipseObject(const sf::Color& color = sf::Color::White);
};

#endif
