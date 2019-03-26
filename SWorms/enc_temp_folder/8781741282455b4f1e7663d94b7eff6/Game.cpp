#include "stdafx.h"
#include "Game.h"




using Sep::Game;

const std::regex Game::REGEX_SPACE(" +");
const std::regex Game::REGEX_LEADING_WHITESPACE("^ +");
const std::string Game::FIRST_WORD_SIZE = "SIZE:";
const std::string Game::FIRST_WORD_MAP = "MAP:";
const std::string Game::ALLOWED_FIELDS = "AWE:";
const std::string Game::MAGIC_VALUE = "#SWORMS";
const std::string Game::COMMENT_IDENTIFIER = "#";

const int Game::HEIGHT_MIN = 10;
const int Game::HEIGHT_MAX = 80;
const int Game::WIDTH_MIN = 10;
const int Game::WIDTH_MAX = 80;

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
	infile_.open(cfg_file);
	if (!infile_)
	{
		std::cout << "[ERROR] invalid config file\n";
		return -1;
	}
	checkMagicValue();
	return 0;
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

void Game::printMap()
{
	printTop();
	for (auto row = 0; row < getHeight(); row++)
	{
		printLeft(row);
		for (auto column = 0; column < getWidth(); column++)
		{
			std::cout << Field::getCharacter(map_.at(row).at(column));
		}
		printRight(row);
	}
	printBottom();
}

int Game::addWorm(int row, int col) 
{
	char charValue = Field::getCharacter(map_.at(row).at(col));
	bool done = false;
	if (charValue != ' ')
	{
		std::cout << "[ERROR] invalid target\n";
		return -2;
	}
	while(!done)
	{
		if (charValue == ' ')
		{
		row++;
		charValue = Field::getCharacter(map_.at(row).at(col));
		}
		else if (charValue == 'E' || charValue == '~')
		{
		map_.at(row-1).at(col) = Field::FieldType::WORM;
		done = true;
		}
		else 
		{
			return -2;
		}
	}
	return 0;
}

void Game::move(int row, int col, int steps)
{
	char charValue = Field::getCharacter(map_.at(row).at(col));
	if (charValue != '~')
	{
		std::cout << "[WARNING] can't move further\n";
	}
	steps = maxSteps(steps);
	if (steps < 0)
	{
		moveLeft(row, col, -steps);
	}
	else if (steps > 0)
	{
		moveRight(row, col, steps);
	}
}

void Game::printTop() 
{
	//rand oben
	std::cout << "Current Map:\n";
	std::cout << "  ";
	for (auto column = 0; column < getWidth(); column++)
	{
		if (column > 9)
		{
			std::cout << column % 10;
		}
		else
		{
			std::cout << column;
		}
	}
	std::cout << "\n";
}

void Game::printLeft(int row)
{
	if (row > 9) {
		std::cout << row;
	}
	else {
		std::cout << " " << row;
	}
}

void Game::printRight(int row)
{
	if (row > 9) {
		std::cout << row << "\n";
	}
	else {
		std::cout << " " << row << "\n";
	}
}

void Game::printBottom()
{
	std::cout << "  ";
	for (auto column = 0; column < getWidth(); column++)
	{
		if (column > 9)
		{
			std::cout << column % 10;
		}
		else
		{
			std::cout << column;
		}
	}
	std::cout << std::endl;
}

bool Game::checkMagicValue()
{
	std::string magic_value = Game::MAGIC_VALUE;
	std::string first_line;
	std::getline(infile_, first_line);
	if (!first_line.compare(magic_value))
	{
		return readline();
	}
	return true;
}

bool Game::readline()
{
	bool valid_config_file = true;
	bool size_exists = false;
	bool map_exists = false;

	while (std::getline(infile_, line_))
	{
		if (!valid_config_file)
		{
			return false;
		}
		if (line_ == "" || !line_.find_first_of(COMMENT_IDENTIFIER))
		{
			continue;
		}
		else
		{
			line_ = std::regex_replace(line_, REGEX_SPACE, " ");
			line_ = std::regex_replace(line_, REGEX_LEADING_WHITESPACE, "");
			std::string first_word = line_.substr(0, line_.find(' '));
			if (!first_word.compare(FIRST_WORD_SIZE) && !size_exists)
			{
				valid_config_file = sizeSetSuccessfully();
				size_exists = true;
			}
			else if (size_exists &&
				!first_word.compare(FIRST_WORD_MAP))
			{
				map_exists = true;
			}
			else if (map_exists)
			{
				if (line_.find_first_not_of(ALLOWED_FIELDS) != std::string::npos ||
					line_.size() != static_cast<unsigned int>(getWidth()))
				{
					return false;
				}
				helpMap_.push_back(line_);
			}
			else
			{
				return false;
			}
		}
	}
	if (helpMap_.size() != static_cast<unsigned int>(getHeight()))
	{
		return false;
	}
	return mapSetSuccessfully();
}

