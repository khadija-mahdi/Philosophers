/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:07:21 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/03 02:25:54 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define FORK_SEM_NAME "/forks_sem"

t_data	**init_data(t_arguments	*arguments)
{
	t_data			**data;
	int				i;

	i = 0;
	data = malloc(sizeof(t_data *) * arguments->philo_nbr);
	while (i < arguments->philo_nbr)
	{
		data[i] = malloc(sizeof(t_data));
		data[i]->args = arguments;
		data[i]->philo_id = i + 1;
		data[i]->meals = 0;
		data[i]->last_eat = 0;

		i++;
	}
	return (data);
}

long	get_program_time(t_data *data)
{
	long	total_microseconds;
	long	microseconds;

	microseconds = get_time_in_ms();
	total_microseconds = microseconds - data->args->start_time;
	return (total_microseconds);
}

int	get_id_value(t_data *data, t_philos *philos)
{
	int	id;

	if (philos->curr_philo + 1 == data->args->philo_nbr)
		id = 0;
	else
		id = philos->curr_philo + 1;
	return (id);
}

void print_state(t_data		*data, char *msg)
{
		long		time;

	time = get_program_time(data);
	sem_wait(data->args->sem_print);
	printf("\n%ld philosopher number %d %s\n\n",time, data->philo_id, msg);
	sem_post(data->args->sem_print);
}

void	*processThread(void *arg)
{
	t_philos	*philos;
	t_data		*data;
	int			id;
	int			i = 0;
	int			philo_nbr;

	long		time;

	philos = (t_philos *) arg;
	data = philos->my_philos[philos->curr_philo];
	id = get_id_value(data, philos);
	data =  philos->my_philos[id];
		philo_nbr = data->args->philo_nbr;
	while (1)
	{
		time = (int)get_program_time(data);
		// printf("\n\n philo id %d : time %ld last_eat : %ld\n\n",data->philo_id, time, data->last_eat);
		if (((time - data->last_eat) >= data->args->die_time && (time ) <= (data->args->die_time + 10)))
		{
			printf(" philo %d time %ld", data->philo_id , time - data->last_eat);
			print_state(data, "is died");
			exit(0);
		}
	}
	return (NULL);
}

void	print_life(t_philos	*philos, t_arguments	*arguments)
{
	long		time;
	t_data		*data;
	int 		i = 0;

	data = philos->my_philos[philos->curr_philo];
	int id = get_id_value(data, philos);
	data =  philos->my_philos[id];
	while (1)
	{
		sem_wait(arguments->forks);
		print_state(data, "has taken left fork");
		print_state(data, "has taken a right fork");
		data->last_eat = get_program_time(data);
		print_state(data, "is eating");
		usleep(data->args->eat_time * 1000);
		data->meals++;
		sem_post(arguments->forks);
		print_state(data, "is sleeping");
		usleep(data->args->sleep_time * 1000);
		print_state(data, "is thinking");
		if (data->args->meals_nbr && data->meals
			&& data->meals == data->args->meals_nbr)
			exit(0) ;
	}
	
}


void	create_philosophers(t_data **data)
{
	int			i;
	int			philo_nbr;
	t_philos	*philos;
    
	i = 0;
	data[0]->args->sem_print = sem_open("/print",  O_CREAT | O_EXCL , 0644, 1);
	philo_nbr = data[0]->args->philo_nbr;
	while (i < philo_nbr)
	{
		pid_t  pid = fork();
		if (pid < 0)
			exit_msg("fork failed\n", 1);
		else if (pid)
			data[i]->philosophers = pid;
		else if (pid == 0)
		{
			philos = malloc(sizeof(t_philos));
			philos->my_philos = data;
			philos->curr_philo = i;
			pthread_t tid;
            pthread_create(&tid, NULL, processThread, philos);
			print_life(philos, data[0]->args);
            pthread_join(tid, NULL);
			exit(0);
		}
		i++;
	}
	return ;
}
int	main(int argc, char **argv)
{
	t_arguments	*arguments;
	t_data		**data;
	int			i;

	i = 0;
	arguments = init_arguments(argv, argc);
	check_invalid_argument(arguments);
	data = init_data(arguments);
	arguments->forks = sem_open("/my_semaphore", O_CREAT | O_EXCL , 0644, (arguments->philo_nbr / 2));
	create_philosophers(data);
	i = -1;
    while (++i < arguments->philo_nbr)
        waitpid(data[i]->philosophers, NULL, 0);
	sem_close(arguments->forks);
	sem_close(data[0]->args->sem_print);
    sem_unlink("/my_semaphore");
    sem_unlink("/print");
	return 0;
}
