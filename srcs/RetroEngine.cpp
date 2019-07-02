#include "RetroEngine.hpp"
#include "TimeLapse.hpp"


RetroEngine::RetroEngine()
{}

RetroEngine::RetroEngine(RetroEngine const &src)
{
	// SHOULD NOT BE USED
	*this = src;
}

RetroEngine::~RetroEngine()
{}


RetroEngine  &RetroEngine::operator=(RetroEngine const &rhs)
{
	// SHOULD NOT BE USED
	this->_renderer = rhs._renderer;
	this->_player = rhs._player;
	this->_entityList = rhs._entityList;

	return *this;
}


KeyEvent	RetroEngine::retrieveKeyEvent() const
{
	return this->_renderer.retrieveEvent();
}

void		RetroEngine::handleKeyEvent(KeyEvent key)
{
	if (key == keySpace)
		this->_entityList.push(this->_player.shoot());
	else
		this->_updatePlayerPos(key);
}

void		RetroEngine::renderFrame()
{
	// Wipe all the frame
	clear();

	// Replace all entities on the frame
	for (EntityList::iterator it = this->_entityList.begin(); it != this->_entityList.end(); ++it)
	{
		if (!(*it)->isBoss())
			this->_renderer.replaceEntity(*it);
		else
		{
			Boss	*boss = dynamic_cast<Boss *>((*it));
			for (EntityList::iterator bossIt = boss->begin(); bossIt != boss->end(); ++bossIt)
				this->_renderer.replaceEntity(*bossIt);
		}
	}
	this->_renderer.replaceEntity(&this->_player);
	this->_putHp();
	this->_putScore();
	this->_renderer.render();
}

void		RetroEngine::_checkCollisionEntities(EntityList::iterator &entity)
{
	EntityList::iterator it = this->_entityList.begin();
	while (it != this->_entityList.end())
	{
		if ((*entity) != (*it))
		{
			// Check position of the two Entities
			if ((*entity)->getXPos() == (*it)->getXPos() && (*entity)->getYPos() == (*it)->getYPos())
			{
				(*entity)->takeDamage((*it)->getAttackDamage());
				(*it)->takeDamage((*entity)->getAttackDamage());
				this->_player.setScore(20);
				this->_renderer.putScoreObject((*entity)->getXPos(), (*entity)->getYPos() - 1, 20);
			}

			// Is it dead ?
			if ((*it)->getHp() == 0)
			{
				EntityList::iterator tmp = it++;
				delete this->_entityList.pop(tmp);
				continue;
			}
		}
		it++;
	}
}

bool		RetroEngine::_checkCollisionPlayer(EntityList::iterator &entity)
{
	if (this->_player.getXPos() == (*entity)->getXPos() && this->_player.getYPos() == (*entity)->getYPos())
	{
		(*entity)->takeDamage(this->_player.getAttackDamage());
		this->_player.takeDamage((*entity)->getAttackDamage());
		this->_player.setScore(-(*entity)->getAttackDamage());
		this->_renderer.putScoreObject(this->_player.getXPos(), this->_player.getYPos() - 1, -(*entity)->getAttackDamage());
		return this->_player.getHp() > 0;
	}
	return true;
}

void		RetroEngine::_createNewEntities()
{
	// Create New entities (timer are implemented in each functions)

	this->_pushMeteorite();

	if (rand() % 2)
		this->_pushInvader();
	else
		this->_pushBomber();

	this->_pushBoss();
}

