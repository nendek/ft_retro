#ifndef METEORITE_HPP
# define METEORITE_HPP

# include "AEntity.hpp"

class Meteorite : public AEntity
{
public:
	Meteorite(unsigned int xPos, unsigned int yPos);
	Meteorite(Meteorite const &src);
	virtual ~Meteorite();

	Meteorite  &operator=(Meteorite const &rhs);

};

#endif
