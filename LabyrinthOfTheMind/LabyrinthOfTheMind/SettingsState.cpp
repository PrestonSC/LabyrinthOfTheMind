#include "stdafx.h"
#include "SettingsState.h"

//Initializer functions
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
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
		throw("ERROR:SETTINGSSTATE::INITBACKGROUND::CANNOT LOAD MAINMENUBG.PNG FILE");
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	try
	{
		this->font.loadFromFile("Fonts/IMMORTAL.ttf");
	}
	catch (const std::exception&)
	{
		throw("ERROR::SETTINGSSTATE::INITFONTS::COULD NOT LOAD FONTS");
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/settingsStateKeyBinds.ini");

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

void SettingsState::initGui()
{
	this->buttons["BACK"] = new gui::Button(
		500.f, 700.f, 150.f, 65.f,
		&this->font, "Back", 50,
		sf::Color(143, 143, 143, 200), sf::Color(150, 250, 250, 250), sf::Color(150, 250, 250, 100),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["APPLY"] = new gui::Button(
		1270.f, 700.f, 150.f, 65.f,
		&this->font, "Apply", 50,
		sf::Color(143, 143, 143, 200), sf::Color(150, 250, 250, 250), sf::Color(150, 250, 250, 100),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	std::vector<std::string> modes_str;

	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(1010, 180, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(font);

	this->optionsText.setPosition(sf::Vector2f(750.f, 185.f));

	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution:\n\nFullscreen:\n\nVsync:\n\nAntialiasing:\n"
	);
}

//Constructors/destructors
SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}


//Accessors

//Functions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	/*Updates all gui elements in the state*/

	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->updateTextAsButton(this->mousePosView);
	}

	//Button functionality
	//Back state
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST REMOVE LATER!!
		this->stateData->gfxSettings->resolution = this->modes[
			this->dropDownLists["RESOLUTION"]->getActiveElementId()
		];

		this->window->create(
			this->stateData->gfxSettings->resolution, 
			this->stateData->gfxSettings->title, 
			sf::Style::Default
		);
	}

	//Dropdown lists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}

	//Dropdown lists functionality
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

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