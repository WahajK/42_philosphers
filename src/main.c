/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:47:04 by muhakhan          #+#    #+#             */
/*   Updated: 2025/07/23 22:22:46 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosphers.h"

int	ft_nan(char *num)
{
	if (*num == '+')
		num++;
	while (*num)
		if (*num >= '0' && *num <= '9')
			num++;
		else
			return (1);
	return (0);
}

int	validate_arguments(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
		if (ft_nan(argv[i++]))
			return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		if (validate_arguments(argc, argv))
			return (printf("Invalid argument type or value\n"));
	}
	else
		return (printf("Invalid number of arguments\n"), 1);
	
}