/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:44:17 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/29 14:13:17 by ycyr-roy         ###   ########.fr       */
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
    // printf("is_philo_alive #%d: ", philo->id);
    if (philo->status == DEAD || is_running() == FALSE)
    {
        // printf("status %d and dead\n", philo->status);
        return (FALSE);
    }
    if (philo->last_eat_time + get_data()->time_to_die < get_time())
    {   
        p_die(philo);
        // printf("just dead\n");
        return (FALSE);
    }
    // printf("alive and well\n");
    return (TRUE);
}

void stop(void)
{
	t_data *data;

	data = get_data();
    printf("Stopping philos\n");
	data->running = FALSE;
}

int ate_enough(t_philo *philo)
{
    t_data *data;
    
    data = get_data();
    if (data->nb_eat == -1)
        return (FALSE);
    if (philo->ate >= data->nb_eat)
        return (TRUE);
    return (FALSE);
}