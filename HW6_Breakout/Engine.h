#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Sounds.h"
#include "Board.h"
#include "Level.h"

#include "TextObject.h"

/// <summary>
/// Number of levels in the game.
/// </summary>
const int LEVELS = 3;

/// <summary>
/// Manages Pong.
/// </summary>
class Engine
{

private:

	/// <summary>
	/// Game sound object. Loads and controls sounds.
	/// </summary>
	Sounds* sounds = nullptr;

	/// <summary>
	/// Game board object. Acts as a universal parent for the game's objects.
	/// </summary>
	Board* board = nullptr;

	/// <summary>
	/// Game over: victory board.
	/// </summary>
	Board* winBoard = nullptr;

	/// <summary>
	/// Game over: loss board.
	/// </summary>
	Board* loseBoard = nullptr;

	/// <summary>
	/// Array of level objects.
	/// </summary>
	Level** levels = nullptr;

	/// <summary>
	/// Current active level index.
	/// </summary>
	int level = 0;

	/// <summary>
	/// Gate variable for preventing reset spam.
	/// </summary>
	bool reset = false;

	/// <summary>
	/// Victory state flag.
	/// </summary>
	bool victory = false;

	/// <summary>
	/// Failure state flag.
	/// </summary>
	bool failure = false;

public:

	/// <summary>
	/// Creates a new SFML window hosting the pong engine.
	/// </summary>
	/// <param name="width">Width of the SFML window in pixels.</param>
	/// <param name="height">Height of the SFML window in pixels.</param>
	/// <param name="name">Display name for the SFML window.</param>
	void Start(int width, int height, const std::string& name);

private:

	/// <summary>
	/// Ensures that the correct level is active and visible.
	/// </summary>
	void PrepareLevels();

	/// <summary>
	/// Invoked for each event that occurs this frame.
	/// </summary>
	/// <param name="event">Information about the current event.</param>
	/// <param name="window">Window that triggered the event.</param>
	void OnInput(const sf::Event& event, sf::RenderWindow& window);

	/// <summary>
	/// Invoked once per frame to update the engine state.
	/// </summary>
	/// <param name="delta">Frame delta time.</param>
	/// <param name="window">Window to update.</param>
	void OnUpdate(const sf::Time& delta, sf::RenderWindow& window);

	/// <summary>
	/// Invoked to render the window for this frame.
	/// </summary>
	/// <param name="window">Window to render.</param>
	void OnRender(sf::RenderWindow& window);

	/// <summary>
	/// Invoked to check the level after each update.
	/// </summary>
	void OnCheck();

	/// <summary>
	/// Resets the engine and level.
	/// </summary>
	void Reset();
};

#endif
