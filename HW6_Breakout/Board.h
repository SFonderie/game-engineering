#ifndef BOARD_H
#define BOARD_H

#include "Object.h"

/// <summary>
/// Virtual game board.
/// </summary>
class Board : public Object
{

private:

	/// <summary>
	/// Board background color.
	/// </summary>
	sf::Color color;

public:

	/// <summary>
	/// Creates the board with the given color, if any.
	/// </summary>
	explicit Board(const sf::Color& color = sf::Color::Black);

	/// <summary>
	/// Renders the board.
	/// </summary>
	virtual void Render(sf::RenderWindow& canvas);

	/// <summary>
	/// Returns the background color.
	/// </summary>
	const sf::Color& GetColor() const;

	/// <summary>
	/// Sets the background color.
	/// </summary>
	void SetColor(const sf::Color& color);

	/// <summary>
	/// Resets the board position.
	/// </summary>
	void Reset();
};

#endif
