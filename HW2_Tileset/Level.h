#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Tileset.h"

/// <summary>
/// Manages the level sprites.
/// </summary>
class Level
{
	/// <summary>
	/// Level tile data.
	/// </summary>
	class Tile
	{
		// Tile is nested for a reason!
		friend class Level;

		/// <summary>
		/// Tile sprite.
		/// </summary>
		sf::Sprite sprite;

		/// <summary>
		/// ID of the assigned sprite.
		/// </summary>
		int spriteID = 0;

		/// <summary>
		/// Tile visibility.
		/// </summary>
		bool active = false;
	};

public:

	/// <summary>
	/// Allocates for and positions the level tiles.
	/// </summary>
	/// <param name="width">Width of the level in tiles.</param>
	/// <param name="height">Height of the level in tiles.</param>
	/// <param name="size">Size of each tile in pixels.</param>
	Level(int width, int height, int size);

	// Unloads the tiles.
	~Level();

	/// <summary>
	/// Returns the tile size in pixels.
	/// </summary>
	int getSize() const;

	/// <summary>
	/// Attempts to load a tileset.
	/// </summary>
	/// <param name="path">Local file path to the tileset texture.</param>
	/// <param name="size">Size of each tileset sprite in pixels.</param>
	void make(const std::string& path, int size);

	/// <summary>
	/// Places an integer string into the given output.
	/// </summary>
	bool save(std::ostream& output) const;

	/// <summary>
	/// Loads the input stream into the level.
	/// </summary>
	bool load(std::istream& input);

	/// <summary>
	/// Sets the tileset bounds for the tile at the given coordinates.
	/// </summary>
	void setTile(int x, int y, int index);

	/// <summary>
	/// Marks the tile at the given coordinates for rendering.
	/// </summary>
	void showTile(int x, int y);

	/// <summary>
	/// Unmarks the tile at the given coordinates for rendering.
	/// </summary>
	void hideTile(int x, int y);

	/// <summary>
	/// Updates and moves the hover tile to the given coordinates.
	/// </summary>
	void setHover(int x, int y, int index);

	/// <summary>
	/// Reveal the hover tile.
	/// </summary>
	void showHover();

	/// <summary>
	/// Hide the hover tile.
	/// </summary>
	void hideHover();

	/// <summary>
	/// Renders each level tile.
	/// </summary>
	void render(sf::RenderWindow& window) const;

private:

	/// <summary>
	/// Accesses the tile at the given index.
	/// </summary>
	Tile& operator()(int index) const;

	/// <summary>
	/// Accesses the tile at the given coordinates.
	/// </summary>
	Tile& operator()(int x, int y) const;

	/// <summary>
	/// Pointer to the array of tiles.
	/// </summary>
	Tile* tiles;

	/// <summary>
	/// Pointer to the hover tile.
	/// </summary>
	Tile* hover;

	/// <summary>
	/// Pointer to the current tileset.
	/// </summary>
	Tileset* tileset;

	/// <summary>
	/// Width of the level in tiles.
	/// </summary>
	int width;

	/// <summary>
	/// Height of the level in tiles.
	/// </summary>
	int height;

	/// <summary>
	/// Size of each tile in pixels.
	/// </summary>
	int size;
};

#endif
