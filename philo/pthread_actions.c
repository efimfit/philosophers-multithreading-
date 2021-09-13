#include "philosophers.h"

void	death_print(t_philo *philo, char *s)
{
	if (!ft_strcmp(s, "die"))
		printf("%llu\t[%d] is dead, now he is undead\n", now(philo),
			   philo->position + 1);
}

void	my_print(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->init->print);
	if (!ft_strcmp(s, "take a fork") && !philo->init->death_status)
		printf("%llu\t[%d] has taken a fork\n", now(philo), philo->position + 1);
	if (!ft_strcmp(s, "eat") && !philo->init->death_status)
		printf("%llu\t[%d] is eating\n", now(philo), philo->position + 1);
	if (!ft_strcmp(s, "sleep") && !philo->init->death_status)
		printf("%llu\t[%d] is sleeping\n", now(philo), philo->position + 1);
	if (!ft_strcmp(s, "think") && !philo->init->death_status)
		printf("%llu\t[%d] is thinking\n", now(philo), philo->position + 1);
	pthread_mutex_unlock(&philo->init->print);
}

int	take_forks(t_philo *philo)
{
	if (philo->init->death_status)
		return (0);
	pthread_mutex_lock(&philo->init->forks[philo->position]);
	if (philo->init->death_status)
		return (0);
	my_print(philo, "take a fork");
	if (philo->init->death_status)
		return (0);
	if (philo->position == philo->init->n_philo - 1)
		pthread_mutex_lock(&philo->init->forks[0]);
	else if (philo->init->death_status == 0)
		pthread_mutex_lock(&philo->init->forks[philo->position + 1]);
	if (philo->init->death_status)
		return (0);
	my_print(philo, "take a fork");
	return (1);
}

int	eat_put_forks(t_philo *philo)
{
	if (philo->init->death_status)
		return (0);
	pthread_mutex_lock(&philo->mutex);
	my_print(philo, "eat");
	philo->death_time = time_now() + philo->init->time_to_die * 1000;
	philo->eat_count++;
	if (philo->init->times_to_eat == philo->eat_count)
		philo->init->times_have_eaten++;
	my_usleep(philo->init->time_to_eat * 1000, philo);
	pthread_mutex_unlock(&philo->mutex);
	if (philo->init->death_status)
		return (0);
	pthread_mutex_unlock(&philo->init->forks[philo->position]);
	if (philo->position == philo->init->n_philo - 1)
		pthread_mutex_unlock(&philo->init->forks[0]);
	else
		pthread_mutex_unlock(&philo->init->forks[philo->position + 1]);
	return (1);
}

void	sleep_think(t_philo *philo)
{
	if (philo->init->death_status)
		return ;
	my_print(philo, "sleep");
	my_usleep(philo->init->time_to_sleep * 1000, philo);
	if (philo->init->death_status)
		return ;
	my_print(philo, "think");
}
