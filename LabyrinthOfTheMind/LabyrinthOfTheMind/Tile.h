#ifndef TILE_H
#define TILE_H

enum TileTypes 
{
	DEFAULT = 0,
	DAMAGING,
	FOREGROUND,
	SLOWING,
	SPEEDING,
	FALL_THROUGH,
	TELEPORT,
	ALWAYS_AT_END
};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	short type;
	bool collision;

public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	//Accessors
	const short& getType() const;
	const bool getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsString() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

#endif