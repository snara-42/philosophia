/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:23:55 by subaru            #+#    #+#             */
/*   Updated: 2022/12/04 12:30:42 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	*routine_monitor(void *arg)
{
	t_ctx *const	ctx = arg;
	size_t			i;

	i = 0;
	while (i++ < ctx->n_philo)
	{
		sem_wait(ctx->sem_done);
	}
	kill_processes(ctx);
	return (NULL);
}

int	create_processes(t_ctx *ctx)
{
	size_t	i;
	t_philo	*p;

	i = 0;
	while (i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		p->pid = fork();
		if (p->pid == -1)
			return (1);
		if (p->pid == 0)
		{
			if (pthread_create(&p->th_doctor, NULL, routine_doctor, p)
				|| pthread_detach(p->th_doctor))
				exit(1);
			routine_philo(p);
		}
		i++;
	}
	if (pthread_create(&ctx->th_monitor, NULL, routine_monitor, p->ctx)
		|| pthread_detach(ctx->th_monitor))
		exit(1);
	return (0);
}

int	kill_processes(t_ctx *ctx)
{
	size_t	i;
	t_philo	*p;
	int		ret;

	i = 0;
	ret = 0;
	while (i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		if (kill(p->pid, SIGINT))
			ret = 1;
		i++;
	}
	return (ret);
}

int	wait_processes(t_ctx *ctx)
{
	size_t	i;
	t_philo	*p;
	int		status;
	int		ret;

	i = 0;
	ret = 0;
	while (i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		if (waitpid(p->pid * 0, &status, 0))
			ret = 1;
		i++;
	}
	return (ret);
}
