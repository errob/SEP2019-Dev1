#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
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
		// Constructor
		// @param config contains the configfilename
		//
		//Game(std::string configName);
		//--------------------------------------------------------------------------
		// Destructor
		//
		~Game();

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
		//void move(int row, int col, int steps);

		/////////////////////////////////////////////////////////////////////////////
		// extra methodes 
		////////////////////////////////////////////////////////////////////////////



	};

}
