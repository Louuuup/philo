/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:44:17 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/28 15:28:29 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data *get_data(void)
{
    static t_data data;

    return (&data);
}

int error_str(char *str)
{
    write(2, ERROR_HEADER, ft_strlen(ERROR_HEADER));
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    return (ERROR);
}

int is_philo_alive(t_philo *philo)
{
    pthread_mutex_lock(&get_data()->print_mutex);
    // printf("is_philo_alive #%d: ", philo->id);
    if (philo->status == DEAD || is_running() == FALSE)
    {
        // printf("status %d and dead\n", philo->status);
        pthread_mutex_unlock(&get_data()->print_mutex);
        return (FALSE);
    }
    if (philo->last_eat_time + get_data()->time_to_die < get_time())
    {   
        p_die(philo);
        // printf("just dead\n");
        pthread_mutex_unlock(&get_data()->print_mutex);
        return (FALSE);
    }
    // printf("alive and well\n");
    pthread_mutex_unlock(&get_data()->print_mutex);
    return (TRUE);
}

void stop(void)
{
	t_data *data;

	data = get_data();
    printf("Stopping philos\n");
	data->running = FALSE;
}