/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:07:35 by subaru            #+#    #+#             */
/*   Updated: 2022/12/03 20:08:50 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

void	take_forks(t_philo *p)
{
	pthread_mutex_lock(p->fork_primary);
	print_log(p, "has taken a fork");
	pthread_mutex_lock(p->fork_secondary);
	print_log(p, "has taken a fork");
}

void	release_forks(t_philo *p)
{
	pthread_mutex_unlock(p->fork_secondary);
	pthread_mutex_unlock(p->fork_primary);
}

void	notify_death(t_philo *p)
{
	time_t			now;

	now = get_time();
	pthread_mutex_lock(&p->ctx->mu_print);
	if (!p->ctx->n_is_dead)
		printf("%ld %zu %s\n", now, p->i, "died");
	p->ctx->n_is_dead = 1;
	pthread_mutex_unlock(&p->ctx->mu_print);
}

int	print_log(const t_philo *p, const char *s)
{
	time_t	now;
	bool	ret;

	pthread_mutex_lock(&p->ctx->mu_print);
	now = get_time();
	ret = (p->ctx->n_is_dead || p->ctx->n_is_satisfied >= p->ctx->n_philo);
	if (!ret)
		printf("%ld %zu %s\n", now, p->i, s);
	pthread_mutex_unlock(&p->ctx->mu_print);
	return (ret);
}
