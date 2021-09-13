#include "philosophers.h"

void	death_print(t_init *init, char *s)
{
	sem_wait(init->print);
	if (!ft_strcmp(s, "die"))
		printf("%llu\t[%d] is dead, now he is undead\n", now(init),
			   init->position + 1);
}

void	my_print(t_init *init, char *s)
{
	sem_wait(init->print);
	if (!ft_strcmp(s, "take a fork"))
		printf("%llu\t[%d] has taken a fork\n", now(init), init->position + 1);
	if (!ft_strcmp(s, "eat"))
		printf("%llu\t[%d] is eating\n", now(init), init->position + 1);
	if (!ft_strcmp(s, "sleep"))
		printf("%llu\t[%d] is sleeping\n", now(init), init->position + 1);
	if (!ft_strcmp(s, "think"))
		printf("%llu\t[%d] is thinking\n", now(init), init->position + 1);
	sem_post(init->print);
}

int	take_forks(t_init *init)
{
	sem_wait(init->take_forks);
	sem_wait(init->forks);
	my_print(init, "take a fork");
	sem_wait(init->forks);
	my_print(init, "take a fork");
	sem_post(init->take_forks);
	return (1);
}

int	eat_put_forks(t_init *init)
{
	init->is_eating = 1;
	my_print(init, "eat");
	init->eat_count++;
	if (init->times_to_eat == init->eat_count)
	{
		sem_post(init->times_have_eaten);
		init->eat_count++;
	}
	init->death_time = time_now() + init->time_to_die * 1000;
	my_usleep(init->time_to_eat * 1000, init);
	init->is_eating = 0;
	sem_post(init->forks);
	sem_post(init->forks);
	return (1);
}

void	sleep_think(t_init *init)
{
	my_print(init, "sleep");
	my_usleep(init->time_to_sleep * 1000, init);
	my_print(init, "think");
}
