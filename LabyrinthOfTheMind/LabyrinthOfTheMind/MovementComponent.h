#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum movement_states {
	IDLE = 0,
	MOVING,
	MOVING_DOWN,
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_UP
};

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;
	
	//Initializer functions


public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, 
		float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	//Functions
	const bool getState(const short unsigned state) const;
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	void move(const float dir_x, const float dir_y, const float dt);
	void update(const float& dt);
};

#endif