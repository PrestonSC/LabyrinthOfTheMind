#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"

class Player;
class sf::RectangleShape;
class sf::Font;

class PlayerGUI
{
private:
	Player* player;

	sf::Font font;

	//Level Bar
	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBackground;

	//EXP Bar
	std::string expBarString;
	sf::Text expBarText;
	float expBarMaxWidth;
	sf::RectangleShape expBarBackground;
	sf::RectangleShape expBarForeground;

	//HP Bar
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBackground;
	sf::RectangleShape hpBarForeground;

	void initFont();
	void initLevelBar();
	void initExpBar();
	void initHpBar();

public:
	PlayerGUI(Player* player);
	virtual ~PlayerGUI();

	//Functions
	void updateLevelBar();
	void updateExpBar();
	void updateHpBar();
	void update(const float& dt);

	void renderLevelBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

#endif