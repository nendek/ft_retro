#include "Rocket.hpp"


Rocket::Rocket(unsigned int xPos, unsigned int yPos, bool direction)
	: AEntity(1, xPos, yPos, '-', FT_RED, direction, 20, 1)
{}

Rocket::Rocket(Rocket const &src)
{
	*this = src;
}

Rocket::~Rocket()
{}


Rocket  &Rocket::operator=(Rocket const &rhs)
{
	this->AEntity::operator=(rhs);
	return *this;
}
