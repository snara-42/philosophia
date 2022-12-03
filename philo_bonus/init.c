/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:19:25 by subaru            #+#    #+#             */
/*   Updated: 2022/12/04 01:29:16 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_bonus.h"

#define BASE10 "0123456789"

int	parse_args(t_ctx *ctx, int ac, char *av[])
{
	unsigned int	n[6];

	n[5] = 0;
	if (!(ac == 5 || ac == 6)
		|| (!ft_parseuint_base(av[1], &n[1], BASE10) || n[1] < 1)
		|| (!ft_parseuint_base(av[2], &n[2], BASE10) || n[2] < 60)
		|| (!ft_parseuint_base(av[3], &n[3], BASE10) || n[3] < 60)
		|| (!ft_parseuint_base(av[4], &n[4], BASE10) || n[4] < 60)
		|| ((ac == 6 && !ft_parseuint_base(av[5], &n[5], BASE10))
			|| (ac == 5 && n[5]--) || n[5] < 1)
	)
		return (1);
	*ctx = (t_ctx){
		.n_philo = n[1], .time_die = n[2], .time_eat = n[3],
		.time_sleep = n[4], .n_eat = n[5], };
	return (0);
}

#define SEM_FORKS "philo_forks"
#define SEM_PRINT "philo_print"
#define SEM_DONE  "philo_done"

int	init_philos(t_ctx *ctx)
{
	t_philo			*p;
	size_t			i;
	const size_t	n = ctx->n_philo;

	ctx->philos = malloc(sizeof(t_philo) * ctx->n_philo);
	sem_unlink(SEM_FORKS);
	ctx->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, S_IRWXU, n);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	ctx->sem_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, S_IRWXU, 1);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DONE);
	ctx->sem_done = sem_open(SEM_DONE, O_CREAT | O_EXCL, S_IRWXU, 0);
	sem_unlink(SEM_DONE);
	if (!ctx->philos || ctx->sem_forks == SEM_FAILED
		|| ctx->sem_print == SEM_FAILED || ctx->sem_done == SEM_FAILED)
		return (1);
	i = 0;
	while (i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		*p = (t_philo){.i = i + 1, .ctx = ctx, };
		i++;
	}
	return (0);
}

int	destroy_ctx(t_ctx *ctx)
{
	int		ret;

	ret = 0;
	if (sem_close(ctx->sem_forks)
		|| sem_close(ctx->sem_print))
		ret = 1;
	free(ctx->philos);
	return (ret);
}
