#include "philosophers.h"

void	*start(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	pthread_mutex_lock(&philo->init->turn_mutex);
	philo->position = philo->init->turn++;
	pthread_mutex_unlock(&philo->init->turn_mutex);
	philo->death_time = time_now() + philo->init->time_to_die * 1000;
	philo->eat_count = 0;
	while (1)
	{
		if (!take_forks(philo))
			return (NULL);
		if (!eat_put_forks(philo))
			return (NULL);
		sleep_think(philo);
	}
	return (NULL);
}

void	*ft_monitor(void *philo_old)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *) philo_old;
	i = -1;
	while (++i < philo->init->n_philo)
	{
		if (philo->init->times_have_eaten == philo->init->n_philo || \
		time_now() > philo[i].death_time)
		{
			pthread_mutex_lock(&philo->init->print);
			philo->init->death_status = 1;
			if (philo->init->times_have_eaten != philo->init->n_philo)
				death_print(philo, "die");
			pthread_mutex_lock(&philo->mutex);
			return (NULL);
		}
		if (i + 1 == philo->init->n_philo)
			i = -1;
	}
	return (NULL);
}

void	launch_threads(t_init *init, t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	init->start_time = time_now();
	i = -1;
	while (++i < init->n_philo)
	{
		pthread_create(&philo[i].thread, NULL, start, (void *)(&(philo[i])));
		pthread_detach(philo[i].thread);
		usleep(100);
	}
	pthread_create(&monitor, NULL, ft_monitor, philo);
	pthread_join(monitor, NULL);
}

void	clean_mutex(t_init *init, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < init->n_philo)
	{
		pthread_mutex_destroy(&init->forks[i]);
		pthread_mutex_destroy(&philos[i].mutex);
	}
	pthread_mutex_destroy(&init->turn_mutex);
	pthread_mutex_destroy(&init->eat_mutex);
	pthread_mutex_destroy(&init->print);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_init	init;
	t_philo	*philos;

	ft_bzero(&init, sizeof(t_init));
	if (start_init(&init, &philos, argv, argc))
		return (1);
	launch_threads(&init, philos);
	clean_mutex(&init, philos);
	return (0);
}
