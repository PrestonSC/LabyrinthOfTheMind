#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

	this->map.resize(this->maxSize.x, std::vector< std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	try
	{
		this->tileSheet.loadFromFile(this->textureFile);
	}
	catch (const std::exception&)
	{
		throw("ERROR::TILEMAP::TILEMAP()::COULD NOT LOAD TEXTURE!");
	}
	
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

//Functions
void TileMap::addTile(const unsigned x, const unsigned y, 
	const unsigned z, const sf::IntRect& texture_rect)
{
	/* Take x, y, z from mousePosGrid and add a tile if array allows it*/

	if (x < this->maxSize.x && x >= 0 && 
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			/*Add Tile*/

			this->map[x][y][z] = new Tile(
				x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, 
				this->tileSheet, texture_rect 
			);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/* Take x, y, z from mousePosGrid and remove a tile if array allows it*/

	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			/*Remove Tile*/
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/* Saves tilemap to a text file
	
	FORMAT:

	Basic:
	Size x and y
	gridSize
	layers
	texture file

	All Tiles:
	gridPos x and y, Texture rect x and y, collision, type
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if(this->map[x][y][z])
						out_file << this->map[x][y][z]->getAsString() << " "; // MAKE SURE THIS LAST SPACE IS NOT SAVED
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME::" << file_name << "\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME::" << file_name << "\n";
	}

	in_file.close();
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != NULL)
					z->render(target);
			}
		}
	}
}


