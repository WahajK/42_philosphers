/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:48:05 by muhakhan          #+#    #+#             */
/*   Updated: 2025/08/12 18:27:43 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

/******************************************************************************
*                                     Macros                                  *
******************************************************************************/

# define USAGE_MSG "Usage: ./philosphers number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n\
Example: ./philosphers 5 800 200 200 7\n"
# define INVALID_ARG_MSG "Please enter valid only valid positive numbers\n"
# define ZERO_PHILO_MSG "Number of philosphers must be greater than 1\n"
# define PTHREAD_FAILURE "Failed to initialize threads\n"

/******************************************************************************
*                                    Data Structures                          *
******************************************************************************/

typedef pthread_mutex_t	t_mutex;

typedef struct s_philospher
{
	t_mutex	*left_chopstick;
	t_mutex	*right_chopstick;
	int		test;
}	t_philospher;

typedef struct s_vars
{
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				eat_num;
	t_mutex			*chopsticks;
	t_mutex			*left_chopstick;
	t_mutex			*right_chopstick;
	t_mutex			print_mutex;
	t_philospher	*philosphers;
}	t_vars;

/******************************************************************************
*                                     Enums                                   *
******************************************************************************/

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

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

long	ft_atol(const char *str);
#endif