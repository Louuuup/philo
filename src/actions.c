/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:55:13 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/29 14:25:41 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void p_sleep(t_philo *philo)
{
	philo->status = SLEEPING;
	print_status(philo);
	spend_time(philo, get_data()->time_to_sleep);
}

static void p_eat(t_philo *philo)
{
    take_forks(philo);
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

static void p_think(t_philo *philo)
{
    philo->status = THINKING;
    print_status(philo);
}

void    philo_life(t_philo *philo)
{
    while (is_running() == FALSE)
        ;
    if (!philo->id % 2)
        usleep(70);
    else if (get_data()->nb_philo % 2 == 1 && philo->id == get_data()->nb_philo)
        usleep(70);
	while (is_philo_alive(philo) == TRUE)
	{
        // printf("Cycle: %d, status = %d, is_running = %d\n", philo->id, philo->status, is_running());
		if (is_philo_alive(philo) == TRUE)
			p_think(philo);
        if (get_data()->nb_philo == 1)
        {
            print_time();
	        printf("Philo #001 has taken a fork\n");
            spend_time(philo, get_data()->time_to_die);
            p_die(philo);
            break ;
        }
		if (is_philo_alive(philo) == TRUE)
			p_eat(philo);
        // if (ate_enough(philo) == TRUE)
        //     break ;
		if (is_philo_alive(philo) == TRUE)
			p_sleep(philo);
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