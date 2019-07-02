#include "Invader.hpp"

Invader::Invader(unsigned int xPos, unsigned int yPos)
	: ASpaceShip(40, xPos, yPos, '<', FT_WHITE, true, 100, 1), _randShoot(rand())
{}

	Invader::Invader(Invader const &src)
: ASpaceShip(src)
{
	*this = src;
}

Invader::~Invader()
{}

Invader  &Invader::operator=(Invader const &rhs)
{
	this->_randShoot = rand();
	this->ASpaceShip::operator=(rhs);
	return *this;
}

Coord Invader::move()
{
	Coord	newCoord = { this->getXPos(), this->getYPos() };
	static int fram = 0;
	unsigned int direction_vertical = rand() % 2;

	if (!(fram % 3))
		newCoord.x += (this->getDirection() ? -1 : 1) * this->getSpeed();

	if (!(fram++ % 10))
	{
		if (direction_vertical && newCoord.y < FT_LINES)
			newCoord.y += 1;
		else if (!direction_vertical && newCoord.y > 0)
			newCoord.y -= 1;
	}

	this->_xPos = newCoord.x;
	this->_yPos = newCoord.y;

	return newCoord;
}

AEntity *Invader::shoot()
{
	if (this->_randShoot++ % FT_FRAMERATE == 0)
		return ASpaceShip::shoot();
	return NULL;
}
