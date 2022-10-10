#include "Editor.h"

Editor::Editor(const std::string& name, int width, int height)
{
	window = new sf::RenderWindow(sf::VideoMode(width, height), name);
	level = nullptr;

	tile = 0;
	step = 0;

	path = "";
	confirm = 0;
}

Editor::~Editor()
{
	// Only unload if needed.
	if (level) delete level;

	// Unload the SFML window.
	delete window;
}

void Editor::makeLevel(int width, int height, int size, const std::string& path, int sprite)
{
	// Unload any existing level.
	if (level) delete level;

	// Create a level and load its tileset.
	level = new Level(width, height, size);
	level->make(path, sprite);
}

void Editor::loadLevel(const std::string& path, bool check)
{
	if (path.empty())
	{
		std::cout << "[ERROR] - Level file path is empty." << std::endl;
		return;
	}

	// Only follow through if confirm is passed!
	if (check && confirm != 'l')
	{
		std::cout << "Preparing to Load Level from " << path << ". Press again to confirm." << std::endl;
		confirm = 'l';
		return;
	}

	// Make the file.
	std::ifstream file;
	file.open(path);

	// LOAD FROM FILE!
	if (file.is_open())
	{
		// First, we must construct a new level.
		// Create the empty input variables.
		int width, height, size, sprite;
		std::string tileset;

		// Load from the input stream.
		file >> width >> height >> size >> tileset >> sprite;

		// Make the new level (which also deletes the old).
		makeLevel(width, height, size, tileset, sprite);

		// Now we can ACTUALLY load the level tiles with the rest of the stream.
		if (level->load(file)) std::cout << "Loaded Level from " << path << "." << std::endl;
	}
	else
	{
		std::cout << "[ERROR] - File failed to open." << std::endl;
	}

	file.close();
	confirm = 0;
}

void Editor::saveLevel(const std::string& path, bool check)
{
	if (path.empty())
	{
		std::cout << "[ERROR] - Level file path is empty." << std::endl;
		return;
	}

	// Only follow through if confirm is passed!
	if (check && confirm != 's')
	{
		std::cout << "Preparing to Save Level to " << path << ". Press again to confirm." << std::endl;
		confirm = 's';
		return;
	}

	// Make the file.
	std::ofstream file;
	file.open(path);

	// SAVE TO FILE!
	if (file.is_open())
	{
		if (level->save(file)) std::cout << "Saved Level to " << path << "." << std::endl;
	}
	else
	{
		std::cout << "[ERROR] - File failed to open." << std::endl;
	}

	file.close();
	confirm = 0;
}

void Editor::start()
{
	while (window->isOpen())
	{
		sf::Event query;

		while (window->pollEvent(query))
		{
			onInput(query);
		}

		onUpdate();
		onRender();
	}
}

void Editor::setStep(int step)
{
	this->step = step;
}

void Editor::setPath(const std::string& path)
{
	this->path = path;
}

void Editor::onInput(sf::Event& event)
{
	bool cancel = false;

	if (event.type == sf::Event::Closed)
	{
		window->close();
	}

	// Handle mouse button clicks using a private helper method.
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		clickTile(true);
		cancel = true;
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		clickTile(false);
		cancel = true;
	}

	// Handle key input events.
	if (event.type == sf::Event::KeyPressed)
	{
		cancel = true;

		// Tile scrolling inputs (increment / decrement)
		if (event.key.code == sf::Keyboard::Left) tile--;
		if (event.key.code == sf::Keyboard::Right) tile++;

		// Tile jumping inputs (increment / decrement sets)
		if (event.key.code == sf::Keyboard::Down) tile -= step;
		if (event.key.code == sf::Keyboard::Up) tile += step;

		// Screenshot button.
		if (event.key.code == sf::Keyboard::Space) screenshot();

		// Save and load commands.
		if (event.key.code == sf::Keyboard::E)
		{
			saveLevel(path, true);
			cancel = false;
		}

		if (event.key.code == sf::Keyboard::R)
		{
			loadLevel(path, true);
			cancel = false;
		}
	}

	if (confirm != 0 && cancel)
	{
		std::cout << "Operation cancelled." << std::endl;
		confirm = 0;
	}
}

void Editor::onUpdate()
{
	// Move the hover tile.
	if (level)
	{
		// Extract the mouse position relative to the window.
		sf::Vector2i mouse = sf::Mouse::getPosition(*window);

		// Snaps the mouse to a tile grid.
		int x = mouse.x / level->getSize();
		int y = mouse.y / level->getSize();

		level->setHover(x, y, tile);
		level->showHover();
	}
}

void Editor::onRender()
{
	window->clear();

	// Render the entire level.
	if (level) level->render(*window);

	window->display();
}

void Editor::clickTile(bool add)
{
	if (!level) return;

	// Extract the mouse position relative to the window.
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);

	// Snaps the mouse to a tile grid.
	int x = mouse.x / level->getSize();
	int y = mouse.y / level->getSize();

	if (add)
	{
		level->setTile(x, y, tile);
		level->showTile(x, y);
	}
	else
	{
		level->hideTile(x, y);
	}
}

void Editor::screenshot()
{
	sf::Texture texture;
	sf::Vector2u size = window->getSize();

	texture.create(size.x, size.y);
	texture.update(*window);

	if (texture.copyToImage().saveToFile("Saved/HW2_Screenshot.png"))
	{
		std::cout << "Saved a screenshot to Saved/HW2_Screenshot.png" << std::endl;
	}
}
