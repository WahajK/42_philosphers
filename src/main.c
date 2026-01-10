/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:47:04 by muhakhan          #+#    #+#             */
/*   Updated: 2026/01/10 15:54:49 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosphers.h"

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
