#include "stdafx.h"
#include "GameState.h"

//Initializer functions
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gameStateKeyBinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initFonts()
{
	try
	{
		this->font.loadFromFile("Fonts/IMMORTAL.ttf");
	}
	catch (const std::exception&)
	{
		throw("ERROR::MAINMENUSTATE::INITFONTS::COULD NOT LOAD FONTS");
	}
}

void GameState::initTextures()
{
	try
	{
		this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/player-sheet.png");
	}
	catch (const std::exception&)
	{
		throw("ERROR::GAMESTATE::INITTEXTURES::COULD NOT LOAD TEXTURE");
	}
}

void GameState::initPauseMenu()
{
	this->pMenu = new PauseMenu(*this->window, this->font);

	this->pMenu->addButton("QUIT", 800.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(960, 540, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/Images/Tiles/tileMap1.png");
}

//Constructors/Destructors
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();

	this->initPlayers();

	this->initTileMap();
}

GameState::~GameState()
{
	delete this->player;
	delete this->pMenu;
	delete this->tileMap;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) 
		&& this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ARROW_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ARROW_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ARROW_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ARROW_DOWN"))))
		this->player->move(0.f, 1.f, dt);	
}

void GameState::updatePauseMenuButtons()
{
	if (this->pMenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused update
	{
		this->updatePlayerInput(dt);

		this->player->update(dt);
	}
	else //Paused update
	{
		this->pMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//this->map.render(*target);

	this->player->render(*target);

	if (this->paused) //Pause menu render
	{
		this->pMenu->render(*target);
	}
}
