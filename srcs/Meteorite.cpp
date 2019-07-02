#include "Meteorite.hpp"


Meteorite::Meteorite(unsigned int xPos, unsigned int yPos)
	: AEntity(1, xPos, yPos, 'x', FT_GREEN, true, 10, 1)
{}

Meteorite::Meteorite(Meteorite const &src)
{
	*this = src;
}

Meteorite::~Meteorite()
{}


Meteorite  &Meteorite::operator=(Meteorite const &rhs)
{
	this->AEntity::operator=(rhs);
	return *this;
}
