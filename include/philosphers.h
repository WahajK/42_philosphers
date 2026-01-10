/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:48:05 by muhakhan          #+#    #+#             */
/*   Updated: 2025/10/19 22:02:49 by muhakhan         ###   ########.fr       */
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

# define USAGE_MSG "Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n\
Example: ./philo 5 800 200 200 7\n"
# define INVALID_ARG_MSG "Please enter valid only valid positive numbers \
invalid\n"
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

typedef pthread_mutex_t		t_mutex;
typedef pthread_t			t_thread;
typedef struct s_philospher	t_philospher;
typedef struct s_vars		t_vars;

typedef struct s_philospher
{
	int			id;
	int			num_eaten;
	long		last_ate_time;
	t_thread	thread;
	t_state		current_state;
	t_mutex		*left_chopstick;
	t_mutex		*right_chopstick;
	t_mutex		last_meal_mutex;
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

int		check_all_eaten(t_philospher *philo);
int		is_philo_dead(t_philospher *philo);
long	ft_atol(const char *str);
long	get_current_time(void);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	print_status(t_philospher *philo, char *msg);
int		ft_nan(char *num);
void	parse_data(int argc, char *argv[], t_vars *vars);
int		validate_arguments(int argc, char *argv[], t_vars *vars);

void	free_philosophers(t_vars *vars);
void	free_chopsticks(t_vars *vars);
void	free_mutexes(t_vars *vars);
void	free_resources(t_vars *vars);

int		simulation_ended(t_vars *vars);
void	safely_set_flags(t_vars *vars, int death_flag, int all_eaten);
void	philosphers_janaza(t_vars *vars, int i);
void	*monitor_routine(void *args);
int		is_philo_dead(t_philospher *philo);
int		check_all_eaten(t_philospher *philo);

void	set_chopsticks(t_vars *vars);
int		init_values(t_vars *vars);
void	set_last_ate_time(t_philospher *philo);

void	lock_chopsticks_ordered(t_philospher *philo);
int		essen(t_philospher *philo);
int		schlafen(t_philospher *philo);
int		denken(t_philospher *philo);
void	*philo_routine(void *args);

int		start_simulation(t_vars *vars);
void	handle_single_philo(t_vars *vars);
#endif