#include <SFGUI\SFGUI.hpp> 
#include <SFGUI\Widgets.hpp> 

#include <SFML\Graphics.hpp> 
#include <iostream> 

sfg::SFGUI but; 
sf::RenderWindow render_window(sf::VideoMode(800, 600), "Cardiorgam");
sf::Event event;
sf::Texture backgroundTexture;
sf::Sprite background;

int DrawButton(); 

int Events()
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

int DrawBackground()
{
	render_window.setFramerateLimit(60);
	if (!backgroundTexture.loadFromFile("cardiogram.jpg")) //! ¬—“¿¬»“‹ Õ”∆Õ€… ‘ŒÕ!!! !// 
		std::cout << "Can't load Background" << "\n";
	backgroundTexture.setSmooth(true);
	background.setTexture(backgroundTexture);
	render_window.draw(background);

	return 0;
}

int DrawInterface()
{
	DrawBackground();
	DrawButton(); 

	return 0;
}

int DrawButton()
{
auto label = sfg::Label::Create("Hello world");

auto button = sfg::Button::Create("Load");
button->GetSignal(sfg::Widget::OnLeftClick).Connect([label] { label->SetText("Hello SFGUI, pleased to meet you!"); });

auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
box->Pack(label);
box->Pack(button, false);

auto window = sfg::Window::Create();
window->SetTitle("Hellow world");
window->Add(box);

return 0;
}

int main()
{
	while (render_window.isOpen())
	{
		Events();

		render_window.clear(sf::Color::White);
		DrawInterface();
		but.Display(render_window); 

		render_window.display();
	}

	system("pause");

	return 0;
}