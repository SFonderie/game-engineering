#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

const int Width = 800;
const int Height = 600;

const int Radius = 12;

//Start Execution
int main()
{
	//Create the SFML window using the numerical constants above.
	sf::RenderWindow window(sf::VideoMode(Width, Height), "SFML Template");

	//Create the actual brush.
	sf::CircleShape shape(Radius);

	//Define the base loop.
	while (window.isOpen())
	{
		//Define an event.
		sf::Event event;

		//Tick all possible events.
		while (window.pollEvent(event))
		{
			//Close the window if it gets closed.
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//Clean the screen.
		window.clear();

		//Set the brush color.
		shape.setFillColor(sf::Color::Red);

		//Get the position of the mouse relative to the window.
		sf::Vector2i position = sf::Mouse::getPosition(window);

		//Move the brush to the mouse.
		shape.setPosition(position.x - Radius, position.y - Radius);

		//Draw the brush.
		window.draw(shape);
		window.display();
	}

	//Default.
	return 0;
}
