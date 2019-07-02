#ifndef RETROENGINE_HPP
# define RETROENGINE_HPP

# include "ft_retro.hpp"
# include "Renderer.hpp"
# include "Meteorite.hpp"
# include "Player.hpp"
# include "Rocket.hpp"
# include "Invader.hpp"
# include "Bomber.hpp"
# include "EntityList.hpp"
# include "Bomb.hpp"
# include "EntityList.hpp"
# include "Boss.hpp"

class RetroEngine
{
public:
	RetroEngine();
	RetroEngine(RetroEngine const &src);
	~RetroEngine();

	RetroEngine  &operator=(RetroEngine const &rhs);

	KeyEvent	retrieveKeyEvent() const;
	void		handleKeyEvent(KeyEvent key);

	void		renderFrame();
	bool		updateEntities();
	void		addEntity(AEntity *entity);

private:
	void		_updatePlayerPos(KeyEvent direction);
	bool		_checkCollisionPlayer(EntityList::iterator &entity);
	void		_checkCollisionEntities(EntityList::iterator &entity);

	void		_createNewEntities();
	void		_pushMeteorite();
	void		_pushInvader();
	void		_pushBomber();
	void		_pushBoss();

	void		_makeShoot();
	void		_putHp();
	void		_putScore();

	void		_gameOver();

	Renderer		_renderer;
	EntityList		_entityList;
	Player			_player;
};


#endif // RETROENGINE_HPP
