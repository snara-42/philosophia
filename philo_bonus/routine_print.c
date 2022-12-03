/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:07:35 by subaru            #+#    #+#             */
/*   Updated: 2022/12/04 02:11:30 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_bonus.h"

void	take_forks(t_philo *p)
{
	sem_wait(p->ctx->sem_forks);
	print_log(p, "has taken a fork");
	sem_wait(p->ctx->sem_forks);
	print_log(p, "has taken a fork");
}

void	release_forks(t_philo *p)
{
	sem_post(p->ctx->sem_forks);
	sem_post(p->ctx->sem_forks);
}

void	notify_death(t_philo *p)
{
	time_t			now;

	now = get_time();
	sem_wait(p->ctx->sem_print);
	printf("%ld %zu %s\n", now, p->i, "died");
}

int	print_log(const t_philo *p, const char *s)
{
	time_t	now;
	bool	ret;

	ret = 0;
	sem_wait(p->ctx->sem_print);
	now = get_time();
	printf("%ld %zu %s\n", now, p->i, s);
	sem_post(p->ctx->sem_print);
	return (ret);
}
