#include "../include/philosphers.h"

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
        if (pthread_create(&vars->philosphers[i].thread, NULL, philo_routine,
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
