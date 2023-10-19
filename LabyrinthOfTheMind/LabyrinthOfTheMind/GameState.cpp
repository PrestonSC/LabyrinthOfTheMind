#include "stdafx.h"
#include "GameState.h"


//Initializer functions
void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0, 
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

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

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/TopDownTileset.png");
	this->tileMap->loadFromFile("Resources/Maps/test.lotmmp");
}

//Constructors/Destructors
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initView();

	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();

	this->initPlayers();
	this->initPlayerGUI();

	this->initTileMap();
}

GameState::~GameState()
{
	delete this->player;
	delete this->pMenu;
	delete this->tileMap;
	delete this->playerGUI;
}

//Functions
void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x), 
		std::floor(this->player->getPosition().y)
	);
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
	{
		this->player->move(0.f, -1.f, dt);
		this->player->gainExp(100);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ARROW_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
		this->player->loseExp(100);
	}
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pMenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player, dt);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused update
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);
		this->updatePlayerGUI(dt);

		this->updateTileMap(dt);

		this->player->update(dt);
	}
	else //Paused update
	{
		this->pMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture, 
		this->player->getGridPosition(static_cast<int>(this->stateData->gridSize))
		);

	this->player->render(this->renderTexture);

	this->tileMap->renderDeferred(this->renderTexture);

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused) //Pause menu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pMenu->render(this->renderTexture);
	}

	//Final render
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
