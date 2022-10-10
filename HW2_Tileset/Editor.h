#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Level.h"

/// <summary>
/// Manages the SFML Tileset Editor.
/// </summary>
class Editor
{

public:

	/// <summary>
	/// Creates the SFML window with the given display name, width, and height.
	/// </summary>
	Editor(const std::string& name, int width, int height);

	// Unloads the window and level
	~Editor();

	/// <summary>
	/// Creates a level for the editor and loads a tileset for it.
	/// </summary>
	void makeLevel(int width, int height, int size, const std::string& path, int sprite);

	/// <summary>
	/// Loads a level based from the file path.
	/// </summary>
	void loadLevel(const std::string& path, bool check = false);

	/// <summary>
	/// Saves a level to the file path.
	/// </summary>
	void saveLevel(const std::string& path, bool check = false);

	/// <summary>
	/// Starts and maintains the editor loop.
	/// </summary>
	void start();

	/// <summary>
	/// Set the step size manually.
	/// </summary>
	void setStep(int step);

	/// <summary>
	/// Set the level file path manually.
	/// </summary>
	void setPath(const std::string& path);

private:

	/// <summary>
	/// Handles event processing for this frame.
	/// </summary>
	void onInput(sf::Event& event);

	/// <summary>
	/// Handles editor updates for this frame.
	/// </summary>
	void onUpdate();

	/// <summary>
	/// Handles rendering the editor this frame.
	/// </summary>
	void onRender();

	/// <summary>
	/// Adds or removes a tile at the mouse position.
	/// </summary>
	void clickTile(bool add);

	/// <summary>
	/// Takes a screenshot.
	/// </summary>
	void screenshot();

	/// <summary>
	/// Pointer to the SFML window.
	/// </summary>
	sf::RenderWindow* window;

	/// <summary>
	/// Pointer to the active level.
	/// </summary>
	Level* level;

	/// <summary>
	/// Current tile index.
	/// </summary>
	int tile;

	/// <summary>
	/// Tile step size.
	/// </summary>
	int step;

	/// <summary>
	/// Local level file path.
	/// </summary>
	std::string path;

	/// <summary>
	/// Flag to prevent accidental saves and loads.
	/// </summary>
	char confirm;
};

#endif
