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
const int Step = 4;
const int Max = 100;

const sf::Color RedColor = sf::Color::Red;
const sf::Color GreenColor = sf::Color::Green;
const sf::Color BlueColor = sf::Color::Blue;

//Start Execution
int main()
{
	sf::Color color = RedColor;
	int radius = Radius;
	bool draw = false;

	//Create the SFML window using the numerical constants above.
	sf::RenderWindow window(sf::VideoMode(Width, Height), "Paintbrush.cpp");

	//Create the actual brush.
	sf::CircleShape shape(radius);

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

			//When the user presses the left mouse button, begin drawing with the brush.
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == 0)
			{
				draw = true;
			}

			//When the user releases the left mouse button, stop drawing with the brush.
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == 0)
			{
				draw = false;
			}

			//Filter for key press events.
			if (event.type == sf::Event::KeyPressed)
			{
				//User presses up arrow.
				if (event.key.code == sf::Keyboard::Up)
				{
					//Increase brush size.
					radius += Step;

					//Report brush size increase for UX feedback reasons.
					std::cout << "Increased Brush Size. Size is now " << radius << std::endl;

					//Limit brush size.
					if (radius >= Max)
					{
						radius = Max;
					}
				}

				//User pressed down arrow.
				if (event.key.code == sf::Keyboard::Down)
				{
					//Decrease brush size.
					radius -= Step;

					//Report brush size decrease for UX feedback reasons.
					std::cout << "Decreased Brush Size. Size is now " << radius << std::endl;

					//Prevent exception.
					if (radius <= 0)
					{
						radius = 0;
					}
				}

				//User presses the 1 key.
				//Numpad 1 is not supported.
				if (event.key.code == sf::Keyboard::Num1)
				{
					//Set color to red.
					color = RedColor;

					//Report color change for UX feedback reasons.
					std::cout << "Brush is now Red." << std::endl;
				}

				//User presses the 2 key.
				//Numpad 2 is not supported.
				if (event.key.code == sf::Keyboard::Num2)
				{
					//Set color to green.
					color = GreenColor;

					//Report color change for UX feedback reasons.
					std::cout << "Brush is now Green." << std::endl;
				}

				//User presses the 3 key.
				//Numpad 3 is not supported.
				if (event.key.code == sf::Keyboard::Num3)
				{
					//Set color to blue.
					color = BlueColor;

					//Report color change for UX feedback reasons.
					std::cout << "Brush is now Blue." << std::endl;
				}

				//User presses the spacebar.
				if (event.key.code == sf::Keyboard::Space)
				{
					//Create a texture.
					sf::Texture texture;

					//Make the texture match the window.
					sf::Vector2u size = window.getSize();
					texture.create(size.x, size.y);

					//Take the screenshot.
					texture.update(window);

					//Attempt to save the texture to an output file.
					if (texture.copyToImage().saveToFile("PaintbrushScreenshot.png"))
					{
						//Report the screenshot for UX feedback reasons.
						std::cout << "Screenshot saved to PaintbrushScreenshot.png" << std::endl;
					}
				}
			}
		}

		//Set the brush size if drawing.
		shape.setRadius(draw ? radius : 0);

		//Set the brush color.
		shape.setFillColor(color);

		//Get the position of the mouse relative to the window.
		sf::Vector2i position = sf::Mouse::getPosition(window);

		//Move the brush to the mouse.
		shape.setPosition(position.x - radius, position.y - radius);

		//Draw the brush.
		window.draw(shape);
		window.display();
	}

	//Default.
	return 0;
}
