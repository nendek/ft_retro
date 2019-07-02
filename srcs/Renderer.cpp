#include <string>
#include "Renderer.hpp"
#include "ft_retro.hpp"


Renderer::Renderer()
	: _column(FT_COLUMNS), _line(FT_LINES), _window(initscr())
{
	noecho();
	curs_set(false);
	nodelay(stdscr, true);
	keypad(stdscr, true);

	// Init colors
	start_color();
	init_color(COLOR_MAGENTA, 900, 600, 600);
	init_pair(FT_RED, COLOR_RED, COLOR_BLACK);
	init_pair(FT_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(FT_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(FT_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(FT_WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(FT_PINK, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(FT_CYAN, COLOR_CYAN, COLOR_BLACK);
}

Renderer::Renderer(Renderer const &src)
{
	// SHOULD NOT BE USED
	*this = src;
}

Renderer::~Renderer()
{
	delwin(this->_window);
	endwin();
}

Renderer  &Renderer::operator=(Renderer const &rhs)
{
	// SHOULD NOT BE USED
	this->_column = rhs._column;
	this->_line = rhs._line;
	delwin(this->_window);
	this->_window = rhs._window;

	return *this;
}

KeyEvent	Renderer::retrieveEvent() const
{
	return (KeyEvent)getch();
}

void	Renderer::replaceEntity(AEntity *entity)
{
	std::string	entityChar(1, entity->getForm());

	attron(COLOR_PAIR(entity->getColor()));
	mvwprintw(this->_window, (int)entity->getYPos(), (int)entity->getXPos(), entityChar.c_str());
	attroff(COLOR_PAIR(entity->getColor()));
}


void	Renderer::render() const
{
	refresh();
}

unsigned int		Renderer::getLineNb() const
{
	return this->_line;
}

unsigned int		Renderer::getColumnNb() const
{
	return this->_column;
}

WINDOW*				Renderer::getWindow() const
{
	return this->_window;
}

void				Renderer::putScoreObject(int x, int y, int score)
{
	mvwprintw(this->_window, y, x, std::to_string(score).c_str());
}

void				Renderer::putString(int x, int y, std::string str)
{
	mvwprintw(this->_window, y, x, str.c_str());
}
