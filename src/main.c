/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:47:04 by muhakhan          #+#    #+#             */
/*   Updated: 2025/08/02 20:26:57 by muhakhan         ###   ########.fr       */
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

int	validate_arguments(int argc, char *argv[], t_vars *vars)
{
	int	i;

	i = 1;
	while (i < argc)
		if (ft_nan(argv[i++]))
			return (FAILURE);
	i = 0;
	vars->num_philo = ft_atol(argv[++i]);
	vars->ttd = ft_atol(argv[++i]);
	vars->tte = ft_atol(argv[++i]);
	vars->tts = ft_atol(argv[++i]);
	if (argc == 6)
		vars->eat_num = ft_atol(argv[++i]);
	else
		vars->eat_num = -1;
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc == 5 || argc == 6)
	{
		if (validate_arguments(argc, argv, &vars))
			return (printf("Invalid argument type or value\n"));
		if (vars.num_philo == 1)
			return (SUCCESS);
		
	}
	else
		return (printf(USAGE_MSG), 1);
}
