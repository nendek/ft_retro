#include "ASpaceShip.hpp"


ASpaceShip::ASpaceShip(unsigned int hp, unsigned int xPos, unsigned int yPos, char form, int color, bool direction, unsigned int attackDamage, unsigned int speed)
	: AEntity(hp, xPos, yPos, form, color, direction, attackDamage, speed)
{}

ASpaceShip::ASpaceShip(ASpaceShip const &src)
{
	*this = src;
}

ASpaceShip::~ASpaceShip()
{}


ASpaceShip  &ASpaceShip::operator=(ASpaceShip const &rhs)
{
	this->AEntity::operator=(rhs);
	return *this;
}

AEntity		*ASpaceShip::shoot()
{
	Rocket	*result = new Rocket(this->getXPos() + (this->getDirection() ? -1 : 1), this->getYPos(), this->getDirection());

	return result;
}
