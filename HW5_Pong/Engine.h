#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Sounds.h"
#include "Board.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"

#include "TextObject.h"

/// <summary>
/// Manages Pong.
/// </summary>
class Engine
{

private:

	/// <summary>
	/// Game board object. Acts as a universal parent for the game's objects.
	/// </summary>
	Board* board = nullptr;

	/// <summary>
	/// Player paddle.
	/// </summary>
	Player* player = nullptr;

	/// <summary>
	/// Enemy paddle.
	/// </summary>
	Enemy* enemy = nullptr;

	/// <summary>
	/// Ball object.
	/// </summary>
	Ball* ball = nullptr;

	/// <summary>
	/// Player score tracker.
	/// </summary>
	TextObject* pScore = nullptr;

	/// <summary>
	/// Enemy score tracker.
	/// </summary>
	TextObject* eScore = nullptr;

	/// <summary>
	/// Countdown timer.
	/// </summary>
	TextObject* timer = nullptr;

	/// <summary>
	/// Victory screen board.
	/// </summary>
	Board* victory = nullptr;

	/// <summary>
	/// Victory screen message.
	/// </summary>
	TextObject* message = nullptr;

	/// <summary>
	/// Sound manager.
	/// </summary>
	Sounds sounds;

	/// <summary>
	/// Player scores.
	/// </summary>
	sf::Vector2u score;

	/// <summary>
	/// Time since game start.
	/// </summary>
	float time = 0;

	/// <summary>
	/// Flag used to prevent spam-resets.
	/// </summary>
	bool reset = false;

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
	/// Resets the game state.
	/// </summary>
	void Reset();

	/// <summary>
	/// Resets the game score.
	/// </summary>
	void ResetScore();
};

#endif
