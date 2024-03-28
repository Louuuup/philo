/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:53:47 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/28 15:19:13 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    printf(TIME_IN);
    printf("%09ld", tv.tv_sec * 1000 + tv.tv_usec / 1000 - get_data()->start_time);
    printf(TIME_OUT);
}

long start_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long get_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - get_data()->start_time);
}

void spend_time(t_philo *philo, int ms)
{
    struct timeval  start;
    struct timeval  end;
    long            seconds;
    long            microseconds;
    double          elapsed_milliseconds;

    gettimeofday(&start, NULL);
    while (1)
    {
        gettimeofday(&end, NULL);
        seconds = end.tv_sec - start.tv_sec;
        microseconds = end.tv_usec - start.tv_usec;
        elapsed_milliseconds = seconds * 1000 + microseconds / 1000.0;
        if (elapsed_milliseconds > ms)
                break ;
        if (is_philo_alive(philo) == FALSE)
            break ;
    }
}
