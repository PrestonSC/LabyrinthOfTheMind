#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/IMMORTAL.ttf");
}

void PlayerGUI::initLevelBar()
{
	float width = 60.f;
	float height = 30.f;
	float x = 20.f;
	float y = 100.f;

	this->levelBarBackground.setSize(sf::Vector2f(width, height));
	this->levelBarBackground.setFillColor(sf::Color::Transparent);
	this->levelBarBackground.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(20);
	this->levelBarText.setPosition(this->levelBarBackground.getPosition().x, this->levelBarBackground.getPosition().y);
}

void PlayerGUI::initExpBar()
{
	float width = 200.f;
	float height = 30.f;
	float x = 20.f;
	float y = 60.f;

	this->expBarMaxWidth = width;

	this->expBarBackground.setSize(sf::Vector2f(width, height));
	this->expBarBackground.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBackground.setPosition(x, y);

	this->expBarForeground.setSize(sf::Vector2f(width, height));
	this->expBarForeground.setFillColor(sf::Color(20, 20, 250, 200));
	this->expBarForeground.setPosition(this->expBarBackground.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(14);
	this->expBarText.setPosition(this->expBarForeground.getPosition().x + 10.f, this->expBarForeground.getPosition().y + 5.f);
}

void PlayerGUI::initHpBar()
{
	float width = 200.f;
	float height = 30.f;
	float x = 20.f;
	float y = 20.f;

	this->hpBarMaxWidth = width;

	this->hpBarBackground.setSize(sf::Vector2f(width, height));
	this->hpBarBackground.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBackground.setPosition(x, y);

	this->hpBarForeground.setSize(sf::Vector2f(width, height));
	this->hpBarForeground.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarForeground.setPosition(this->hpBarBackground.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(14);
	this->hpBarText.setPosition(this->hpBarForeground.getPosition().x + 10.f, this->hpBarForeground.getPosition().y + 5.f);
}

PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->initFont();
	this->initLevelBar();
	this->initExpBar();
	this->initHpBar();
}

PlayerGUI::~PlayerGUI()
{

}

//Functions
void PlayerGUI::updateLevelBar()
{
	this->levelBarString = "Lv " + std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(levelBarString);
}

void PlayerGUI::updateExpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBarForeground.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
			this->expBarForeground.getSize().y
		)
	);

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + "/" + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

void PlayerGUI::updateHpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);

	this->hpBarForeground.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxWidth * percent)), 
			this->hpBarForeground.getSize().y
		)
	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + "/" + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::update(const float& dt)
{
	this->updateLevelBar();
	this->updateExpBar();
	this->updateHpBar();
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBackground);
	target.draw(this->levelBarText);
}

void PlayerGUI::renderExpBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBackground);
	target.draw(this->expBarForeground);
	target.draw(this->expBarText);
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBackground);
	target.draw(this->hpBarForeground);
	target.draw(this->hpBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderLevelBar(target);
	this->renderExpBar(target);
	this->renderHpBar(target);
}
