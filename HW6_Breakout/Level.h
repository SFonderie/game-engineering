#ifndef LEVEL_H
#define LEVEL_H

#include "Ball.h"
#include "Brick.h"
#include "TextObject.h"

const int BRICKS = 5;
const int ROWS = 5;

/// <summary>
/// Level is essentially a filter object that manages its own children.
/// </summary>
class Level : public Object
{

private:

	/// <summary>
	/// Level's player paddle.
	/// </summary>
	Player* player = nullptr;

	/// <summary>
	/// Level's ball.
	/// </summary>
	Ball* ball = nullptr;

	/// <summary>
	/// Local name value.
	/// </summary>
	std::string name;

	/// <summary>
	/// List of the brick lists.
	/// </summary>
	std::vector<Brick*> bricks;

	/// <summary>
	/// Number of misses the player is allowed.
	/// </summary>
	int lives = 0;

	// UI
	TextObject* levelLabel = nullptr;
	TextObject* livesLabel = nullptr;

public:

	/// <summary>
	/// Creates a new level with bounds.
	/// </summary>
	/// <param name="parent">Parent object. Should be a board.</param>
	/// <param name="ID">Level ID.</param>
	/// <param name="width">Width of the screen in pixels.</param>
	/// <param name="height">Height of the screen in pixels.</param>
	/// <param name="name">Display name for this level.</param>
	/// <param name="sounds">Sounds object needed for the ball.</param>
	Level(Object* parent, int ID, int width, int height, const std::string& name, Sounds& sounds, const sf::Font& font);

	/// <summary>
	/// Here just in case...
	/// </summary>
	virtual ~Level();

	/// <summary>
	/// Returns the level's name.
	/// </summary
	const std::string& GetName() const;

	/// <summary>
	/// Returns the level's player paddle.
	/// </summary>
	Player& GetPlayer() const;

	/// <summary>
	/// Returns the level's ball paddle.
	/// </summary>
	Ball& GetBall() const;

	/// <summary>
	/// True if any bricks are still alive.
	/// </summary>
	bool HasBricks() const;

	/// <summary>
	/// True if the ball is in range.
	/// </summary>
	bool HasBall() const;

	/// <summary>
	/// True if the player has lives.
	/// </summary>
	bool HasLives() const;

	/// <summary>
	/// Resets the level and its children.
	/// </summary>
	void ResetAll();

	/// <summary>
	/// Resets the player and ball.
	/// </summary>
	void ResetPlayer();

	/// <summary>
	/// Damages the player.
	/// </summary>
	void DamagePlayer();
};

#endif
