/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:48:05 by muhakhan          #+#    #+#             */
/*   Updated: 2025/10/15 17:11:38 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <unistd.h>
# include <stddef.h>
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
# define MUTEX_FAILURE "Failed to initialize mutex\n"
# define PTHREAD_JOIN_FAILURE "Failed to join threads\n"
# define RESET   "\033[0m"      // Reset color
# define RED     "\033[31m"     // Red text
# define GREEN   "\033[32m"     // Green text
# define YELLOW  "\033[33m"     // Yellow text
# define BLUE    "\033[34m"     // Blue text
# define CYAN    "\033[36m"     // Cyan text
# define BOLD    "\033[1m"      // Bold text
# define BROWN   "\033[33m"     // Brown (approximated as dark yellow)
# define UNDERLINE "\033[4m"    // Underlined text

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
*                                    Data Structures                          *
******************************************************************************/

typedef pthread_mutex_t	t_mutex;
typedef pthread_t	t_thread;
typedef struct s_philospher t_philospher;
typedef struct s_vars t_vars;

typedef struct s_philospher
{
	int			id;
	int			last_ate_time;
	int			num_eaten;
	t_thread	thread;
	t_state		current_state;
	t_mutex		*left_chopstick;
	t_mutex		*right_chopstick;
	t_vars		*vars;
}	t_philospher;

typedef struct s_vars
{
	int				num_philo;
	int				eat_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	volatile int	death_flag;
	volatile int	all_eaten;
	t_mutex			*chopsticks;
	t_mutex			print_mutex;
	t_mutex			death_mutex;
	t_thread		monitor;
	t_philospher	*philosphers;
}	t_vars;

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

long	ft_atol(const char *str);
long	get_current_time(void);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
#endif