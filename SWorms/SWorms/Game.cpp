#include "stdafx.h"
#include "Game.h"
#include <sstream>


using Sep::Game;

Game::Game()
{
	board_height_ = 0;
	board_width_ = 0;
}


Game::~Game()
{
}

//----------------------------------
int Game::getWidth()
{
	return board_width_;
}

int Game::getHeight()
{
	return board_height_;
}

void Game::setWidth(const int width)
{
	board_width_ = width;
}

void Game::setHeight(const int height)
{
	board_height_ = height;
}

//---------------------------------------------
int Game::loadConfig(std::string cfg_file)
{
	std::cout << cfg_file+'\n'; 
	infile_.open(cfg_file);
	if (!infile_)
	{
		return false;
	}
	
//todo 
	// prüfen der config datei
	// auslesen der größe
	//rückgabe werte 0 / -1 fehler
	//error invalid config file
	setWidth(40);
	setHeight(11);

	while (std::getline(infile_, line_))
	{
		helpMap_.push_back(line_);
	}

	Game::printHelperMap();
	
	for (int row = 0; row < getHeight(); row++)
	{
		std::vector<Field::FieldType> vector_column;
		for (int column = 0; column < getWidth(); column++)
		{
			if (helpMap_.at(row).at(column) == 'A')
			{
				vector_column.push_back(Field::FieldType::AIR);
			}
			else if (helpMap_.at(row).at(column) == 'E')
			{
				vector_column.push_back(Field::FieldType::EARTH);
			}
			else if (helpMap_.at(row).at(column) == 'W')
			{
				vector_column.push_back(Field::FieldType::WATER);
			}
		}
		Game::map_.push_back(vector_column);
	}

	//testzwecke
	Game::printMap();
	Game::addWorm(3, 3);
	Game::printMap();
	return true;
}
 //zum vergleichen testzwecke
void Game::printHelperMap() 
{

	for (auto row = 0; row < getHeight(); row++)
	{
		for (auto column = 0; column < getWidth(); column++)
		{
			std::cout << helpMap_.at(row).at(column);
		}
		std::cout << std::endl;
	}
}

//todo umrandung des spielfeldes 0 bis 9 \n
void Game::printMap()
{
	for (auto row = 0; row < getHeight(); row++)
	{
		for (auto column = 0; column < getWidth(); column++)
		{
			std::cout << Field::getCharacter(map_.at(row).at(column));
		}
		std::cout << std::endl;
	}
}

int Game::addWorm(int row, int col) 
{
	
	map_.at(row).at(col) = Field::FieldType::WORM;
	//todo
	//schwerkraft
	//check for air/water colissions
	//return 0 / -2 invalid target


	return 0;
}


//todo move 

