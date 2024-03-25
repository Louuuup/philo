/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:47:36 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/19 16:25:03 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(t_philo *philo)
{
    t_data *data;

    data = get_data();
    pthread_mutex_lock(&data->print_mutex);
    print_time();
    if (philo->status == THINKING)
        printf("Philo #%03d is thinking\n", philo->id);
    else if (philo->status == EATING)
        printf("Philo #%03d is eating\n", philo->id);
    else if (philo->status == SLEEPING)
        printf("Philo #%03d is sleeping\n", philo->id);
    else if (philo->status == DEAD)
        printf("Philo #%03d is dead\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
}
