#include "Bomb.hpp"


Bomb::Bomb(unsigned int xPos, unsigned int yPos, bool direction)
	: AEntity(80, xPos, yPos, 'o', FT_RED, direction, 20, 1)
{}

Bomb::Bomb(Bomb const &src)
{
	*this = src;
}

Bomb::~Bomb()
{}


Bomb  &Bomb::operator=(Bomb const &rhs)
{
	this->AEntity::operator=(rhs);
	return *this;
}

Coord 	Bomb::move()
{
	if (this->_count++ % 5 == 0)
		this->_yPos++;

	Coord result = { this->getXPos(), this->getYPos() };
	return result;
}
