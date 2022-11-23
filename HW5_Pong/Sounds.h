#ifndef SOUNDS_H
#define SOUNDS_H

#include <map>
#include <SFML/Audio.hpp>

/// <summary>
/// Manages playing sounds.
/// </summary>
class Sounds
{

private:

	/// <summary>
	/// Map of loaded sounds keyed to string names.
	/// </summary>
	std::map<std::string, sf::SoundBuffer*> buffers;

	/// <summary>
	/// Actually plays the sounds.
	/// </summary>
	sf::Sound sound;

public:

	/// <summary>
	/// Initializes the sounds object.
	/// </summary>
	Sounds();

	/// <summary>
	/// Unloads the buffers.
	/// </summary>
	~Sounds();

	/// <summary>
	/// Attempts to load the given sound into the manager with the given name.
	/// If the load fails, then the function returns false.
	/// </summary>
	bool LoadSound(const std::string& filepath, const std::string& name);

	/// <summary>
	/// Attempts to find the given sound and play it.
	/// If the find fails, then the function returns false.
	/// </summary>
	bool PlaySound(const std::string& name);
};

#endif
