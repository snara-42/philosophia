/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:23:48 by subaru            #+#    #+#             */
/*   Updated: 2022/12/04 02:11:45 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_dead_or_satisfied(t_ctx *ctx)
{
	bool	ret;

	ret = 0;
	sem_wait(ctx->sem_print);
	sem_post(ctx->sem_print);
	return (ret);
}

time_t	get_last_meal(t_philo *p)
{
	time_t	ret;

	sem_wait(p->ctx->sem_print);
	ret = p->time_last_meal;
	sem_post(p->ctx->sem_print);
	return (ret);
}

void	set_last_meal(t_philo *p)
{
	const time_t	now = get_time();

	sem_wait(p->ctx->sem_print);
	p->time_last_meal = now;
	sem_post(p->ctx->sem_print);
}
//TODO
