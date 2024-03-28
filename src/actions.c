/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:55:13 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/28 15:15:31 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void p_sleep(t_philo *philo)
{
	philo->status = SLEEPING;
	print_status(philo);
	spend_time(philo, get_data()->time_to_sleep);
}
    // long sleep_time;
    
    // philo->status = SLEEPING;
    // print_status(philo);
    // sleep_time = get_time();
    // while (get_time() - sleep_time < get_data()->time_to_sleep && \
    //     is_running() == TRUE && philo->status != DEAD)
    // {
    //     usleep(1000);
    //     if (philo->last_eat_time + get_data()->time_to_die < get_time())
    //     {
    //         p_die(philo);
    //         return ;
    //     }
    // }
static void p_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork);
    pthread_mutex_lock(&philo->next->fork);
    if (is_philo_alive(philo) == TRUE)
    {
		philo->status = EATING;
   		print_status(philo);
        spend_time(philo, get_data()->time_to_eat);
	}
    if (is_philo_alive(philo) == FALSE)
        return ;
    philo->last_eat_time = get_time();
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->next->fork);    
}

// static void p_eat(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->left_fork);
//     pthread_mutex_lock(&philo->right_fork);
//     philo->status = EATING;
//     philo->last_eat_time = get_time();
//     print_status(philo);
//     while (get_time() - philo->last_eat_time < get_data()->time_to_eat && \
//         is_running() == TRUE && philo->status != DEAD)
//     {
//         usleep(1000);
//         if (philo->last_eat_time + get_data()->time_to_die < get_time())
//         {
//             p_die(philo);
//             return ;
//         }
//     }
//     print_status(philo);
//     pthread_mutex_unlock(&philo->left_fork);
//     pthread_mutex_unlock(&philo->right_fork);
// }

static void p_think(t_philo *philo)
{
    philo->status = THINKING;
    print_status(philo);
}

void    philo_life(t_philo *philo)
{
    while (is_running() == FALSE)
        ;
    if (philo->id % 2 == 0)
        usleep(2);
	while (is_philo_alive(philo) == TRUE)
	{
        // printf("Cycle: %d, status = %d, is_running = %d\n", philo->id, philo->status, is_running());
		if (is_philo_alive(philo) == TRUE)
			p_eat(philo);
		if (is_philo_alive(philo) == TRUE)
			p_sleep(philo);
		if (is_philo_alive(philo) == TRUE)
			p_think(philo);
	}
}

void p_die(t_philo *philo)
{
    pthread_mutex_lock(&get_data()->running_mutex);
    if (philo->status != DEAD)
    {
        philo->status = DEAD;
        print_status(philo);
    	stop();
    }
    pthread_mutex_unlock(&get_data()->running_mutex);
}