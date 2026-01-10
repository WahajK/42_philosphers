#include "../include/philosphers.h"

int	simulation_ended(t_vars *vars)
{
    int	ended;

    pthread_mutex_lock(&vars->death_mutex);
    ended = vars->death_flag;
    pthread_mutex_unlock(&vars->death_mutex);
    return (ended);
}

void	safely_set_flags(t_vars *vars, int death_flag, int all_eaten)
{
    pthread_mutex_lock(&vars->death_mutex);
    vars->death_flag = death_flag;
    vars->all_eaten = all_eaten;
    pthread_mutex_unlock(&vars->death_mutex);
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
            safely_set_flags(vars, 1, 1);
        usleep(1000);
    }
    return (NULL);
}
