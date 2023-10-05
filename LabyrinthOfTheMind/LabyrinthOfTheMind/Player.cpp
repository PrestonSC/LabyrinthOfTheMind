#include "Player.h"

//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	
}

//Constructors/Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_DOWN", 10.f, 0, 0, 0, 0, 63, 63);
	this->animationComponent->addAnimation("IDLE_UP", 10.f, 0, 4, 0, 4, 63, 63);
	this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 2, 0, 2, 63, 63);
	this->animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 6, 0, 6, 63, 63);

	this->animationComponent->addAnimation("RUN_DOWN", 10.f, 0, 0, 3, 0, 63, 63);
	this->animationComponent->addAnimation("RUN_DOWN_LEFT", 10.f, 0, 1, 3, 1, 63, 63);
	this->animationComponent->addAnimation("RUN_LEFT", 10.f, 0, 2, 3, 2, 63, 63);
	this->animationComponent->addAnimation("RUN_UP_LEFT", 10.f, 0, 3, 3, 3, 63, 63);
	this->animationComponent->addAnimation("RUN_UP", 10.f, 0, 4, 3, 4, 63, 63);
	this->animationComponent->addAnimation("RUN_UP_RIGHT", 10.f, 0, 5, 3, 5, 63, 63);
	this->animationComponent->addAnimation("RUN_RIGHT", 10.f, 0, 6, 3, 6, 63, 63);
	this->animationComponent->addAnimation("RUN_DOWN_RIGHT", 10.f, 0, 7, 3, 7, 63, 63);
}

Player::~Player()
{
}

//Functions
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	
	if (this->movementComponent->getState(MOVING_DOWN_LEFT))
		this->animationComponent->play("RUN_DOWN_LEFT", dt);
	else if (this->movementComponent->getState(MOVING_DOWN_RIGHT))
		this->animationComponent->play("RUN_DOWN_RIGHT", dt);
	else if (this->movementComponent->getState(MOVING_DOWN))
		this->animationComponent->play("RUN_DOWN", dt);
	else if (this->movementComponent->getState(MOVING_UP_LEFT))
		this->animationComponent->play("RUN_UP_LEFT", dt);
	else if (this->movementComponent->getState(MOVING_UP_RIGHT))
		this->animationComponent->play("RUN_UP_RIGHT", dt);
	else if (this->movementComponent->getState(MOVING_LEFT))
		this->animationComponent->play("RUN_LEFT", dt);
	else if (this->movementComponent->getState(MOVING_RIGHT))
		this->animationComponent->play("RUN_RIGHT", dt);
	else if (this->movementComponent->getState(MOVING_UP))
		this->animationComponent->play("RUN_UP", dt);
	else if (this->movementComponent->getState(IDLE))
	{
		if (this->animationComponent->getLastAnimation() == "IDLE_UP")
			this->animationComponent->play("IDLE_UP", dt);
		else if (this->animationComponent->getLastAnimation() == "IDLE_DOWN")
			this->animationComponent->play("IDLE_DOWN", dt);
		else if (this->animationComponent->getLastAnimation() == "IDLE_RIGHT")
			this->animationComponent->play("IDLE_RIGHT", dt);
		else if (this->animationComponent->getLastAnimation() == "IDLE_LEFT")
			this->animationComponent->play("IDLE_LEFT", dt);
		else if (this->animationComponent->getLastAnimation() == "RUN_DOWN")
			this->animationComponent->play("IDLE_DOWN", dt);
		else if (this->animationComponent->getLastAnimation() == "RUN_DOWN_RIGHT")
			this->animationComponent->play("IDLE_DOWN", dt);
		else if (this->animationComponent->getLastAnimation() == "RUN_DOWN_LEFT")
			this->animationComponent->play("IDLE_DOWN", dt);
		else if (this->animationComponent->getLastAnimation() == "RUN_UP")
			this->animationComponent->play("IDLE_UP", dt);
		else if (this->animationComponent->getLastAnimation() == "RUN_UP_LEFT")
			this->animationComponent->play("IDLE_UP", dt);
		else if (this->animationComponent->getLastAnimation() == "RUN_UP_RIGHT")
			this->animationComponent->play("IDLE_UP", dt);
		else if (this->animationComponent->getLastAnimation() == "RUN_LEFT")
			this->animationComponent->play("IDLE_LEFT", dt);
		else if (this->animationComponent->getLastAnimation() == "RUN_RIGHT")
			this->animationComponent->play("IDLE_RIGHT", dt);

	}
}
