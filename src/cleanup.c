#include "../include/philosphers.h"

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
