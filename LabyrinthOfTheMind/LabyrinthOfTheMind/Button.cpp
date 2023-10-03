#include "Button.h"

Button::Button(float x, float y, float width, float height, 
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BUTTON_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	int charSize = 24;
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(charSize);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y - charSize / 3 + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);

}

Button::~Button()
{
}

//Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BUTTON_ACTIVE)
		return true;

	return false;
}

//Functions
void Button::update(const sf::Vector2f mousePos)
{
	/*Update booleans for hover and pressed*/

	this->buttonState = BUTTON_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BUTTON_HOVER;

		//Active
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		{
			this->buttonState = BUTTON_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BUTTON_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BUTTON_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BUTTON_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
