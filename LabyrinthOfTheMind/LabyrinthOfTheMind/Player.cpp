#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{
	
}

//Constructors/Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 23.f, 53.f, 45.f, 30.f);
	this->createMovementComponent(350.f, 1500.f, 800.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("ATTACK", 10.f, 3, 0, 3, 7, 215, 118);
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 0, 4, 92, 117);
	this->animationComponent->addAnimation("RUN", 10.f, 1, 0, 1, 7, 92, 117);
}

Player::~Player()
{
}

//Accessors
AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

//Functions
void Player::loseHp(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHp(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseExp(const int exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainExp(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		//Animate and check for animation end
		if (this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(90.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}
		this->animationComponent->play("RUN", dt,
			this->movementComponent->getVelocity().x,
			this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("RUN", dt,
			this->movementComponent->getVelocity().x,
			this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("RUN", dt,
			this->movementComponent->getVelocity().y,
			this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("RUN", dt,
			this->movementComponent->getVelocity().y,
			this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	
	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
