#include "Board.h"

Board::Board(const sf::Color& color) : Object(nullptr), color(color)
{
	// Constructor doesn't do anything!
}

void Board::Render(sf::RenderWindow& canvas)
{
	// If the board is visible, fill the canvas with color.
	if (this->IsVisible()) canvas.clear(this->color);

	// Now render children.
	Object::Render(canvas);
}

const sf::Color& Board::GetColor() const
{
	return this->color;
}

void Board::SetColor(const sf::Color& color)
{
	this->color = color;
}

void Board::Reset()
{
	SetPosition(sf::Vector2f());
}
