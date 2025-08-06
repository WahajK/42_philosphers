/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:47:04 by muhakhan          #+#    #+#             */
/*   Updated: 2025/08/06 20:18:03 by muhakhan         ###   ########.fr       */
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

int	init_values(t_vars *vars)
{
	vars->philosphers = malloc(sizeof(t_philospher) * vars->num_philo);
	vars->forks = malloc(sizeof)
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc == 5 || argc == 6)
	{
		if (validate_arguments(argc, argv, &vars))
			return (FAILURE);
		if (init_values(&vars))
			return (FAILURE);
	}
	else
		return (printf(USAGE_MSG), 1);
}
