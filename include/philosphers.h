/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:48:05 by muhakhan          #+#    #+#             */
/*   Updated: 2025/08/06 20:05:19 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

# define USAGE_MSG "Usage: ./philosphers number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define INVALID_ARG_MSG "Please enter valid only valid positive numbers\n"
# define ZERO_PHILO_MSG "Number of philosphers must be greater than 1\n"
typedef pthread_mutex_t	t_mutex;
typedef struct s_vars
{
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				eat_num;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philospher	*philosphers;
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