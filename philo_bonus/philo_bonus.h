/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 03:24:35 by subaru            #+#    #+#             */
/*   Updated: 2022/12/04 01:55:47 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_philo	t_philo;
struct s_philo
{
	size_t			i;
	uint64_t		meal_count;
	time_t			time_last_meal;
	pid_t			pid;
	pthread_t		th_doctor;
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
	pthread_t		th_monitor;
	sem_t			*sem_print;
	sem_t			*sem_forks;
	sem_t			*sem_done;
	struct s_philo	*philos;
};

int		parse_args(t_ctx *ctx, int ac, char *av[]);
int		init_philos(t_ctx *ctx);
int		destroy_ctx(t_ctx *ctx);

void	*routine_philo(void *arg);
void	*routine_doctor(void *arg);

void	take_forks(t_philo *p);
void	release_forks(t_philo *p);
int		print_log(const t_philo *p, const char *s);
void	notify_death(t_philo *p);
bool	is_dead_or_satisfied(t_ctx *ctx);
time_t	get_last_meal(t_philo *p);
void	set_last_meal(t_philo *p);
int64_t	var_add(sem_t *sem, uint64_t *p, uint64_t n);

int		create_processes(t_ctx *ctx);
int		kill_processes(t_ctx *ctx);
int		wait_processes(t_ctx *ctx);

time_t	get_time(void);
void	msleep(time_t t);

bool	ft_parseint_base(const char *s, int *np, const char *digits);
bool	ft_parseuint_base(const char *s, unsigned int *np, const char *digits);

#endif // PHILO_BONUS_H
