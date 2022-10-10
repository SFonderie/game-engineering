#include "Tileset.h"

Tileset::Tileset(const std::string& path, int size)
{
	// Allocate the texture.
	texture = new sf::Texture;

	// Save inputs.
	this->path = path;
	this->size = size;

	// Attempt to load the texture from a file.
	bool loaded = texture->loadFromFile(path);

	// Only continue if the load was successful.
	if (loaded)
	{
		// Report the successful load to the user for feedback.
		std::cout << "Texture loaded from " << path << " successfully." << std::endl;

		// Calculate the texture width and height.
		sf::Vector2u dimensions = texture->getSize();
		int width = dimensions.x / size;
		int height = dimensions.y / size;

		// Allocate the rectangle bound array.
		bounds = new sf::IntRect[width * height];
		length = width * height;

		// Actually fill the rectangle array.
		for (int column = 0; column < width; column++)
		{
			// We will scan up-down, then left-right.
			for (int row = 0; row < height; row++)
			{
				// Get the pointer using *shudders* pointer math.
				sf::IntRect* bound = bounds + (column * height + row);

				// Set the rectangle bounds.
				bound->left = column * size;
				bound->top = row * size;
				bound->width = size;
				bound->height = size;
			}
		}
	}
	else
	{
		// Report the failure to load to the user.
		std::cout << "[ERROR] - " << path << " failed to load." << std::endl;

		// There is no bound array.
		bounds = nullptr;
		length = 0;
	}
}

Tileset::~Tileset()
{
	// Only unload if necessary.
	if (bounds) delete[] bounds;

	// Unload the texture.
	delete texture;
}

sf::IntRect& Tileset::operator()(int& index) const
{
	// Modulo doesn't work right for negatives.
	// So I need this nonsense to wrap the index.
	while (index >= length) index -= length;
	while (index < 0) index += length;

	// Return the bound.
	return bounds[index];
}
