#ifndef ENTITYLIST_HPP
# define ENTITYLIST_HPP

#include <cstddef>
# include "AEntity.hpp"


class EntityList
{
public:

	struct EntityNode
	{
		AEntity		*elem;
		EntityNode	*next;
	};

	struct EntityIterator
	{
		EntityNode		*current;

		EntityIterator	&operator++();
		EntityIterator	operator++(int);
		bool			operator!=(EntityIterator rhs) const;
		bool			operator==(EntityIterator rhs) const;
		AEntity			*operator*();
	};

	typedef EntityList::EntityIterator			iterator;

	EntityList();
	EntityList(EntityList const &src);
	~EntityList();

	EntityList  &operator=(EntityList const &rhs);
	AEntity		*operator[](int i);

	EntityList::iterator	begin();
	EntityList::iterator	end();

	size_t		size() const;
	void		push(AEntity *elem);
	AEntity		*pop(int i);
	AEntity		*pop(iterator &elem);

private:
	size_t		_nodeNb;
	EntityNode	*_entityList;
};

#endif // ENTITYLIST_HPP