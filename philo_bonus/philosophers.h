#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>

typedef struct s_init
{
	int			n_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_to_eat;
	int			death_status;
	uint64_t	start_time;
	sem_t		*forks;
	sem_t		*is_dead;
	sem_t		*stop;
	sem_t		*print;
	sem_t		*take_forks;
	sem_t		*times_have_eaten;
	uint64_t	death_time;
	int			position;
	int			eat_count;
	int			is_eating;

}	t_init;

int			ft_atoi(char *nptr);
int			ft_strlen(char *s);
void		ft_putnbr(long long n);
void		ft_bzero(void *s, size_t n);
int			my_error(int n);

int			start_init(t_init *init, char **argv, int argc);
int			ft_strcmp(char *s1, char *s2);

void		my_usleep(unsigned long long microseconds, t_init *init);
uint64_t	time_now(void);
uint64_t	now(t_init *init);

int			take_forks(t_init *init);
int			eat_put_forks(t_init *init);
void		sleep_think(t_init *init);
void		my_print(t_init *init, char *s);
void		death_print(t_init *init, char *s);

#endif