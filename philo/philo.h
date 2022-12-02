/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:24:35 by subaru            #+#    #+#             */
/*   Updated: 2022/12/03 03:26:35 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;
struct s_philo
{
	size_t			i;
	uint64_t		meal_count;
	time_t			time_last_meal;
	pthread_t		th_philo;
	pthread_t		th_doctor;
	pthread_mutex_t	mu_fork;
	pthread_mutex_t	*fork_primary;
	pthread_mutex_t	*fork_secondary;
	struct s_ctx	*ctx;
};

typedef struct s_ctx	t_ctx;
struct s_ctx
{
	size_t			n_philo;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_sleep;
	uint64_t		n_eat;
	uint64_t		n_is_satisfied;
	uint64_t		n_is_dead;
	pthread_mutex_t	mu_print;
	struct s_philo	*philos;
};

void	*routine_philo(void *arg);
void	*routine_doctor(void *arg);

bool	is_dead_or_satisfied(t_ctx *ctx);
int		print_log(const t_philo *p, const char *s);
time_t	get_last_meal(t_philo *p);
void	set_last_meal(t_philo *p);
int64_t	mutex_var_add(pthread_mutex_t *mu, uint64_t *p, uint64_t n);

int		create_threads(t_ctx *ctx);
int		detach_threads(t_ctx *ctx);
int		join_threads(t_ctx *ctx);

time_t	get_time(void);
void	msleep(time_t t);

bool	ft_parseint_base(const char *s, int *np, const char *digits);
bool	ft_parseuint_base(const char *s, unsigned int *np, const char *digits);

#endif // PHILO_H
