#include "Button.h"

Button::Button() :
	but()
{}

int Button::DrawButton()
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