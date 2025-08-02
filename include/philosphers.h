/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:48:05 by muhakhan          #+#    #+#             */
/*   Updated: 2025/08/02 20:27:51 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <pthread.h>

# define USAGE_MSG "Usage: ./philosphers number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef pthread_mutex_t	t_mutex;
typedef struct s_vars
{
	long	num_philo;
	long	ttd;
	long	tte;
	long	tts;
	long	eat_num;
}	t_vars;

typedef struct s_philospher
{
	int	test;
}	t_philospher;

typedef enum e_state
{
	THINKING,
	HUNGRY,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

typedef enum e_status
{
	SUCCESS,
	FAILURE
}	t_status;

long	ft_atol(const char *str);
#endif