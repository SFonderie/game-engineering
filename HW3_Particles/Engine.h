#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>

#include "EffectFirework.h"
#include "EffectSparkler.h"

/// <summary>
/// Manages particle effects.
/// </summary>
class Engine
{
	/// <summary>
	/// Current particle effect.
	/// </summary>
	IEffect* effect;

	/// <summary>
	/// Particle to create.
	/// </summary>
	int palette;

public:

	/// <summary>
	/// Creates a new SFML window hosting the particle engine.
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
};

#endif
