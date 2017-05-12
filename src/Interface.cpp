#include "Interface.h"
#include <iostream>

Interface::Interface() :
	render_window(sf::VideoMode(800, 600), "Cardiorgam", sf::Style::Default),
	event(),
	backgroundTexture(),
	background()
{}

int Interface::Run()
{
	while (render_window.isOpen())
	{
		Events();

		render_window.clear(sf::Color::White);
		DrawInterface();

		render_window.display();
	}

	system("pause");
	return 0;
}

int Interface::Events()
{
	while (render_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			render_window.close();
			break;
		default:
			break;
		}
	}

	return 0;
}

int Interface::DrawBackground()
{
	render_window.setFramerateLimit(60);
	if (!backgroundTexture.loadFromFile("World_map_DUS.png")) //! ¬—“¿¬»“‹ Õ”∆Õ€… ‘ŒÕ!!! !//
		std::cout << "Can't load Background" << "\n";
	backgroundTexture.setSmooth(true);
	background.setTexture(backgroundTexture);
	render_window.draw(background);

	return 0;
}

int Interface::DrawInterface()
{
	DrawBackground();
	DrawButton();

	return 0;
}