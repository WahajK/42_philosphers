#include "../include/philosphers.h"

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
