#include "Game.h"

//Static Functions

//Initializer Functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Labyrinth of the Mind");
}

//Constructors/Destructors
Game::Game()
{
    this->initWindow();
}

Game::~Game()
{
	delete this->window;
}


//Functions
void Game::updateDt()
{
    /*Updates the dt variable with the time it takes to update and render 1 frame*/
    this->dt = this->dtCLock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();
}

void Game::render()
{
    this->window->clear();
    
    //Render Items

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}

