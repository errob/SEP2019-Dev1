//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 10, study assistant <Thomas Brunner>
//
// Authors: <Robert Ertl> <01114419>
//------------------------------------------------------------------------------
//
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include "Field.h"

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
		// Destructor
		//
		~Game();
		//--------------------------------------------------------------------------
		// Constants to minimise Typos
		// Partly reused from Code SEP 2018
		// Group: Group 18622, study assistant Roman Walch
		//
		// Authors: Christina Dionysio (01610877)
		// Johannes Mayerhofer (11739820)
		// Robert Ertl (01114419)
		//
		const static std::regex REGEX_SPACE;
		const static std::regex REGEX_LEADING_WHITESPACE;
		const static std::string FIRST_WORD_SIZE;
		const static std::string FIRST_WORD_MAP;
		const static std::string ALLOWED_FIELDS;
		const static std::string MAGIC_VALUE;
		const static std::string COMMENT_IDENTIFIER;
		const static int HEIGHT_MIN;
		const static int HEIGHT_MAX;
		const static int WIDTH_MIN;
		const static int WIDTH_MAX;
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
		// loads Config data, sets height, width, fieldtypes 
		int loadConfig(std::string cfg_file);
		//--------------------------------------------------------------------------
		// Method to create Worm  (x, y)
		// @param field_type contains the corresponding Field enum type
		// @param row contains y coordinates
		// @param col contains x coordinates
		//
		int addWorm(int row, int col);
		//--------------------------------------------------------------------------
		// Method to print the helper map, testing purpose only
		//
		void printHelperMap();
		//--------------------------------------------------------------------------
		// Method to print the map
		//
		void printMap();
		//--------------------------------------------------------------------------
		// Method to move Worm(x, y)
		// @param field_type contains the corresponding Field enum type
		// @param row contains y coordinates
		// @param col contains x coordinates
		//
		void move(int row, int col, int steps);
		/////////////////////////////////////////////////////////////////////////////
		// extra methodes 
		////////////////////////////////////////////////////////////////////////////
		//--------------------------------------------------------------------------
		// Method to print Top surrounding mpa
		//
		void printTop();
		//--------------------------------------------------------------------------
		// Method to print Left surrounding map
		//
		void printLeft(int row);
		//--------------------------------------------------------------------------
		// Method to print Right surrounding map
		//
		void printRight(int row);
		//--------------------------------------------------------------------------
		// Method to print Bottom surrounding map
		//
		void printBottom();
		//--------------------------------------------------------------------------
		// Method to check magic value in config file
		//
		bool checkMagicValue();
		//--------------------------------------------------------------------------
		// Method to read lines from config file
		//
		bool readline();
		//--------------------------------------------------------------------------
		// Method to set the map size
		//
		bool sizeSetSuccessfully();
		//--------------------------------------------------------------------------
		// Method to set the map fields
		//
		bool mapSetSuccessfully();
		//--------------------------------------------------------------------------
		// Method to deal with max move steps
		// param steps, maximal steps to move
		int maxSteps(int steps);
		//--------------------------------------------------------------------------
		// Method to check for falls
		// @param row contains y coordinates
		// @param col contains x coordinates
		// @param invert, value to determine if left or right moves
		void checkForPitfalls(int row, int col, bool invert);
		//--------------------------------------------------------------------------
		// Method to move Worm to right side
		// @param row contains y coordinates
		// @param col contains x coordinates
		// @param steps contains how muchs teps to take
		void moveRight(int row, int col, int steps);
		//--------------------------------------------------------------------------
		// Method to move Worm to left side
		// @param row contains y coordinates
		// @param col contains x coordinates
		// @param steps contains how muchs teps to take
		void moveLeft(int row, int col, int steps);
		//--------------------------------------------------------------------------
		// Method to check if climbing is available
		// @param row contains y coordinates
		// @param col contains x coordinates
		// @param invert, value to determine if left or right moves
		bool checkForClimb(int col, int row, bool invert);
	};
}
