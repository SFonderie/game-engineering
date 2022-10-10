#include "Level.h"

Level::Level(int width, int height, int size)
{
	// Allocate the level sprites.
	tiles = new Tile[width * height];
	hover = new Tile;

	this->width = width;
	this->height = height;
	this->size = size;

	this->tileset = nullptr;
}

Level::~Level()
{
	// Only delete if it loaded.
	if (tileset) delete tileset;

	// Unload the level.
	delete[] tiles;
	delete hover;
}

int Level::getSize() const
{
	return size;
}

void Level::make(const std::string& path, int size)
{
	// Unload the old tileset.
	if (tileset) delete tileset;

	// Create and load the tileset.
	tileset = new Tileset(path, size);

	// Scales sprites to match the tile size.
	float scale = (float)this->size / size;

	// Load texture for and scale each tile.
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			// Only load if the tileset is valid.
			if (tileset->bounds)
			{
				// Also position the sprites.
				float xPos = (float)x * this->size;
				float yPos = (float)y * this->size;

				// Set the texture and the scale with an accessor.
				(*this)(x, y).sprite.setTexture(*(tileset->texture));
				(*this)(x, y).sprite.setPosition(sf::Vector2f(xPos, yPos));
				(*this)(x, y).sprite.setScale(sf::Vector2f(scale, scale));
			}

			// Reset all sprites on load.
			(*this)(x, y).spriteID = 0;
			(*this)(x, y).active = false;
		}
	}

	// Render the hover tile.
	if (tileset->bounds)
	{
		hover->sprite.setTexture(*(tileset->texture));
		hover->sprite.setScale(sf::Vector2f(scale, scale));
		hover->sprite.setColor(sf::Color(255, 255, 255, 127));
		hover->active = false;
	}
}

bool Level::save(std::ostream& output) const
{
	if (!tileset->bounds)
	{
		std::cout << "[ERROR] - Cannot save; tileset failed to load." << std::endl;
		return false;
	}

	// Load the level dimensions into the output stream.
	output << width << ' ' << height << ' ' << size << ' ';

	// Load the tileset path and size into the output stream.
	output << tileset->path << ' ' << tileset->size << ' ';

	// Load the level sprites into the output stream.
	for (int i = 0; i < width * height; i++)
	{
		// Add an asterisk if the tile is inactive.
		if (!(*this)(i).active) output << '*' << ' ';
		// Otherwise load the sprite ID as a number.
		else output << (*this)(i).spriteID << ' ';
	}

	return true;
}

bool Level::load(std::istream& input)
{
	if (!tileset->bounds)
	{
		std::cout << "[ERROR] - Cannot load; tileset failed to load." << std::endl;
		return false;
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			// Extract to a string.
			std::string value;
			input >> value;

			try
			{
				// Try to convert to int.
				int id = std::stoi(value);

				// If successful, load the ID.
				setTile(x, y, id);
				showTile(x, y);
			}
			// If the conversion failed, ignore.
			catch (std::invalid_argument) {}
		}
	}

	return true;
}

void Level::setTile(int x, int y, int index)
{
	// Only attempt if the tileset isn't broken.
	if (tileset && tileset->bounds)
	{
		// BEHOLD! THE OPERATOR-RIDDLED CODE THAT CHANGES TILE SPRITES!
		(*this)(x, y).sprite.setTextureRect((*tileset)(index));
		(*this)(x, y).spriteID = index;
	}
}

void Level::showTile(int x, int y)
{
	// Only attempt if the tileset isn't broken.
	if (tileset && tileset->bounds)
	{
		(*this)(x, y).active = true;
	}
}

void Level::hideTile(int x, int y)
{
	(*this)(x, y).active = false;
}

void Level::setHover(int x, int y, int index)
{
	// Only attempt if the tileset isn't broken.
	if (tileset && tileset->bounds)
	{
		// SEE SET TILE FOR MY EPIC COMMENTARY!
		hover->sprite.setTextureRect((*tileset)(index));
		hover->spriteID = index;

		// Also position the hover tile.
		if (x >= width) x = width - 1;
		if (x < 0) x = 0;

		if (y >= height) y = height - 1;
		if (y < 0) y = 0;

		// Convert position to pixels.
		float xPos = (float)x * this->size;
		float yPos = (float)y * this->size;

		// Now it will hover over the given coordinates.
		hover->sprite.setPosition(sf::Vector2f(xPos, yPos));
	}
}

void Level::showHover()
{
	// Only attempt if the tileset isn't broken.
	if (tileset && tileset->bounds)
	{
		hover->active = true;
	}
}

void Level::hideHover()
{
	hover->active = false;
}

void Level::render(sf::RenderWindow& window) const
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			// Only draw if the tile is active.
			if ((*this)(x, y).active)
			{
				// Draw to the window reference.
				window.draw((*this)(x, y).sprite);
			}
		}
	}

	// Always draw hover last.
	if (hover->active)
	{
		window.draw(hover->sprite);
	}
}

Level::Tile& Level::operator()(int index) const
{
	// Clamp the index.
	if (index >= width * height) index = width * height - 1;
	if (index < 0) index = 0;

	// Access the tile at index.
	return tiles[index];
}

Level::Tile& Level::operator()(int x, int y) const
{
	// Clamp the x-coordinate.
	if (x >= width) x = width - 1;
	if (x < 0) x = 0;

	// Clamp the y-coordinate.
	if (y >= height) y = height - 1;
	if (y < 0) y = 0;

	// Access the tile at (x, y).
	return tiles[(x * height) + y];
}
