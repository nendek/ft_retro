#ifndef IENTITY_HPP
# define IENTITY_HPP

# include "Coord.hpp"

class IEntity
{
public:
	virtual ~IEntity() {}

	virtual Coord	move() = 0;//return the new position
	virtual void	takeDamage(int damage) = 0;

};

#endif // IENTITY_HPP
