#ifndef TIMELAPSE_HPP
# define TIMELAPSE_HPP

class TimeLapse
{
public:
	TimeLapse();
	TimeLapse(TimeLapse const &src);
	~TimeLapse();

	TimeLapse  &operator=(TimeLapse const &rhs);

	void		start();
	void		update();
	bool		checkTime(double seconds);
	bool		checkTotalTime(double seconds) const;
	double		getTotalTime() const;

private:
	double		_getTime() const;
	double		_elapsedTime;
	double		_totalTime;
	double		_lastTime;
};

#endif // TIMELAPSE_HPP
