/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:39:53 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/29 13:22:03 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int fork_attribute(t_data *data)
{
    t_philo *tmp;
    int i;

    i = 0;
    tmp = data->philo;
    while (i < data->nb_philo)
    {
        if (i == data->nb_philo - 1)
            tmp->next = data->philo;
        tmp = tmp->next;
        i++;
    }
    return (0);
}

int create_philo(t_data *data)
{
    t_philo philo[200];
    int i;
    t_philo *tmp;
    
    i = 0;
    tmp = data->philo;
    get_data()->philo = &philo[0];
    while (i < data->nb_philo)
    {
        tmp = &philo[i];
        tmp->id = i + 1;
        tmp->status = 0;
        pthread_mutex_init(&tmp->fork, NULL);
        tmp->next = &philo[i + 1];
        i++;
    }
    return (0);
}

int parse_main(int argc, char *argv[])
{
    t_data *data;

    data = get_data();
    if (parse_args(argc, argv, data))
        return (error_str("Invalid arguments"));
    create_philo(data);
    fork_attribute(data);
    if (DEBUG_ON)
        print_data(data);
    return (0);
}

int	parse_args(int argc, char *argv[], t_data *data)
{
    if (argc < 5 || argc > 6)
        return (1);
    if (!ft_isnumber(argv[1]) || !ft_isnumber(argv[2]) || !ft_isnumber(argv[3]) \
        || !ft_isnumber(argv[4]) || (argc == 6 && !ft_isnumber(argv[5])))
        return (1);
	data->start_time = get_time();
    data->nb_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->nb_eat = ft_atoi(argv[5]);
    else
        data->nb_eat = -1;
    if (data->nb_philo < 1 || data->time_to_die < 60 || data->time_to_eat < 60
        || data->time_to_sleep < 60 || (argc == 6 && data->nb_eat < 1))
        return (1);
    return (0);
}
