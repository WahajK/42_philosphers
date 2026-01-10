/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:51:28 by muhakhan          #+#    #+#             */
/*   Updated: 2026/01/10 15:51:30 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosphers.h"

void	lock_chopsticks_ordered(t_philospher *philo)
{
    t_mutex	*first;
    t_mutex	*second;

    first = philo->left_chopstick;
    second = philo->right_chopstick;
    if (first > second)
    {
        t_mutex *tmp = first;
        first = second;
        second = tmp;
    }
    pthread_mutex_lock(first);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(second);
    print_status(philo, "has taken a fork");
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
    lock_chopsticks_ordered(philo);
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
