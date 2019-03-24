#pragma once

namespace Sep
{
	//----------------------------------------------------------------------------
	// Field Class
	// class to assign field types 
	//
	class Field
	{
	public:
		//------------------------------------------------------------------------
		// Enumeration of all supported field types
		//
		enum FieldType {AIR, EARTH, WATER, WORM};

	private:

		//------------------------------------------------------------------------
		// variable to store Field Type
		//
		FieldType type_;


	public:

		//------------------------------------------------------------------------
		// Standard Constructor
		//
		Field();
		Field(FieldType type);
		//------------------------------------------------------------------------
		// Destructor
		//
		~Field();
		//------------------------------------------------------------------------
		// Getter Methods
		//
		FieldType getType();
		static char getCharacter(Field::FieldType type);

		//------------------------------------------------------------------------
		// Setter Methods
		//
		void setType(FieldType type);
	};
}
