#include "philosophers.h"

void	my_usleep(unsigned long long milliseconds, t_philo *philo)
{
	unsigned long long	now;
	unsigned long long	wait_to;

	now = time_now();
	wait_to = milliseconds + now;
	while (now < wait_to && philo->init->death_status == 0)
	{
		usleep(100);
		now = time_now();
	}
}

unsigned long long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000) + (time.tv_usec / 1));
}

unsigned long long	now(t_philo *philo)
{
	return ((time_now() - philo->init->start_time) / 1000);
}
