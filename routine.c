/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:23:06 by subaru            #+#    #+#             */
/*   Updated: 2022/12/03 03:23:46 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	*routine_philo(void *arg)
{
	t_philo *const	p = arg;

	if (p->i % 2 == 0)
		usleep(42);
	set_last_meal(p);
	while (!is_dead_or_satisfied(p->ctx))
	{
		pthread_mutex_lock(p->fork_primary);
		print_log(p, "has taken a fork");
		pthread_mutex_lock(p->fork_secondary);
		print_log(p, "has taken a fork");
		print_log(p, "is eating");
		set_last_meal(p);
		msleep(p->ctx->time_eat);
		if (++p->meal_count == p->ctx->n_eat)
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
		if (now > get_last_meal(p) + p->ctx->time_die)
		{
			pthread_mutex_lock(&p->ctx->mu_print);
			printf("%ld %zu %s\n", now, p->i, "died");
			p->ctx->n_is_dead = 1;
			pthread_mutex_unlock(&p->ctx->mu_print);
			break ;
		}
		msleep(1);
	}
	pthread_mutex_unlock(p->fork_secondary);
	pthread_mutex_unlock(p->fork_primary);
	return (NULL);
}
