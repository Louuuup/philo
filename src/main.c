/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:43 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/04/01 16:59:55 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_running(void)
{
	t_data *data;

	data = get_data();
	pthread_mutex_lock(&data->running_mutex);
	if (data->running == FALSE)
	{
		pthread_mutex_unlock(&data->running_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&data->running_mutex);
	return (data->running);
}

void join_philos(t_data *data)
{
	t_philo *tmp;
	int i;

	i = 0;
	tmp = data->philo;
	while (tmp && i < data->nb_philo)
	{
		pthread_mutex_unlock(&tmp->fork);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	tmp = data->philo;
	// printf("Closing %d philos\n", data->nb_philo);
	while (tmp && i < data->nb_philo)
	{
		// printf("Closing philo %d...\n ", tmp->id);
		pthread_join(tmp->thread, NULL);
		// printf("Done!\n");
		tmp = tmp->next;
		i++;
	}
	printf("All philos closed\n");
}


static void mutex_init(t_data *data)
{
	// printf("mutex init\n");
	pthread_mutex_init(&data->running_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->die_mutex, NULL);
}

int thread_main(t_data *data)
{
	int i;
	t_philo *tmp;

	i = 0;
	tmp = data->philo;
	while (i < data->nb_philo)
	{
		// printf("Creating philo %d\n", tmp->id);
		pthread_create(&tmp->thread, NULL, (void *)philo_life, tmp);
		tmp = tmp->next;
		i++;
	}
	pthread_mutex_unlock(&data->running_mutex);
	while (TRUE)
	{
		if (is_running() == FALSE)
		{
			// printf("stopped\n");
			join_philos(data);
			return (0);
		}
		// removed else sleep
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data *data;

	data = get_data();
	
	if (parse_main(argc, argv))
		return (1);
	data->running = TRUE;
	// test_sleep_accuracy();
	mutex_init(data);
	pthread_mutex_lock(&data->running_mutex);
	thread_main(data);
	return (0);
}