#include "philosophers.h"

int	init_philos(t_init *init, t_philo **philos)
{
	int	i;

	pthread_mutex_init(&init->eat_mutex, NULL);
	pthread_mutex_init(&init->turn_mutex, NULL);
	pthread_mutex_init(&init->print, NULL);
	*philos = (t_philo *)malloc(sizeof(t_philo) * init->n_philo);
	if (!(*philos))
		return (1);
	i = -1;
	while (++i < init->n_philo)
	{
		pthread_mutex_init(&(*philos)[i].mutex, NULL);
		(*philos)[i].init = init;
	}
	return (0);
}

int	start_init(t_init *init, t_philo **philos, char **argv, int argc)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (my_error(2));
	init->n_philo = ft_atoi(argv[1]);
	init->time_to_die = ft_atoi(argv[2]);
	init->time_to_eat = ft_atoi(argv[3]);
	init->time_to_sleep = ft_atoi(argv[4]);
	init->times_to_eat = 0;
	if (argc == 6)
		init->times_to_eat = ft_atoi(argv[5]);
	if (init->time_to_sleep < 60 || init->time_to_eat < 60 || \
			init->time_to_die < 60 || init->n_philo < 1 || \
	init->n_philo > 200 || (init->times_to_eat < 1 && argc == 6))
		return (my_error(3));
	init->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
			init->n_philo);
	if (!init->forks)
		return (my_error(1));
	i = -1;
	while (++i < init->n_philo)
		pthread_mutex_init(&init->forks[i], NULL);
	return (init_philos(init, philos));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
