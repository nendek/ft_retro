#ifndef RENDERER_HPP
# define RENDERER_HPP

# include <string>
# include <ncurses.h>
# include "KeyEvent.hpp"
# include "AEntity.hpp"

class Renderer
{
public:

	Renderer();
	~Renderer();
	Renderer(Renderer const &src);
	Renderer  &operator=(Renderer const &rhs);

	KeyEvent	retrieveEvent() const;
	void		render() const;
	void		replaceEntity(AEntity *entity);
	void		putScoreObject(int x, int y, int score);
	void		putString(int x, int y, std::string str);

	unsigned int		getLineNb() const;
	unsigned int		getColumnNb() const;
	WINDOW				*getWindow() const;


private:

	unsigned int		_column;
	unsigned int		_line;
	WINDOW				*_window;
};

#endif // RENDERER_HPP
