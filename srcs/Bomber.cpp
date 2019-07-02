#include "Bomber.hpp"

Bomber::Bomber(unsigned int xPos, unsigned int yPos)
	: ASpaceShip(10, xPos, yPos, '8', FT_CYAN, true, 100, 1), _randShoot(rand())
{}

	Bomber::Bomber(Bomber const &src)
: ASpaceShip(src)
{
	*this = src;
}

Bomber::~Bomber()
{}

Bomber  &Bomber::operator=(Bomber const &rhs)
{
	this->_randShoot = rand();
	this->ASpaceShip::operator=(rhs);
	return *this;
}

Coord Bomber::move()
{
	static int fram = 0;
	Coord	newCoord = { this->getXPos(), this->getYPos() };

	if (!(fram % 3))
	{
		newCoord.x += (this->getDirection() ? -1 : 1) * this->getSpeed();
		this->_xPos = newCoord.x;
		this->_yPos = newCoord.y;
	}

	return newCoord;
}

AEntity *Bomber::shoot()
{
	if (this->_randShoot++ % FT_FRAMERATE == 0)
		return new Bomb(this->getXPos(), this->getYPos() + 1, this->getDirection());
	return NULL;
}
