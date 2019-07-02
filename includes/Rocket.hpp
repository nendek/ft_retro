#ifndef ROCKET_HPP
# define ROCKET_HPP

# include "AEntity.hpp"

class Rocket : public AEntity
{
public:
	Rocket(unsigned int xPos, unsigned int yPos, bool direction);
	Rocket(Rocket const &src);
	virtual ~Rocket();

	Rocket  &operator=(Rocket const &rhs);

};

#endif
