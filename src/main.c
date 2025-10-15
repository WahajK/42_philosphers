/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:47:04 by muhakhan          #+#    #+#             */
/*   Updated: 2025/10/12 23:34:39 by muhakhan         ###   ########.fr       */
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
	ended = vars->death_flag || vars->all_eaten;
	pthread_mutex_unlock(&vars->death_mutex);
	return (ended);
}

int	check_death(t_vars *vars)
{
	pthread_mutex_lock(&vars->death_mutex);
	if (vars->death_flag || vars->all_eaten)
		return (pthread_mutex_unlock(&vars->death_mutex), 1);
	return (pthread_mutex_unlock(&vars->death_mutex), 0);
}

int	eat(void)
{
	return (SUCCESS);
}

int	sleep_(void)
{
	return (SUCCESS);
}

int	think(t_vars *vars)
{
	if (check_death(vars))
		return (FAILURE);
	return (SUCCESS);
}

// void	print_status(t_vars *vars, char *msg)
// {
// 	long	timestamp;

// 	pthread_mutex_lock(&vars->print_mutex);
// 	if (simulation_ended(vars))
// 	{
// 	}
// }

// void	philo_routine(void *vars)
// {
// 	t_vars *philo;

// 	philo = (t_vars *) vars;
// 	while (simulation_ended(&vars) != 1)
// 	{
// 		if (eat())
// 			return (NULL);
// 		if (sleep())
// 			return (NULL);
// 		if (think())
// 			return (NULL);
// 	}
// }

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
	}
}

int	init_values(t_vars *vars)
{
	int	i;

	vars->philosphers = ft_calloc(sizeof(t_philospher), vars->num_philo);
	vars->chopsticks = malloc(sizeof(t_mutex) * vars->num_philo);
	if (!vars->philosphers || !vars->chopsticks)
		return (FAILURE);
	i = -1;
	while (++i < vars->num_philo)
	{
		if (pthread_mutex_init(&vars->chopsticks[i], NULL) != 0)
			return (printf(MUTEX_FAILURE), FAILURE);
		vars->philosphers[i].id = i;
	}
	if (pthread_mutex_init(&vars->print_mutex, NULL) != 0
		|| pthread_mutex_init(&vars->death_mutex, NULL) != 0)
		return (printf(MUTEX_FAILURE), FAILURE);
	return (SUCCESS);
}

int	essen(t_philospher *philo)
{

}

void	*philo_routine(void *args)
{
	t_philospher *philo = (t_philospher *)args;
	printf("Pihlo ID: %d\n", philo->id);
	if (philo->id % 2 == 0)
		usleep(5);
	if (essen(philo))
		return (NULL);
	if (schlafen())
		return (NULL);
	if (denken())
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
		if (pthread_join(vars->philosphers->thread, NULL) != 0)
			return (printf(PTHREAD_JOIN_FAILURE), FAILURE);
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
