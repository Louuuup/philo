/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:43 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/25 14:34:36 by ycyr-roy         ###   ########.fr       */
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

void stop(void)
{
	t_data *data;

	data = get_data();
	pthread_mutex_lock(&data->running_mutex);
	data->running = FALSE;
	pthread_mutex_unlock(&data->running_mutex);

}
void join_philos(t_data *data)
{
	t_philo *tmp;
	int i;

	i = 0;
	tmp = data->philo;
	// printf("Closing philos\n");
	while (i < data->nb_philo)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
}
int	main(int argc, char *argv[])
{
	t_data *data;

	data = get_data();
	
	if (parse_main(argc, argv))
		return (1);
	data->running = TRUE;
	// test_sleep_accuracy();
	thread_main(data);
	return (0);
}

int thread_main(t_data *data)
{
	int i;
	t_philo *tmp;

	i = 0;
	tmp = data->philo;
	pthread_mutex_init(&data->running_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	while (i < data->nb_philo)
	{
		pthread_create(&tmp->thread, NULL, (void *)philo_life, tmp);
		tmp = tmp->next;
		i++;
	}
	while (TRUE)
	{
		if (is_running() == FALSE)
		{
			printf("stopped\n");
			join_philos(data);
			return (0);
		}
		else
			usleep(1000);
	}
	return (0);
}