bool Game::sizeSetSuccessfully()
{
	std::istringstream iss(line_);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };
	if (tokens.size() != 3)
	{
		return false;
	}
		setWidth(std::stoi(tokens.at(1)));
		setHeight(std::stoi(tokens.at(2)));

	if (getHeight() <= HEIGHT_MIN
		|| getHeight() >= HEIGHT_MAX
		|| getWidth() <= WIDTH_MIN
		|| getWidth() >= WIDTH_MAX)
	{
		return false;
	}
	return true;
}

bool Game::mapSetSuccessfully()
{
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
	return true;
}

int Game::maxSteps(int steps)
{
	if (steps >= 3)
	{
		return 3;
	}
	else if (steps <= -3)
	{
		return -3;
	}
	else
		return steps;
}

void Game::checkForPitfalls(int col, int row, bool invert)
{
	int inverter = 1;
	int counter = 1;
	bool done = false;
	if (invert == true)
	{
		inverter = -1;
	}

	char charValueX = Field::getCharacter(map_.at(row).at(col + inverter));
	map_.at(row).at(col-1) = Field::FieldType::AIR;

	while (!done)	
	{
		char charValueY = Field::getCharacter(map_.at(row + counter).at(col + inverter));
		if (charValueY == 'E' || charValueY == '~') 
		{
			map_.at(row+counter-1).at(col+inverter) = Field::FieldType::WORM;
			done = true;
		} else if (charValueY == 'W') 
		{
			done = true;
		}
		counter++;
	}
}

void Game::moveRight(int row, int col, int steps)
{
	char charValueX = 0;
	char charValueY = 0;
	for (int icol = 1; icol <= steps; icol++)
	{
		charValueX = Field::getCharacter(map_.at(row).at(col + icol));
		charValueY = Field::getCharacter(map_.at(row + 1).at(col + icol));
		if (charValueX == ' ' && (charValueY == 'E' || charValueY == '~'))
		{
			map_.at(row).at(col + icol) = Field::FieldType::WORM;
			map_.at(row).at(col + icol - 1) = Field::FieldType::AIR;
		}
		else if (charValueX == ' ' && (charValueY == 'W'))
		{
			map_.at(row).at(col + icol - 1) = Field::FieldType::AIR;
		}
		else if (checkForClimb(row, col, false) == true)
		{
			map_.at(row-1).at(col + icol) = Field::FieldType::WORM;
			map_.at(row).at(col + icol - 1) = Field::FieldType::AIR;
		}
		else if (charValueX == ' ' && (charValueY == ' '))
		{
			checkForPitfalls(col+icol, row, false);
		}
	}
}

void Game::moveLeft(int row, int col, int steps)
{
	char charValueX = 0;
	char charValueY = 0;
	for (int icol = 1; icol <= steps; icol++)
	{
		charValueX = Field::getCharacter(map_.at(row).at(col - icol));
		charValueY = Field::getCharacter(map_.at(row + 1).at(col - icol));
		if (charValueX == ' ' && (charValueY == 'E' || charValueY == '~'))
		{
			map_.at(row).at(col - icol) = Field::FieldType::WORM;
			map_.at(row).at(col - icol + 1) = Field::FieldType::AIR;
		}
		else if (charValueX == ' ' && (charValueY == 'W'))
		{
			map_.at(row).at(col - icol + 1) = Field::FieldType::AIR;
		}
		else if (checkForClimb(row, col, true) == true)
		{
			map_.at(row - 1).at(col - icol) = Field::FieldType::WORM;
			map_.at(row).at(col - icol + 1) = Field::FieldType::AIR;
		}
		else if (charValueX == ' ' && (charValueY == ' '))
		{
			checkForPitfalls(col - icol, row, true);
		}
	}
}

bool Game::checkForClimb(int row, int col, bool invert)
{
	int inverter = 1;
	if (invert == true)
	{
		inverter = -1;
	}
	char charValueX = Field::getCharacter(map_.at(row).at(col+inverter));
	char charValueY = Field::getCharacter(map_.at(row-1).at(col+inverter));
	if ((charValueY == ' ' || charValueY == '~' )&& (charValueX == 'E' || charValueX == '~'))
	{
		return true;
	}
	else 
	{
		return false;
	}	
}