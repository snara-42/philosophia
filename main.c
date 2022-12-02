#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "philo.h"

int	init_ctx(t_ctx *ctx, int ac, char *av[]) //TODO
{
	if (!(ac == 5 || ac == 6))
		return (1);
	*ctx = (t_ctx){};
	sscanf(av[1], "%lu", &ctx->n_philo);
	sscanf(av[2], "%ld", &ctx->time_die);
	sscanf(av[3], "%ld", &ctx->time_eat);
	sscanf(av[4], "%ld", &ctx->time_sleep);
	ctx->n_eat = -1;
	if (ac == 6)
		sscanf(av[5], "%llu", &ctx->n_eat);
	pthread_mutex_init(&ctx->mu_print, NULL);
	ctx->philos = malloc(sizeof(t_philo) * ctx->n_philo);

	size_t	i;
	t_philo	*p;

	i = -1;
	while (++i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		*p = (t_philo){.i = i + 1, .ctx = ctx,};
		pthread_mutex_init(&p->mu_fork, NULL);
		p->fork_primary = &ctx->philos[(i + !(i % 2)) % ctx->n_philo].mu_fork;
		p->fork_secondary = &ctx->philos[(i + (i % 2)) % ctx->n_philo].mu_fork;
	}
	return (0);
}

int	destroy_ctx(t_ctx *ctx)
{
	size_t	i;
	t_philo	*p;
	int		ret;

	i = 0;
	ret = 0;
	while (i < ctx->n_philo)
	{
		if (pthread_mutex_destroy(&ctx->philos[i].mu_fork))
			ret = 1;
		i++;
	}
	if (pthread_mutex_destroy(&ctx->mu_print))
		ret = 1;
	free(ctx->philos);
	return (ret);
}

bool	is_dead_or_satisfied(t_ctx *ctx)
{
	bool	ret;

	pthread_mutex_lock(&ctx->mu_print);
	ret = (ctx->n_is_dead || ctx->n_is_satisfied >= ctx->n_philo);
	pthread_mutex_unlock(&ctx->mu_print);
	return (ret);
}

int	print_log(const t_philo *p, const char *s)
{
	const time_t	now = get_time();

	if (is_dead_or_satisfied(p->ctx))
		return (1);
	pthread_mutex_lock(&p->ctx->mu_print);
	printf("%ld %zu %s\n", now, p->i, s);
	pthread_mutex_unlock(&p->ctx->mu_print);
	return (0);
}

time_t	get_last_meal(t_philo *p)
{
	time_t	ret;

	pthread_mutex_lock(&p->ctx->mu_print);
	ret = p->time_last_meal;
	pthread_mutex_unlock(&p->ctx->mu_print);
	return (ret);
}

void	set_last_meal(t_philo *p)
{
	const time_t	now = get_time();

	pthread_mutex_lock(&p->ctx->mu_print);
	p->time_last_meal = now;
	pthread_mutex_unlock(&p->ctx->mu_print);
}

uint64_t	mutex_var_add(pthread_mutex_t *mu, uint64_t *p, uint64_t n)
{
	uint64_t	ret;

	pthread_mutex_lock(mu);
	*p += n;
	ret = *p;
	pthread_mutex_unlock(mu);
	return (ret);
}

void	*routine_philo(void *arg)
{
	t_philo *const	p = arg;

	set_last_meal(p);
	while (!is_dead_or_satisfied(p->ctx))
	{
		pthread_mutex_lock(p->fork_primary);
		print_log(p, "has taken a fork");
		pthread_mutex_lock(p->fork_secondary);

		print_log(p, "is eating");
		set_last_meal(p);
		msleep(p->ctx->time_eat);
		if (++p->meal_count >= p->ctx->n_eat)
			mutex_var_add(&p->ctx->mu_print, &p->ctx->n_is_satisfied, 1);

		pthread_mutex_unlock(p->fork_secondary);
		pthread_mutex_unlock(p->fork_primary);

		print_log(p, "is sleeping");
		msleep(p->ctx->time_sleep);

		print_log(p, "is thinking");
	}
	return (NULL);
}

void	*routine_doctor(void *arg)
{
	t_philo *const	p = arg;
	time_t			now;

	msleep(1);
	while (!is_dead_or_satisfied(p->ctx))
	{
		now = get_time();
		if (now > get_last_meal(p) + p->ctx->time_die) //
		{
			pthread_mutex_lock(&p->ctx->mu_print);
			printf("%ld %zu %s\n", now, p->i, "died");
			p->ctx->n_is_dead = 1;
			pthread_mutex_unlock(&p->ctx->mu_print);
		}
		msleep(1);
	}
	return (NULL);
}


int	main(int ac, char *av[])
{
	t_ctx	ctx;

	if ((init_ctx(&ctx, ac, av) && printf("error init\n"))
			|| (create_threads(&ctx) && printf("error creating thread\n"))
			|| (join_threads(&ctx) && printf("error joining thread\n"))
	   )
		return (1);
	return (0);
}
