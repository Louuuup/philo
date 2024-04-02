/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:39:53 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/04/02 18:13:51 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void philo_init(t_philo philo[200])
{
    int i;

    i = 0;
    while (i < 200)
    {
        philo[i].id = 0;
        philo[i].status = 0;
        philo[i].ate = 0;
        philo[i].last_eat_time = 0;
        philo->next = NULL;
        
        i++;
    }
}


int create_philo(t_philo philo[200], t_data *data)
{
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
        if (philo[i].id > 150)
        	printf("initialing philo %d\n", philo[i].id);
        if (i + 1 < data->nb_philo)
        	tmp->next = &philo[i + 1];
        i++;
    }
    tmp->next = NULL;
//tmp
	// philo_test(data, "after init");
    return (0);
}

int parse_main(t_philo philo[200], int argc, char *argv[])
{
    t_data *data;

    data = get_data();
    if (parse_args(argc, argv, data))
        return (error_str("Invalid arguments"));
    create_philo(philo, data);
    if (DEBUG_ON)
        print_data(data);
	// philo_test(data, "parse_main");
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
