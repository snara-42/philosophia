/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:21:22 by subaru            #+#    #+#             */
/*   Updated: 2022/12/03 11:39:11 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

#define MSG1 "usage: ./philo number_of_philosophers time_to_die time_to_eat " 
#define MSG2 "time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

int	main(int ac, char *av[])
{
	t_ctx	ctx;

	if ((parse_args(&ctx, ac, av) && printf(MSG1 MSG2))
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
