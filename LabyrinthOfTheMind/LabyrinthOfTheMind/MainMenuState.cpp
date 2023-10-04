#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);

	try
	{
		this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/mainMenuBg.png");
	}
	catch (const std::exception&)
	{
		throw("ERROR::MAINMENUSTATE::INITBACKGROUND::CANNOT LOAD MAINMENUBG.PNG FILE");
	}

	this->background.setTexture(&this->backgroundTexture);

}

void MainMenuState::initFonts()
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

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainMenuStateKeyBinds.ini");

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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(
		885.f, 200.f, 150.f, 50.f,
		&this->font, "New Game", 50,
		sf::Color(143, 143, 143, 200), sf::Color(150, 250, 250, 250), sf::Color(150, 250, 250, 100),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SETTINGS_STATE"] = new Button(
		885.f, 280.f, 150.f, 50.f,
		&this->font, "Settings", 50,
		sf::Color(143, 143, 143, 200), sf::Color(150, 250, 250, 250), sf::Color(150, 250, 250, 100),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EDITOR_STATE"] = new Button(
		885.f, 360.f, 150.f, 50.f,
		&this->font, "Editor", 50,
		sf::Color(143, 143, 143, 200), sf::Color(150, 250, 250, 250), sf::Color(150, 250, 250, 100),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["QUIT_STATE"] = new Button(
		885.f, 460.f, 150.f, 50.f,
		&this->font, "Quit", 50,
		sf::Color(143, 143, 143, 200), sf::Color(150, 250, 250, 250), sf::Color(150, 250, 250, 100),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

//Constructors/Destructors
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	//Updates all the buttons in the state
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Check for new game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Check for quit
	if (this->buttons["QUIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);

	//REMOVE LATER!!!
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(100);
	std::stringstream ss;
	ss << this->mousePosView.x << "" << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}