/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:19:11 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/04/01 16:53:24 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_status(t_philo *philo)
{
    t_philo *tmp = philo;
    
    if (!tmp) {
        printf("No philosophers\n");
        return ;
    }
    int i = 0;
    while (i < get_data()->nb_philo)
    {
        printf("=====PHILO #%d=====\n", tmp->id);
        printf("Status: ");
        if (tmp->status == THINKING)
            printf("thinking\n");
        else if (tmp->status == EATING)
            printf("eating\n");
        else if (tmp->status == SLEEPING)
            printf("sleeping\n");
        else if (tmp->status == DEAD)
            printf("dead\n");
        printf("Left fork: %p\n",  &tmp->fork);
        tmp = tmp->next;
        i++;
    }
}

void print_data(t_data *data)
{
    printf("=====DATA=====\n");
    printf("Number of philosophers: %d\n", data->nb_philo);
    printf("Time to die: %d\n", data->time_to_die);
    printf("Time to eat: %d\n", data->time_to_eat);
    printf("Time to sleep: %d\n", data->time_to_sleep);
    printf("Running: %d\n", data->running);
    printf("Start time: %ld\n", data->start_time);
}

void spend_time_alt(int ms)
{
    struct timeval  start;
    struct timeval  end;
    long            seconds;
    long            microseconds;
    double          elapsed_milliseconds;

    gettimeofday(&start, NULL);
    while (TRUE)
    {
        gettimeofday(&end, NULL);
        seconds = end.tv_sec - start.tv_sec;
        microseconds = end.tv_usec - start.tv_usec;
        elapsed_milliseconds = seconds * 1000 + microseconds / 1000.0;
        if (elapsed_milliseconds > ms)
                break ;
    }
}

void    test_sleep_accuracy(void)
{
    struct timeval  start;
    struct timeval  end;
    long            seconds;
    long            microseconds;
    double          elapsed_milliseconds;

    gettimeofday(&start, NULL);
    //
    spend_time_alt(TEST_TIME);
    //
    gettimeofday(&end, NULL);
    //
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    elapsed_milliseconds = (seconds * 1000) + (microseconds / 1000.0);
    //
    printf("Expected sleep duration:\t%d ms\n", TEST_TIME);
    printf("Actual sleep duration:\t\t%.2f ms\n", elapsed_milliseconds);
}
