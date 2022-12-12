#ifndef SHAPE_OBJECT_H
#define SHAPE_OBJECT_H

#include "Object.h"

/// <summary>
/// Shape type to render. Must be a child of sf::Shape.
/// </summary>
template <class Shape = sf::Shape>

/// <summary>
/// Collision-enabled object with a renderable shape.
/// </summary>
class ShapeObject : public Object
{

private:

	/// <summary>
	/// Shape pointer.
	/// </summary>
	Shape* shape = nullptr;

	/// <summary>
	/// Shape rotation in degrees.
	/// </summary>
	float rotation = 0;

	/// <summary>
	/// Shape color.
	/// </summary>
	sf::Color color;

public:

	/// <summary>
	/// Initializes the shape object at the local zero on the given parent.
	/// </summary>
	explicit ShapeObject(Object* parent, const sf::Color& color = sf::Color::White);

	/// <summary>
	/// Initializes the shape object at the world zero.
	/// </summary>
	explicit ShapeObject(const sf::Color& color = sf::Color::White);

	/// <summary>
	/// Unloads the shape pointer.
	/// </summary>
	virtual ~ShapeObject();

	/// <summary>
	/// Updates the shape color.
	/// </summary>
	virtual void Update(const sf::Time& delta);

	/// <summary>
	/// Renders the shape.
	/// </summary>
	virtual void Render(sf::RenderWindow& canvas);

	/// <summary>
	/// Returns the shape pointer.
	/// </summary>
	Shape& GetShape();

	/// <summary>
	/// Returns the shape color.
	/// </summary>
	sf::Color GetColor() const;

	/// <summary>
	/// Returns the shape rotation angle. Rotation is visual only.
	/// </summary>
	float GetRotation() const;

	/// <summary>
	/// Sets the shape color.
	/// </summary>
	void SetColor(const sf::Color& color);

	/// <summary>
	/// Sets the shape rotation angle. Rotation is visual only.
	/// </summary>
	void SetRotation(float rotation);
};

// Template class include!
#include "ShapeObject.cpp"

#endif
