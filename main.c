#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				i;
	uint64_t		eat_count;
	pthread_mutex_t	fork_;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_t		thread;
	t_data			*data;
};

struct s_data
{
	size_t			n_philo;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	uint64_t		n_eat;
	pthread_mutex_t	mu;
	t_philo			*philos;
};

bool	init_data(t_data *data, int ac, char *av[]) //TODO
{
	if (!(ac == 5 || ac == 6))
		return (false);
	*data = (t_data){};
	sscanf(av[1], "%lu", &data->n_philo);
	sscanf(av[2], "%llu", &data->time_die);
	sscanf(av[3], "%llu", &data->time_eat);
	sscanf(av[4], "%llu", &data->time_sleep);
	if (ac == 6)
		sscanf(av[5], "%llu", &data->n_eat);
	else
		data->n_eat = -1;
	pthread_mutex_init(&data->mu, NULL);
	data->philos = malloc(sizeof(t_philo) * data->n_philo);

	size_t	i;
	i = 0;
	while (i < data->n_philo)
	{
		t_philo	*philo = &data->philos[i];
		*philo = (t_philo){
			.i = i,
			.data = data};
		pthread_mutex_init(&philo->fork_, NULL);
		philo->fork_l = &data->philos[(i + 0) % data->n_philo].fork_;
		philo->fork_r = &data->philos[(i + 1) % data->n_philo].fork_;
		i++;
	}
	return (true);
}

time_t	get_ms(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

void	msleep(time_t ms)
{
	const time_t	start = get_ms();
	while (get_ms() < start + ms)
	{
		usleep(100);
	}
}

void	*f_philo(void *arg)
{
	t_philo *const	philo = arg;

	pthread_mutex_lock((pthread_mutex_t *[]){philo->fork_l, philo->fork_r}[philo->i % 2 == 0]);
	printf("%ld %d %s\n", get_ms(), philo->i, "has taken a fork");
	pthread_mutex_lock((pthread_mutex_t *[]){philo->fork_l, philo->fork_r}[philo->i % 2 == 1]);
	printf("%ld %d %s\n", get_ms(), philo->i, "has taken a fork");
	printf("%ld %d %s\n", get_ms(), philo->i, "is eating");
	msleep(philo->data->time_eat);
	philo->eat_count += 1;
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	printf("%ld %d %s\n", get_ms(), philo->i, "is sleeping");
	msleep(philo->data->time_sleep);
	printf("%ld %d %s\n", get_ms(), philo->i, "is thinking");
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_data	data;
	size_t	i;

	if (!init_data(&data, ac, av))
		return (!!printf("error\n"));
	i = 0;
	while (i < data.n_philo)
	{
		pthread_create(&data.philos[i].thread, NULL, f_philo, &data.philos[i]);
		i++;
	}
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
}
