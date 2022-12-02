#ifndef PHILO_H
# define PHILO_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_ctx	t_ctx;
typedef struct s_philo	t_philo;

struct s_philo
{
	size_t			i;
	uint64_t		meal_count;
	time_t			time_last_meal;
	pthread_t		th_philo;
	pthread_t		th_doctor;
	pthread_mutex_t	mu_fork;
	pthread_mutex_t	*fork_primary;
	pthread_mutex_t	*fork_secondary;
	t_ctx			*ctx;
};

struct s_ctx
{
	size_t			n_philo;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_sleep;
	uint64_t		n_eat;
	uint64_t		n_is_satisfied;
	uint64_t		n_is_dead;
	pthread_mutex_t	mu_print;
	t_philo			*philos;
};

time_t	get_time(void);
void	msleep(time_t t);

void	*routine_philo(void *arg);
void	*routine_doctor(void *arg);

int		init_ctx(t_ctx *ctx, int ac, char *av[]);

int		create_threads(t_ctx *ctx);
int		detach_threads(t_ctx *ctx);
int		join_threads(t_ctx *ctx);

#endif // PHILO_H
