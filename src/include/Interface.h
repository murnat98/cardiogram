#pragma once
#include "Button.h"
#include <SFGUI\SFGUI.hpp>
#include <SFGUI\Widgets.hpp>

#include <SFML\Graphics.hpp>


class Interface:
	public Button
{
public:
	sf::RenderWindow render_window;
	sf::Event event;
	sf::Texture backgroundTexture;
	sf::Sprite background;


	Interface();

	int Run();
	int Events();
	int DrawInterface();
	int DrawBackground();
	int DrawButton();
};
