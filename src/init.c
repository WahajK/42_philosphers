#include "../include/philosphers.h"

void	set_chopsticks(t_vars *vars)
{
    int	i;
    int	next;

    i = -1;
    while (++i < vars->num_philo)
    {
        next = (i + 1) % vars->num_philo;
        vars->philosphers[i].right_chopstick = &vars->chopsticks[next];
        vars->philosphers[i].left_chopstick = &vars->chopsticks[i];
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
        if (pthread_mutex_init(&vars->chopsticks[i], NULL) != 0
            || pthread_mutex_init(&vars->philosphers[i].last_meal_mutex, NULL) != 0)
            return (printf(MUTEX_FAILURE), FAILURE);
        vars->philosphers[i].id = i + 1;
    }
    set_chopsticks(vars);
    return (SUCCESS);
}
