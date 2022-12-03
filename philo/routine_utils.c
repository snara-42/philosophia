/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:23:48 by subaru            #+#    #+#             */
/*   Updated: 2022/12/03 20:08:50 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead_or_satisfied(t_ctx *ctx)
{
	bool	ret;

	pthread_mutex_lock(&ctx->mu_print);
	ret = (ctx->n_is_dead || ctx->n_is_satisfied >= ctx->n_philo);
	pthread_mutex_unlock(&ctx->mu_print);
	return (ret);
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

int64_t	var_add(pthread_mutex_t *mu, uint64_t *p, uint64_t n)
{
	uint64_t	ret;

	pthread_mutex_lock(mu);
	*p += n;
	ret = *p;
	pthread_mutex_unlock(mu);
	return (ret);
}
