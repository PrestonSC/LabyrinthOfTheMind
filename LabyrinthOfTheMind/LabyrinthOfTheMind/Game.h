#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:

	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;
	sf::ContextSettings windowSettings;

	//dt = Delta Time
	sf::Clock dtCLock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	//Initialization
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initStates();
	void initStateData();
	void initKeys();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

#endif
