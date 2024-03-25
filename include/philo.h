/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:18 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/21 17:37:23 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

//==================VALUES===================//
# define DEBUG_ON 1
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define SUCCESS 0
# define AVALIABLE 0
# define TAKEN 1
# define TEST_TIME 1000

# define ERROR_HEADER "\033[1m\033[31mPHILO: \033[0m"
# define TIME_IN "\033[32m[\033[37m"
# define TIME_OUT "\033[32m]\033[0m "
//==================Structs===================//

typedef struct s_philo
{
	int id;
	int status;
	long last_eat_time;
	pthread_t thread;
	pthread_mutex_t fork;
	struct s_philo *next;
}				t_philo;

typedef struct s_data
{
	int running;
	pthread_mutex_t running_mutex;
	pthread_mutex_t print_mutex;
	long start_time;
	t_philo *philo;
	int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_eat;
}				t_data;

enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
};

//=========================parse.c=========================//

int parse_main(int argc, char *argv[]);
int	parse_args(int argc, char *argv[], t_data *data);
//=========================actions.c=========================//

void    philo_life(t_philo *philo);
void	p_die(t_philo *philo); 
//=========================time.c=========================//

void print_time(void);
long start_time(void);
long get_time(void);
void spend_time(t_philo *philo, int ms);
//=========================printer.c=========================//

void print_status(t_philo *philo);
//=========================utils.c=========================//

t_data *get_data(void);
int is_philo_alive(t_philo *philo);
int error_str(char *str);
//=========================main.c=========================//

int thread_main(t_data *data);
int is_running(void);
void stop(void);


//tmp
void philo_status(t_philo *philo);
void print_data(t_data *data);
void    test_sleep_accuracy(void);

#endif
