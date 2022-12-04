/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:23:06 by subaru            #+#    #+#             */
/*   Updated: 2022/12/04 12:09:59 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	eating(t_philo *p)
{
	take_forks(p);
	print_log(p, "is eating");
	set_last_meal(p);
	msleep(p->ctx->time_eat);
	if (++p->meal_count == p->ctx->n_eat)
		sem_post(p->ctx->sem_done);
	release_forks(p);
}

void	*routine_philo(void *arg)
{
	t_philo *const	p = arg;

	set_last_meal(p);
	if (p->i % 2 == 0)
		usleep(420);
	while (!is_dead_or_satisfied(p->ctx))
	{
		eating(p);
		print_log(p, "is sleeping");
		msleep(p->ctx->time_sleep);
		print_log(p, "is thinking");
	}
	return (NULL);
}

void	*routine_doctor(void *arg)
{
	t_philo *const	p = arg;

	while (!is_dead_or_satisfied(p->ctx))
	{
		msleep(1);
		if (get_time() > get_last_meal(p) + p->ctx->time_die)
		{
			notify_death(p);
			exit(0);
		}
	}
	return (NULL);
}
