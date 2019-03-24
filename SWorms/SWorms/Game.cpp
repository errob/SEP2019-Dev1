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
	std::cout << "okay\n";

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
	std::cout << "\nrealmap:\n";
	Game::printMap();
	std::cout << "\n add at 10 10:\n";
	Game::addWorm(3, 3);
	std::cout << "\n dingi at 10 10:\n";
	Game::printMap();
	return true;
}

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
	std::cout << "\n hier:" + Field::getCharacter(map_.at(row).at(col));
	char test = Field::getCharacter(map_.at(row).at(col));
	std::cout << "\n hier:"+ test;

	std::cout << Field::getCharacter(map_.at(row).at(col));
	map_.at(row).at(col) = Field::FieldType::WORM;

	return 0;
}


