#include "Boss.hpp"


Boss::BossBody::BossBody(unsigned int hp, unsigned int xPos, unsigned int yPos, char form)
	: AEntity(hp, xPos, yPos, form, FT_PINK, true, 1, 1), _count(5)
{}

Boss::BossBody::BossBody(BossBody const &src)
{
	*this = src;
}

Boss::BossBody::~BossBody()
{}

Boss::BossBody  &Boss::BossBody::operator=(Boss::BossBody const &rhs)
{
	this->AEntity::operator=(rhs);
	return *this;
}

Coord	Boss::BossBody::move()
{
	Coord	newCoord = { this->getXPos(), this->getYPos() };

	newCoord.y += (this->_count % 20 >= 10 ? 1 : -1);
	if (!(this->_count % 10))
		newCoord.x -= 1;

	this->_xPos = newCoord.x;
	this->_yPos = newCoord.y;

	this->_count++;
	return newCoord;
}

Boss::BossCanon::BossCanon(unsigned int hp, unsigned int xPos, unsigned int yPos)
	: ASpaceShip(hp, xPos, yPos, '<', FT_WHITE, true, 1, 1), _count(5)
{}

Boss::BossCanon::BossCanon(BossCanon const &src)
	: ASpaceShip(src)
{
	*this = src;
}

Boss::BossCanon::~BossCanon()
{}

Boss::BossCanon  &Boss::BossCanon::operator=(Boss::BossCanon const &rhs)
{
	this->ASpaceShip::operator=(rhs);
	return *this;
}

AEntity		*Boss::BossCanon::shoot()
{
	static int i = rand();

	if (i++ % 7)
		return this->ASpaceShip::shoot();
	return NULL;
}

Coord	Boss::BossCanon::move()
{
	Coord	newCoord = { this->getXPos(), this->getYPos() };

	newCoord.y += (this->_count % 20 >= 10 ? 1 : -1);
	if (!(this->_count % 10))
		newCoord.x -= 1;
	this->_count++;

	this->_xPos = newCoord.x;
	this->_yPos = newCoord.y;

	return newCoord;
}



Boss::Boss(unsigned int hp, unsigned int xPos, unsigned int yPos)
	: AEntity(hp, xPos, yPos, 'E', FT_WHITE, true, 1, 1), _size(9)
{
	this->_isBoss = true;

	this->_body.push(new BossCanon(hp / this->_size, xPos-1, yPos-1));
	this->_body.push(new BossBody(hp / this->_size, xPos, yPos-1, '-'));
	this->_body.push(new BossBody(hp / this->_size, xPos+1, yPos-1, '\\'));
	this->_body.push(new BossBody(hp / this->_size, xPos-1, yPos, ' '));
	this->_body.push(new BossBody(hp / this->_size, xPos, yPos, '['));
	this->_body.push(new BossBody(hp / this->_size, xPos+1, yPos, ']'));
	this->_body.push(new BossBody(hp / this->_size, xPos+1, yPos+1, '/'));
	this->_body.push(new BossBody(hp / this->_size, xPos, yPos+1, '-'));
	this->_body.push(new BossCanon(hp / this->_size, xPos-1, yPos+1));//push second canon at the end so i can get it with operator[-1]
}

Boss::Boss(Boss const &src)
{
	*this = src;
}

Boss::~Boss()
{}

Boss  &Boss::operator=(Boss const &rhs)
{
	// SHOUDL NOT BE USED
	this->_body = rhs._body;
	this->_size = rhs._size;

	return *this;
}

Coord	Boss::move()
{
	static int	count = 0;
	Coord	newCoord = { this->getXPos(), this->getYPos() };
	int		i = 0;

	++count;
	if (count % 10)
		return newCoord;

	for (EntityList::iterator it = this->_body.begin(); it != this->_body.end(); ++it)
	{
		if (i != 4)
			(*it)->move();
		else
			newCoord = (*it)->move();
		++i;
	}

	return newCoord;
}

AEntity *Boss::shoot()
{
	int i = rand();

	if (i % 4 == 0)
		return this->_body[0]->shoot();
	else if (i % 4 == 2)
		return this->_body[-1]->shoot();
	return NULL;
}

EntityList::iterator	Boss::begin()
{
	return this->_body.begin();
}

EntityList::iterator	Boss::end()
{
	return this->_body.end();
}