bool		RetroEngine::updateEntities()
{
	EntityList::iterator it = this->_entityList.begin();
	while (it != this->_entityList.end())
	{
		// Update Entity pos
		Coord	newCoord = (*it)->move();

		// Out-Of-Bound Check
		if (newCoord.x < 0 || newCoord.x > (int)this->_renderer.getColumnNb()
				|| newCoord.y < 0 || newCoord.y > (int)this->_renderer.getLineNb())
		{
			EntityList::iterator	tmp = it++;
			delete this->_entityList.pop(tmp);
	 		continue;
		}

		// Collision Check between all entities
		// & Collision check with Player
		this->_checkCollisionEntities(it);
		if (!(this->_checkCollisionPlayer(it)))
		{
			this->_putHp();
			return false;// Player is dead!
		}

		// Is it dead ?
		if ((*it)->getHp() == 0)
		{
			EntityList::iterator tmp = it++;
			delete this->_entityList.pop(tmp);
			continue;
		}
		it++;
	}

	// All Entities will shoot now
	this->_makeShoot();

	// Create new Entities
	this->_createNewEntities();

	return true;//Everything is ok
}

void		RetroEngine::_makeShoot()
{
	for (EntityList::iterator it = this->_entityList.begin(); it != this->_entityList.end(); ++it)
	{
		AEntity *tmp = (*it)->shoot();
		if (tmp != NULL)
			this->_entityList.push(tmp);
	}
}

void		RetroEngine::_putHp()
{
	std::string str;

	str = "HP= " + std::to_string(this->_player.getHp());
	this->_renderer.putString(0, FT_LINES, str);
}

void		RetroEngine::_putScore()
{
	std::string str;

	str = "Score= " + std::to_string(this->_player.getScore());
	this->_renderer.putString(10, FT_LINES, str);
}

void		RetroEngine::_pushMeteorite()
{
	static TimeLapse meteoriteTimer;
	int	timeMul = 22.42 / ((meteoriteTimer.getTotalTime()/ 45.) + 1.);
	int	y;

	y = rand() % 16 + 5;// rand value between 5 and 20
	meteoriteTimer.update();

	if (meteoriteTimer.checkTime(FT_TIMELAPSE * timeMul))
		this->_entityList.push(new Meteorite(this->_renderer.getColumnNb(), y));
}

void		RetroEngine::_pushInvader()
{
	static TimeLapse	invaderTimer;
	int			timeMul = 45.73 / ((invaderTimer.getTotalTime()/ 45.) + 1.);
	int y = rand() % 16 + 5;// rand value between 5 and 20

	invaderTimer.update();
	if (invaderTimer.checkTime(FT_TIMELAPSE * timeMul))
		this->_entityList.push(new Invader(this->_renderer.getColumnNb(), y));
}

void		RetroEngine::_pushBomber()
{
	static TimeLapse	bomberTimer;
	int	timeMul = 180.73 / ((bomberTimer.getTotalTime()/ 90.) + 1.);
	int	y;

	y = rand() % 5;
	bomberTimer.update();
	if (bomberTimer.checkTime(FT_TIMELAPSE * timeMul))
	{
		this->_entityList.push(new Bomber(this->_renderer.getColumnNb(), y));
	}
}

void		RetroEngine::_pushBoss()
{
	static TimeLapse bossTimer;
	static double	bossDelay = 45.;

	bossTimer.update();
	if (bossTimer.checkTime(bossDelay))
	{
		this->_entityList.push(new Boss(1150, FT_COLUMNS, FT_LINES / 2));
		if (bossDelay > 11.)
			bossDelay -= 5.;
	}
}

void		RetroEngine::addEntity(AEntity *entity)
{
	this->_entityList.push(entity);
}

void		RetroEngine::_updatePlayerPos(KeyEvent direction)
{
	int		currentY = this->_player.getYPos();
	int		currentX = this->_player.getXPos();

	if (keyUp == direction && (currentY - 1) > 0)
		this->_player.moveVertical(currentY - 1);
	else if (keyDown == direction && (currentY + 1) < FT_LINES)
		this->_player.moveVertical(currentY + 1);
	else if (keyLeft == direction && (currentX - 1) >= 0)
		this->_player.moveHorizontal(currentX - 1);
	else if (keyRight == direction && (currentX + 1) < FT_COLUMNS)
		this->_player.moveHorizontal(currentX + 1);
}