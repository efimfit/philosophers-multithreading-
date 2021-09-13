#include "philosophers.h"

int	init_semaphores(t_init *init)
{
	sem_unlink("forks");
	sem_unlink("stop");
	sem_unlink("print");
	sem_unlink("take_forks");
	sem_unlink("times_have_eaten");
	sem_unlink("is_dead");
	init->forks = sem_open("forks", O_CREAT, 0666, init->n_philo);
	init->stop = sem_open("stop", O_CREAT, 0666, 0);
	init->print = sem_open("print", O_CREAT, 0666, 1);
	init->take_forks = sem_open("take_forks", O_CREAT, 0666, 1);
	init->times_have_eaten = sem_open("times_have_eaten", O_CREAT, 0666, 0);
	init->is_dead = sem_open("is_dead", O_CREAT, 0666, 1);
	return (0);
}

int	start_init(t_init *init, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (my_error(2));
	init->n_philo = ft_atoi(argv[1]);
	init->time_to_die = ft_atoi(argv[2]);
	init->time_to_eat = ft_atoi(argv[3]);
	init->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		init->times_to_eat = ft_atoi(argv[5]);
	if (init->time_to_sleep < 60 || init->time_to_eat < 60 || \
			init->time_to_die < 60 || init->n_philo < 1 || \
	init->n_philo > 200 || (init->times_to_eat < 1 && argc == 6))
		return (my_error(3));
	return (init_semaphores(init));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
