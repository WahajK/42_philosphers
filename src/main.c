/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:47:04 by muhakhan          #+#    #+#             */
/*   Updated: 2025/10/21 13:09:10 by muhakhan         ###   ########.fr       */
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

void	free_philosophers(t_vars *vars)
{
	int	i;

	if (vars->philosphers)
	{
		i = 0;
		while (i < vars->num_philo)
		{
			pthread_mutex_destroy(&vars->philosphers[i].last_meal_mutex);
			i++;
		}
		free(vars->philosphers);
		vars->philosphers = NULL;
	}
}

void	free_chopsticks(t_vars *vars)
{
	int	i;

	if (vars->chopsticks)
	{
		i = 0;
		while (i < vars->num_philo)
		{
			pthread_mutex_destroy(&vars->chopsticks[i]);
			i++;
		}
		free(vars->chopsticks);
		vars->chopsticks = NULL;
	}
}

void	free_mutexes(t_vars *vars)
{
	if (&vars->print_mutex)
		pthread_mutex_destroy(&vars->print_mutex);
	if (&vars->death_mutex)
		pthread_mutex_destroy(&vars->death_mutex);
}

void	free_resources(t_vars *vars)
{
	free_philosophers(vars);
	free_chopsticks(vars);
	free_mutexes(vars);
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

void	philosphers_janaza(t_vars *vars, int i)
{
	long	timestamp;

	pthread_mutex_lock(&vars->death_mutex);
	vars->death_flag = 1;
	pthread_mutex_unlock(&vars->death_mutex);
	pthread_mutex_lock(&vars->print_mutex);
	timestamp = get_current_time() - vars->start_time;
	printf("%s%ld %s%d %shas died%s\n",
		CYAN, timestamp, BOLD, vars->philosphers[i].id, "", RESET);
	pthread_mutex_unlock(&vars->print_mutex);
}

void	*monitor_routine(void *args)
{
	t_vars	*vars;
	int		i;
	int		count;

	vars = (t_vars *) args;
	while (!simulation_ended(vars))
	{
		i = -1;
		count = 0;
		while (++i < vars->num_philo)
		{
			if (is_philo_dead(&vars->philosphers[i]))
			{
				philosphers_janaza(vars, i);
				break ;
			}
			if (check_all_eaten(&vars->philosphers[i]))
				count++;
		}
		if (count == vars->num_philo)
		{
			pthread_mutex_lock(&vars->death_mutex);
			vars->all_eaten = 1;
			vars->death_flag = 1;
			pthread_mutex_unlock(&vars->death_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}

int	is_philo_dead(t_philospher *philo)
{
	long	last_ate_time;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_ate_time = philo->last_ate_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (get_current_time() - last_ate_time >= philo->vars->time_to_die);
}

int	check_all_eaten(t_philospher *philo)
{
	int	num_eaten;

	if (philo->vars->eat_num == -1)
		return (0);
	pthread_mutex_lock(&philo->last_meal_mutex);
	num_eaten = philo->num_eaten;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (num_eaten >= philo->vars->eat_num);
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
	int	next;

	i = -1;
	while (++i < vars->num_philo)
	{
		next = (i + 1) % vars->num_philo;
		if (i % 2 == 0)
		{
			vars->philosphers[i].right_chopstick = &vars->chopsticks[i];
			vars->philosphers[i].left_chopstick = &vars->chopsticks[next];
		}
		else
		{
			vars->philosphers[i].right_chopstick = &vars->chopsticks[next];
			vars->philosphers[i].left_chopstick = &vars->chopsticks[i];
		}
	}
}

int	init_values(t_vars *vars)
{
	int	i;

	vars->philosphers = ft_calloc(vars->num_philo, sizeof(t_philospher));
	vars->chopsticks = malloc(sizeof(t_mutex) * vars->num_philo);
	if (!vars->philosphers || !vars->chopsticks)
		return (FAILURE);
	vars->start_time = get_current_time();
	if (pthread_mutex_init(&vars->print_mutex, NULL) != 0
		|| pthread_mutex_init(&vars->death_mutex, NULL) != 0)
		return (printf(MUTEX_FAILURE), FAILURE);
	i = -1;
	while (++i < vars->num_philo)
	{
		vars->philosphers[i].vars = vars;
		vars->philosphers[i].last_ate_time = vars->start_time;
		if (pthread_mutex_init(&vars->chopsticks[i], NULL) != 0 \
|| pthread_mutex_init(&vars->philosphers[i].last_meal_mutex, NULL) != 0)
			return (printf(MUTEX_FAILURE), FAILURE);
		vars->philosphers[i].id = i + 1;
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

void	set_last_ate_time(t_philospher *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_ate_time = get_current_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

int	essen(t_philospher *philo)
{
	int	num_eaten;

	if (philo->vars->eat_num != -1)
	{
		pthread_mutex_lock(&philo->last_meal_mutex);
		num_eaten = philo->num_eaten;
		pthread_mutex_unlock(&philo->last_meal_mutex);
		if (num_eaten >= philo->vars->eat_num)
			return (1);
	}
	philo->current_state = EATING;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_chopstick);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_chopstick);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_chopstick);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_chopstick);
		print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	set_last_ate_time(philo);
	usleep(philo->vars->time_to_eat * 1000);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->num_eaten++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(philo->right_chopstick);
	pthread_mutex_unlock(philo->left_chopstick);
	return (SUCCESS);
}

int	schlafen(t_philospher *philo)
{
	if (simulation_ended(philo->vars))
		return (1);
	philo->current_state = SLEEPING;
	print_status(philo, "is sleeping");
	usleep(philo->vars->time_to_sleep * 1000);
	return (SUCCESS);
}

int	denken(t_philospher *philo)
{
	if (simulation_ended(philo->vars))
		return (1);
	philo->current_state = THINKING;
	print_status(philo, "is thinking");
	return (SUCCESS);
}

void	*philo_routine(void *args)
{
	t_philospher	*philo;

	philo = (t_philospher *)args;
	if (philo->id % 2 == 0)
		usleep(1000);
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
	while (++i < vars->num_philo)
	{
		if (pthread_create(&vars->philosphers[i].thread, NULL, philo_routine, \
&vars->philosphers[i]) != 0)
			return (printf(PTHREAD_FAILURE), FAILURE);
	}
	if (pthread_create(&vars->monitor, NULL, monitor_routine, vars) != 0)
		return (printf(PTHREAD_FAILURE), FAILURE);
	i = -1;
	while (++i < vars->num_philo)
		if (pthread_join(vars->philosphers[i].thread, NULL) != 0)
			return (printf(PTHREAD_JOIN_FAILURE), FAILURE);
	pthread_join(vars->monitor, NULL);
	return (SUCCESS);
}

void	handle_single_philo(t_vars *vars)
{
	long	start;
	long	timestamp;

	start = get_current_time();
	printf("%s0 %s1 %shas taken a fork%s\n", CYAN, BOLD, "", RESET);
	usleep(vars->time_to_die * 1000);
	timestamp = get_current_time() - start;
	printf("%s%ld %s1 %shas died%s\n", CYAN, timestamp, BOLD, "", RESET);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	if (argc == 5 || argc == 6)
	{
		if (validate_arguments(argc, argv, &vars))
			return (FAILURE);
		if (vars.num_philo == 1)
			return (handle_single_philo(&vars), SUCCESS);
		if (init_values(&vars))
			return (free_resources(&vars), FAILURE);
		if (start_simulation(&vars))
			return (free_resources(&vars), FAILURE);
	}
	else
		return (printf(USAGE_MSG), FAILURE);
	return (free_resources(&vars), SUCCESS);
}
