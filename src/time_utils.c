#include "../include/philosphers.h"

long	get_current_time(void)
{
    struct timeval		v;
    long				current_time;

    gettimeofday(&v, NULL);
    current_time = (v.tv_sec * 1000) + (v.tv_usec / 1000);
    return (current_time);
}

void	set_last_ate_time(t_philospher *philo)
{
    pthread_mutex_lock(&philo->last_meal_mutex);
    philo->last_ate_time = get_current_time();
    pthread_mutex_unlock(&philo->last_meal_mutex);
}
