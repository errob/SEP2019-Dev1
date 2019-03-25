#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Field.h"
#include <regex>


namespace Sep {

	//----------------------------------------------------------------------------
	// Game Class
	// class with the game logic
	//
	class Game {
	private:

		//--------------------------------------------------------------------------
		// Attribute for the board width
		//
		int board_width_;

		//--------------------------------------------------------------------------
		// Attribute for the board height
		//
		int board_height_;

		//--------------------------------------------------------------------------
		// Attribute for the board map
		//
		std::vector<std::string> helpMap_;
		std::vector<std::vector<Field::FieldType>> map_;

		//------------------------------------------------------------------------
		// variable to file
		//
		std::ifstream infile_;

		//------------------------------------------------------------------------
		// variable to store current line read in from config file
		//
		std::string line_;
		

	public:
		//--------------------------------------------------------------------------
		// Constructor
		Game();
		//--------------------------------------------------------------------------
		// Constructor
		// @param config contains the configfilename
		//
		//Game(std::string configName);
		//--------------------------------------------------------------------------
		// Destructor
		//
		~Game();

		const static std::regex REGEX_SPACE;
		const static std::regex REGEX_LEADING_WHITESPACE;
		const static std::string Game::FIRST_WORD_SIZE;
		const static std::string Game::FIRST_WORD_MAP;
		const static std::string Game::ALLOWED_FIELDS;
		const static std::string Game::MAGIC_VALUE;
		const static std::string Game::COMMENT_IDENTIFIER;


		const static int Game::HEIGHT_MIN;
		const static int Game::HEIGHT_MAX;
		const static int Game::WIDTH_MIN;
		const static int Game::WIDTH_MAX;
		//--------------------------------------------------------------------------
		// Getter
		//
		int getWidth();

		int getHeight();

		//--------------------------------------------------------------------------
		// Setter
		//
		void setWidth(const int width);

		void setHeight(const int height);

		//--------------------------------------------------------------------------
		// Method to loadConfig
		// prüft config datei, setzt höhe, breite, fieldtypes 
		int loadConfig(std::string cfg_file);

		//--------------------------------------------------------------------------
		// Method to Worm erstellen position (x, y)
		// @param field_type contains the corresponding Field enum type
		// @param x contains x coordinates
		// @param y contains y coordinates
		//
		int addWorm(int row, int col);

		//--------------------------------------------------------------------------
		// Method to print the map
		//
		void printHelperMap();

		//--------------------------------------------------------------------------
		// Method to print the map
		//
		void printMap();

		//--------------------------------------------------------------------------
		// Method to Worm moven position (x, y)
		// @param field_type contains the corresponding Field enum type
		// @param x contains x coordinates
		// @param y contains y coordinates
		//
		void move(int row, int col, int steps);

		/////////////////////////////////////////////////////////////////////////////
		// extra methodes 
		////////////////////////////////////////////////////////////////////////////

		void printTop();
		void printLeft(int row);
		void printRight(int row);
		void printBottom();
		bool checkMagicValue();
		bool readline();
		bool sizeSetSuccessfully();
		bool mapSetSuccessfully();

	};

}
