#include "Sounds.h"

Sounds::Sounds()
{
	this->buffers = std::map<std::string, sf::SoundBuffer*>();
	this->sound = sf::Sound();
}

Sounds::~Sounds()
{
	for (std::pair<const std::string, sf::SoundBuffer*> pair : this->buffers)
	{
		// Unloads the sound.
		delete pair.second;
	}

	// Empty the bad pointers.
	this->buffers.clear();
}

bool Sounds::LoadSound(const std::string& filepath, const std::string& name)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer;

	if (buffer->loadFromFile(filepath))
	{
		// Loading succeeded.
		this->buffers.emplace(name, buffer);

		return true;
	}

	// Loading failed.
	delete buffer;
	return false;
}

bool Sounds::PlaySound(const std::string& name)
{
	// Try to get the buffer pointer via a getter.
	sf::SoundBuffer* buffer = this->buffers[name];

	if (buffer)
	{
		// Set the buffer if it's valid.
		this->sound.setBuffer(*buffer);

		// Play the sound.
		this->sound.play();

		return true;
	}

	return false;
}
