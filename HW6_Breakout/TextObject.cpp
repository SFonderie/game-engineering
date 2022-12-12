#include "TextObject.h"

TextObject::TextObject(Object* parent, const sf::Font& font, const sf::Color& color) : Object(parent)
{
	// Define the shape and color.
	this->text = new sf::Text;
	this->text->setFont(font);
	this->color = color;
}

TextObject::TextObject(const sf::Font& font, const sf::Color& color) : TextObject(nullptr, font, color)
{
	// Default constructor doesn't do anything!
}

TextObject::~TextObject()
{
	if (this->text) delete this->text;
}

void TextObject::Update(const sf::Time& delta)
{
	if (!this->IsActive()) return;

	// First update everything.
	Object::Update(delta);

	// Update the shape.
	if (this->text)
	{
		// Text renders from its upper left corner.
		// I want it to render from its centers.
		sf::Vector2f scale = this->GetScale();

		// Calculate the text position by constructing an offset vector.
		sf::Vector2f position = this->GetPosition();

		// Now we can actually set the objects' stats.
		this->text->setFillColor(this->GetColor());
		this->text->setPosition(position);
	}
}

void TextObject::Render(sf::RenderWindow& canvas)
{
	if (!this->IsVisible()) return;

	// If the text exists, render ourselves.
	if (this->text) canvas.draw(*(this->text));

	// Now render children.
	Object::Render(canvas);
}

sf::Text& TextObject::GetText()
{
	return *this->text;
}

sf::Color TextObject::GetColor() const
{
	return this->color;
}

void TextObject::SetColor(const sf::Color& color)
{
	this->color = color;
}
