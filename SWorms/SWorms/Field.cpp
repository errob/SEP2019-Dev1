//------------------------------------------------------------------------------
// Field.cpp
//
// Group: Group 10, study assistant <Thomas Brunner>
//
// Authors: <Robert Ertl> <01114419>
//------------------------------------------------------------------------------
//

#include "stdafx.h"
#include "Field.h"

using Sep::Field;

//------------------------------------------------------------------------------
Field::Field()
{
}

//------------------------------------------------------------------------------
Field::Field(FieldType type) : type_(type)
{
}

//------------------------------------------------------------------------------
Field::~Field()
{
}

//------------------------------------------------------------------------------
char Field::getCharacter(Field::FieldType type)
{
	switch (type)
	{
	case AIR:
		return ' ';
	case EARTH:
		return 'E';
	case WATER:
		return 'W';
	case WORM:
		return '~';
	default:
		return ' ';
	}
}

//------------------------------------------------------------------------
Field::FieldType Field::getType()
{
	return Field::type_;
}

//------------------------------------------------------------------------
// Setter Methods
//
void Field::setType(FieldType type)
{
	type_ =  type;
}