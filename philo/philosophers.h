#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int					position;
	int					eat_count;
	pthread_mutex_t	 	mutex;
	pthread_t			thread;
	unsigned long long	death_time;
	struct s_init		*init;
}	t_philo;

typedef struct s_init
{
	int					n_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_to_eat;
	int					times_have_eaten;
	pthread_mutex_t		*forks;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		turn_mutex;
	pthread_mutex_t		print;
	int					turn;
	int					death_status;
	unsigned long long	start_time;
}	t_init;

int			ft_atoi(char *nptr);
int			ft_strlen(char *s);
void		ft_putnbr(long long n);
void		ft_bzero(void *s, size_t n);
int			my_error(int n);

int			start_init(t_init *init, t_philo **philos, char **argv, int argc);
int			init_philos(t_init *init, t_philo **philos);
int			ft_strcmp(char *s1, char *s2);

void		my_usleep(unsigned long long milliseconds, t_philo *philo);
uint64_t	time_now(void);
uint64_t	now(t_philo *philo);

int			take_forks(t_philo *philo);
int			eat_put_forks(t_philo *philo);
void		sleep_think(t_philo *philo);
void		my_print(t_philo *philo, char *s);
void		death_print(t_philo *philo, char *s);

#endif