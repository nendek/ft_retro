#include "EntityList.hpp"


EntityList::EntityIterator	&EntityList::EntityIterator::operator++()
{
	current = current->next;
	return *this;
}

EntityList::EntityIterator	EntityList::EntityIterator::operator++(int)
{
	EntityList::EntityIterator result(*this);
	this->current = this->current->next;
	return result;
}

AEntity		*EntityList::EntityIterator::operator*()
{
	return this->current->elem;
}

bool		EntityList::EntityIterator::operator!=(EntityIterator rhs) const
{
	return this->current != rhs.current;
}

bool		EntityList::EntityIterator::operator==(EntityIterator rhs) const
{
	return this->current == rhs.current;
}



EntityList::EntityList()
	: _nodeNb(0), _entityList(NULL)
{}

EntityList::EntityList(EntityList const &src)
{
	*this = src;
}

EntityList::~EntityList()
{
	EntityList::iterator it = this->begin();
	while (it != this->end())
	{
		EntityList::iterator tmp(it);
		delete *it;
		delete it.current;
		it = ++tmp;
	}
}


EntityList  &EntityList::operator=(EntityList const &rhs)
{
	// we first delete the previous list
	EntityList::iterator it = this->begin();
	while (it != this->end())
	{
		EntityList::iterator tmp(it);
		delete *it;
		delete it.current;
		it = ++tmp;
	}

	this->_nodeNb = rhs._nodeNb;
	this->_entityList = rhs._entityList;

	return *this;
}

AEntity		*EntityList::operator[](int i)
{
	EntityList::iterator it = this->begin();

	if (i == -1)
		i = this->_nodeNb - 1;

	if (i < 0 || (size_t)i >= this->_nodeNb)
		return NULL;

	while (i > 0)
	{
		++it;
		--i;
	}

	return *it;
}


size_t			EntityList::size() const
{
	return this->_nodeNb;
}

void			EntityList::push(AEntity *elem)
{
	EntityList::iterator it = this->begin();
	EntityList::EntityNode	newNode;

	newNode.elem = elem;
	newNode.next = NULL;

	if (it == this->end() || this->_nodeNb == 0)
		this->_entityList = new EntityList::EntityNode(newNode);
	else
	{
		for (unsigned int i = 0; i < this->_nodeNb - 1; ++i)
			++it;
		it.current->next = new EntityList::EntityNode(newNode);
	}
	this->_nodeNb++;
}

AEntity			*EntityList::pop(int index)
{
	EntityList::iterator	it = this->begin();
	AEntity					*result = this->operator[](index);

	if (result == NULL)//no elem in list
		return NULL;

	this->_nodeNb--;
	if (index == 0)//first elem
	{
		++it;
		delete this->_entityList;
		this->_entityList = it.current;
		return result;
	}

	while (index > 1)
	{
		++it;
		--index;
	}

	it.current->next = it.current->next->next;
	++it;
	delete it.current;
	return result;
}

AEntity			*EntityList::pop(EntityList::iterator &elem)
{
	EntityList::iterator	it = this->begin();
	AEntity					*result = *elem;

	if (result == NULL)//no elem in list
		return NULL;

	this->_nodeNb--;
	if (elem == it)//first elem
	{
		++it;
		delete this->_entityList;
		this->_entityList = it.current;
		return result;
	}

	EntityList::iterator	prevIt;
	while (it != elem)
		prevIt = it++;

	prevIt.current->next = prevIt.current->next->next;
	delete elem.current;
	return result;
}

EntityList::iterator	EntityList::begin()
{
	EntityList::iterator	result;

	result.current = this->_entityList;
	return result;
}

EntityList::iterator	EntityList::end()
{
	EntityList::iterator	result;

	result.current = NULL;
	return result;
}