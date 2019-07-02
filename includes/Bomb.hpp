#ifndef BOMB_HPP
# define BOMB_HPP

# include "AEntity.hpp"

class Bomb : public AEntity
{

public:
	Bomb(unsigned int xPos, unsigned int yPos, bool direction);
	Bomb(Bomb const &src);
	virtual ~Bomb();

	virtual Coord move();

	Bomb  &operator=(Bomb const &rhs);

private:
	int _count;

};

#endif
