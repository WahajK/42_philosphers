/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:47:04 by muhakhan          #+#    #+#             */
/*   Updated: 2025/10/15 18:57:19 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosphers.h"

int	ft_nan(char *num)
{
	if (*num == '+')
		num++;
	while (*num)
	{
		if (*num >= '0' && *num <= '9')
			num++;
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

void	parse_data(int argc, char *argv[], t_vars *vars)
{
	int	i;

	i = 0;
	vars->num_philo = (int) ft_atol(argv[++i]);
	vars->time_to_die = ft_atol(argv[++i]);
	vars->time_to_eat = ft_atol(argv[++i]);
	vars->time_to_sleep = ft_atol(argv[++i]);
	if (argc == 6)
		vars->eat_num = (int) ft_atol(argv[++i]);
	else
		vars->eat_num = -1;
}

int	simulation_ended(t_vars *vars)
{
	int	ended;

	pthread_mutex_lock(&vars->death_mutex);
	ended = vars->death_flag;
	pthread_mutex_unlock(&vars->death_mutex);
	return (ended);
}

void	*check_death(void *args)
{
	t_vars *vars;

	vars = (t_vars *) args;
	while (!simulation_ended(vars))
	{
		continue;
	}
	return (NULL);
}

void	print_status(t_philospher *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->vars->print_mutex);
	if (!simulation_ended(philo->vars))
	{
		timestamp = get_current_time() - philo->vars->start_time;
		printf("%s%ld %s%d %s%s\n",
			CYAN, timestamp, BOLD, philo->id, msg, RESET);
	}
	pthread_mutex_unlock(&philo->vars->print_mutex);
}

int	validate_arguments(int argc, char *argv[], t_vars *vars)
{
	int	i;

	i = 1;
	while (i < argc)
		if (ft_nan(argv[i++]))
			return (printf(INVALID_ARG_MSG), FAILURE);
	parse_data(argc, argv, vars);
	if (vars->num_philo < 1)
		return (printf(ZERO_PHILO_MSG), FAILURE);
	return (SUCCESS);
}

void	set_chopsticks(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_philo)
	{
		if (i == vars->num_philo - 1)
		{
			vars->philosphers[i].right_chopstick = &vars->chopsticks[i];
			vars->philosphers[i].left_chopstick = &vars->chopsticks[0];
		}
		else
		{
			vars->philosphers[i].right_chopstick = &vars->chopsticks[i];
			vars->philosphers[i].left_chopstick = &vars->chopsticks[i + 1];
		}
		i++;
	}
}

int	init_values(t_vars *vars)
{
	int	i;

	vars->philosphers = ft_calloc(sizeof(t_philospher), vars->num_philo);
	vars->chopsticks = malloc(sizeof(t_mutex) * vars->num_philo);
	vars->start_time = get_current_time();
	if (!vars->philosphers || !vars->chopsticks)
		return (FAILURE);
	if (pthread_mutex_init(&vars->print_mutex, NULL) != 0
		|| pthread_mutex_init(&vars->death_mutex, NULL) != 0)
		return (printf(MUTEX_FAILURE), FAILURE);
	i = -1;
	while (++i < vars->num_philo)
	{
		vars->philosphers[i].vars = vars;
		if (pthread_mutex_init(&vars->chopsticks[i], NULL) != 0)
			return (printf(MUTEX_FAILURE), FAILURE);
		vars->philosphers[i].id = i;
	}
	set_chopsticks(vars);
	return (SUCCESS);
}

long	get_current_time(void)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

int	essen(t_philospher *philo)
{
	philo->current_state = EATING;
	pthread_mutex_lock(philo->right_chopstick);
	pthread_mutex_lock(philo->left_chopstick);
	print_status(philo, "is eating");
	usleep(philo->vars->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_chopstick);
	pthread_mutex_unlock(philo->left_chopstick);
	return (SUCCESS);
}

int	schlafen(t_philospher *philo)
{
	philo->current_state = SLEEPING;
	print_status(philo, "is sleeping");
	usleep(philo->vars->time_to_sleep * 1000);
	return (SUCCESS);
}

int	denken(t_philospher *philo)
{
	philo->current_state = THINKING;
	print_status(philo, "is thinking");
	return (SUCCESS);
}

void	*philo_routine(void *args)
{
	t_philospher	*philo;

	philo = (t_philospher *)args;
	if (philo->id % 2 == 0)
		usleep(5);
	while (!simulation_ended(philo->vars))
	{
		if (essen(philo))
			return (NULL);
		if (schlafen(philo))
			return (NULL);
		if (denken(philo))
			return (NULL);
	}
	return (NULL);
}

int	start_simulation(t_vars *vars)
{
	int	i;

	i = -1;
	if (pthread_create(&vars->monitor, NULL, check_death, vars) != 0)
		return (printf(PTHREAD_FAILURE), FAILURE);
	while (++i < vars->num_philo)
	{
		if (pthread_create(&vars->philosphers[i].thread, NULL, philo_routine, \
		&vars->philosphers[i]) != 0)
			return (printf(PTHREAD_FAILURE), FAILURE);
	}
	i = -1;
	while (++i < vars->num_philo)
		if (pthread_join(vars->philosphers[i].thread, NULL) != 0)
			return (printf(PTHREAD_JOIN_FAILURE), FAILURE);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	if (argc == 5 || argc == 6)
	{
		if (validate_arguments(argc, argv, &vars))
			return (FAILURE);
		if (init_values(&vars))
			return (FAILURE);
		if (start_simulation(&vars))
			return (FAILURE);
	}
	else
		return (printf(USAGE_MSG), FAILURE);
	return (SUCCESS);
}
