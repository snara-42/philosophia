/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:21:22 by subaru            #+#    #+#             */
/*   Updated: 2022/12/03 03:46:41 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "philo.h"

#define BASE10 "0123456789"

int	parse_args(t_ctx *ctx, int ac, char *av[])
{
	unsigned int	n[6];

	if (ac == 5)
		av[5] = "2147483647";
	if (!(ac == 5 || ac == 6)
		|| (!ft_parseuint_base(av[1], &n[1], BASE10) || n[1] < 1)
		|| (!ft_parseuint_base(av[2], &n[2], BASE10) || n[2] < 60)
		|| (!ft_parseuint_base(av[3], &n[3], BASE10) || n[3] < 60)
		|| (!ft_parseuint_base(av[4], &n[4], BASE10) || n[4] < 60)
		|| (!ft_parseuint_base(av[5], &n[5], BASE10) || n[5] < 1)
	)
		return (1);
	*ctx = (t_ctx){
		.n_philo = n[1], .time_die = n[2], .time_eat = n[3],
		.time_sleep = n[4], .n_eat = n[5], };
	return (0);
}

int	init_philos(t_ctx *ctx)
{
	t_philo			*p;
	size_t			i;
	const size_t	n = ctx->n_philo;

	ctx->philos = malloc(sizeof(t_philo) * ctx->n_philo);
	if (!ctx->philos || pthread_mutex_init(&ctx->mu_print, NULL))
		return (1);
	i = 0;
	while (i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		*p = (t_philo){.i = i + 1, .ctx = ctx};
		p->fork_primary = &ctx->philos[(i + (i % 2)) % n].mu_fork;
		p->fork_secondary = &ctx->philos[(i + !(i % 2)) % n].mu_fork;
		if (pthread_mutex_init(&p->mu_fork, NULL))
			return (1);
		i++;
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
	while (ctx->philos && i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		if (pthread_mutex_destroy(&p->mu_fork))
			ret = 1;
		i++;
	}
	if (pthread_mutex_destroy(&ctx->mu_print))
		ret = 1;
	free(ctx->philos);
	return (ret);
}

int	main(int ac, char *av[])
{
	t_ctx	ctx;

	if ((parse_args(&ctx, ac, av) && printf("usage: ./philo "
				"number_of_philosophers time_to_die time_to_eat time_to_sleep"
				" [number_of_times_each_philosopher_must_eat]\n"))
		|| (init_philos(&ctx) && printf("error init\n"))
		|| (create_threads(&ctx) && printf("error creating thread\n"))
		|| (join_threads(&ctx) && printf("error joining thread\n"))
		|| (destroy_ctx(&ctx) && printf("error cleaning up\n"))
	)
		return (1);
	return (0);
}

#ifdef LEAKS

__attribute__((destructor))
void	destructor(void)
{
	system("leaks -q philo 1>&2");
}

#endif
