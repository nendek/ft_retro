#include "AEntity.hpp"


AEntity::AEntity()
{}

AEntity::AEntity(unsigned int hp, unsigned int xPos, unsigned int yPos, char form, int color, bool direction, unsigned int attackDamage, unsigned int speed)
	: _isBoss(false), _xPos(xPos), _yPos(yPos), _hp(hp), _form(form), _color(color), _direction(direction), _attackDamage(attackDamage), _speed(speed)
{}

AEntity::AEntity(AEntity const &src)
{
	*this = src;
}

AEntity::~AEntity()
{}


AEntity  &AEntity::operator=(AEntity const &rhs)
{
	this->_hp = rhs._hp;
	this->_xPos = rhs._xPos;
	this->_yPos = rhs._yPos;
	this->_form = rhs._form;
	this->_color = rhs._color;
	this->_direction = rhs._direction;
	this->_attackDamage = rhs._attackDamage;
	this->_speed = rhs._speed;

	return *this;
}

Coord	AEntity::move()
{
	Coord	newCoord = { this->getXPos(), this->getYPos() };
	newCoord.x += (this->getDirection() ? -1 : 1) * this->_speed;

	this->_xPos = newCoord.x;
	this->_yPos = newCoord.y;

	return newCoord;
}

void	AEntity::takeDamage(int damage)
{
	this->_hp -= (damage > (int)this->_hp ? this->_hp : damage);
}


unsigned int	AEntity::getXPos() const
{
	return this->_xPos;
}

unsigned int	AEntity::getYPos() const
{
	return this->_yPos;
}

char			AEntity::getForm() const
{
	return this->_form;
}

int				AEntity::getColor() const
{
	return this->_color;
}

bool			AEntity::getDirection() const
{
	return this->_direction;
}

unsigned int	AEntity::getAttackDamage() const
{
	return this->_attackDamage;
}

unsigned int	AEntity::getSpeed() const
{
	return this->_speed;
}

unsigned int	AEntity::getHp() const
{
	return this->_hp;
}

bool			AEntity::isBoss() const
{
	return this->_isBoss;
}

AEntity * AEntity::shoot()
{
	return NULL;
}