#ifndef TILESET_H
#define TILESET_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

/// <summary>
/// Manages a tileset texture and sprite bounds.
/// </summary>
class Tileset
{
	// Only Level can access this class.
	friend class Level;

	/// <summary>
	/// Creates a tileset by loading the given texture.
	/// </summary>
	/// <param name="path">Local file path to the tileset texture.</param>
	/// <param name="size">Size of each tile sprite in pixels.</param>
	Tileset(const std::string& path, int size);

	// Unload the texture and sprite bounds.
	~Tileset();

	/// <summary>
	/// Returns the bound at the given index.
	/// </summary>
	sf::IntRect& operator()(int& index) const;

	/// <summary>
	/// Pointer to the tileset texture.
	/// </summary>
	sf::Texture* texture;

	/// <summary>
	/// Pointer to the sprite bound array.
	/// </summary>
	sf::IntRect* bounds;

	/// <summary>
	/// Tileset path.
	/// </summary>
	std::string path;

	/// <summary>
	/// Tileset sprite size.
	/// </summary>
	int size;

	/// <summary>
	/// Length of the bounds array.
	/// </summary>
	int length;
};

#endif
