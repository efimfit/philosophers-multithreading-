#include "philosophers.h"

void	*ft_monitor(void *old_init)
{
	t_init	*init;

	init = (t_init *)old_init;
	while (1)
	{
		if (init->is_eating == 0 && time_now() > init->death_time)
		{
			sem_wait(init->is_dead);
			death_print(init, "die");
			sem_post(init->stop);
			return (NULL);
		}
	}
	return (NULL);
}

void	*ft_start(void *old_init)
{
	t_init	*init;

	init = (t_init *)old_init;
	while (1)
	{
		if (!take_forks(init))
			return (NULL);
		if (!eat_put_forks(init))
			return (NULL);
		sleep_think(init);
	}
	return (NULL);
}

void	*eat_till(void *old_init)
{
	int		i;
	t_init	*init;

	i = -1;
	init = (t_init *)old_init;
	while (++i < init->n_philo)
		sem_wait(init->times_have_eaten);
	sem_post(init->stop);
	return (NULL);
}

int	launch_processes(t_init *init, pid_t *pid, int i)
{
	pthread_t	thread;
	pthread_t	monitor;

	init->position = i;
	*pid = fork();
	if (*pid < 0)
		return (0);
	if (*pid == 0)
	{
		init->death_time = time_now() + init->time_to_die * 1000;
		init->eat_count = 0;
		pthread_create(&monitor, NULL, ft_monitor, (void *)init);
		pthread_create(&thread, NULL, ft_start, (void *)init);
		sem_wait(init->stop);
		sem_post(init->stop);
		pthread_detach(monitor);
		pthread_detach(thread);
		exit(0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int			i;
	t_init		init;
	pid_t		*pids;
	pthread_t	eat_count;

	ft_bzero(&init, sizeof(t_init));
	if (start_init(&init, argv, argc))
		return (1);
	pids = (pid_t *)malloc(sizeof(pid_t) * init.n_philo);
	if (!pids)
		return (1);
	init.start_time = time_now();
	i = -1;
	while (++i < init.n_philo)
	{
		if (!launch_processes(&init, &pids[i], i))
			return (1);
	}
	if (init.times_to_eat)
		pthread_create(&eat_count, NULL, eat_till, (void *)&init);
	i = -1;
	while (++i < init.n_philo)
		waitpid(pids[i], 0, 0);
	return (0);
}
