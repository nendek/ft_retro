#include "TimeLapse.hpp"
#include <sys/time.h>


TimeLapse::TimeLapse()
	: _elapsedTime(0.), _totalTime(0.), _lastTime(_getTime())
{}

TimeLapse::TimeLapse(TimeLapse const &src)
{
	*this = src;
}

TimeLapse::~TimeLapse()
{}

TimeLapse  &TimeLapse::operator=(TimeLapse const &rhs)
{
	this->_elapsedTime = rhs._elapsedTime;
	this->_lastTime = rhs._lastTime;
	this->_totalTime = rhs._totalTime;

	return *this;
}

void		TimeLapse::start()
{
	*this = TimeLapse();
}

void		TimeLapse::update()
{
	double	tmp = _getTime();

	this->_elapsedTime += tmp - this->_lastTime;
	this->_totalTime += tmp - this->_lastTime;
	this->_lastTime = tmp;
}

bool		TimeLapse::checkTime(double seconds)
{
	if (this->_elapsedTime >= seconds)
	{
		this->_elapsedTime -= seconds;
		return true;
	}
	return false;
}

bool		TimeLapse::checkTotalTime(double seconds) const
{
	return this->_totalTime >= seconds;
}

//I would LOVE to use std::chrono, but it's C++11
double		TimeLapse::_getTime() const
{
    struct timespec time;

    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double)time.tv_sec + 0.000000001 * (double)time.tv_nsec;
}

double		TimeLapse::getTotalTime() const
{
	return this->_totalTime;
}
