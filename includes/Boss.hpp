#ifndef BOSS_HPP
# define BOSS_HPP

# include "AEntity.hpp"
# include "ASpaceShip.hpp"
# include "EntityList.hpp"


class Boss : public AEntity
{
public:

	class BossBody : public AEntity
	{
	public:
		BossBody(unsigned int hp, unsigned int xPos, unsigned int yPos, char form);
		BossBody(BossBody const &src);
		virtual ~BossBody();

		BossBody  &operator=(BossBody const &rhs);

		virtual Coord	move();

	private:
		int	_count;
	};

	class BossCanon : public ASpaceShip
	{
	public:
		BossCanon(unsigned int hp, unsigned int xPos, unsigned int yPos);
		BossCanon(BossCanon const &src);
		virtual ~BossCanon();

		BossCanon  &operator=(BossCanon const &rhs);

		virtual AEntity	*shoot();
		virtual Coord	move();

	private:
		int	_count;
	};

	Boss(unsigned int hp, unsigned int xPos, unsigned int yPos);
	Boss(Boss const &src);
	~Boss();

	Boss  &operator=(Boss const &rhs);

	virtual Coord	move();
	virtual AEntity *shoot();

	EntityList::iterator	begin();
	EntityList::iterator	end();

private:
	EntityList	_body;
	int			_size;
};

#endif // BOSS_HPP