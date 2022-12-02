/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:23:55 by subaru            #+#    #+#             */
/*   Updated: 2022/12/03 03:24:08 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_ctx *ctx)
{
	size_t	i;
	t_philo	*p;

	i = 0;
	while (i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		if (pthread_create(&p->th_philo, NULL, routine_philo, p)
			|| pthread_create(&p->th_doctor, NULL, routine_doctor, p))
			return (1);
		i++;
	}
	return (0);
}

int	detach_threads(t_ctx *ctx)
{
	size_t	i;
	t_philo	*p;

	i = 0;
	while (i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		if (pthread_detach(p->th_philo)
			|| pthread_detach(p->th_doctor))
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_ctx *ctx)
{
	size_t	i;
	t_philo	*p;

	i = 0;
	while (i < ctx->n_philo)
	{
		p = &ctx->philos[i];
		if (pthread_join(p->th_philo, NULL)
			|| pthread_join(p->th_doctor, NULL))
			return (1);
		i++;
	}
	return (0);
}
