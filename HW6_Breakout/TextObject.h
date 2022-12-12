#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "Object.h"

/// <summary>
/// Represents text visually.
/// </summary>
class TextObject : public Object
{

private:

	/// <summary>
	/// Renderable text object.
	/// </summary>
	sf::Text* text = nullptr;

	/// <summary>
	/// Shape color.
	/// </summary>
	sf::Color color;

public:

	/// <summary>
	/// Initializes the text object at the local zero on the given parent.
	/// </summary>
	explicit TextObject(Object* parent, const sf::Font& font, const sf::Color& color = sf::Color::White);

	/// <summary>
	/// Initializes the text object at the world zero.
	/// </summary>
	explicit TextObject(const sf::Font& font, const sf::Color& color = sf::Color::White);

	/// <summary>
	/// Unloads the text pointer.
	/// </summary>
	virtual ~TextObject();

	/// <summary>
	/// Updates the text color and string.
	/// </summary>
	virtual void Update(const sf::Time& delta);

	/// <summary>
	/// Renders the text.
	/// </summary>
	virtual void Render(sf::RenderWindow& canvas);

	/// <summary>
	/// Returns the text pointer.
	/// </summary>
	sf::Text& GetText();

	/// <summary>
	/// Returns the text color.
	/// </summary>
	sf::Color GetColor() const;

	/// <summary>
	/// Sets the text color.
	/// </summary>
	void SetColor(const sf::Color& color);
};

#endif
