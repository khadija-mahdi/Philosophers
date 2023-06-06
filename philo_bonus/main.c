/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:07:21 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/06 04:50:23 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosophers_life(t_philos	*philos, t_arguments *arguments)
{
	t_data		*data;
	int			id;

	data = philos->my_philos[philos->curr_philo];
	id = get_id_value(data, philos);
	data = philos->my_philos[id];
	while (1)
	{
		sem_wait(arguments->forks);
		print_state(data, "has taken left fork");
		if (arguments->philo_nbr == 1)
			sem_wait(arguments->forks);
		print_state(data, "has taken a right fork");
		data->last_eat = get_program_time(data);
		print_state(data, "is eating");
		usleep(data->args->eat_time * 1000);
		data->meals++;
		sem_post(arguments->forks);
		print_state(data, "is sleeping");
		usleep(data->args->sleep_time * 1000);
		print_state(data, "is thinking");
		if (data->args->meals_nbr && data->meals == data->args->meals_nbr)
			exit(0);
	}
}

void	*process_thread(void *arg)
{
	t_philos	*philos;
	t_data		*data;
	int			id;
	long		time;

	philos = (t_philos *) arg;
	data = philos->my_philos[philos->curr_philo];
	id = get_id_value(data, philos);
	data = philos->my_philos[id];
	while (1)
	{
		sem_wait(data->args->sem_print);
		time = get_program_time(data);
		sem_post(data->args->sem_print);
		if (((time - data->last_eat) >= data->args->die_time
				&& time <= (data->args->die_time + 10)))
		{
			print_die(data);
			exit(1);
		}
		if (data->args->meals_nbr && data->meals == data->args->meals_nbr)
			exit(0);
	}
	return (NULL);
}

void	create_philosophers(t_data **data)
{
	int			i;
	pthread_t	tid;
	t_philos	*philos;
	pid_t		pid;

	i = 0;
	while (i < data[0]->args->philo_nbr)
	{
		pid = fork();
		if (pid < 0)
			exit_msg("fork failed\n", 1);
		else if (pid == 0)
		{
			philos = malloc(sizeof(t_philos));
			philos->my_philos = data;
			philos->curr_philo = i;
			pthread_create(&tid, NULL, process_thread, philos);
			philosophers_life(philos, data[0]->args);
			pthread_join(tid, NULL);
			exit(0);
		}
		else
			data[i]->philosophers = pid;
		i++;
	}
}

void	main_process(t_arguments *arguments, t_data **data)
{
	int			status;
	int			i;
	int			j;

	i = 0;
	while (i < arguments->philo_nbr)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			j = 0;
			while (j < arguments->philo_nbr)
				kill(data[j++]->philosophers, SIGTERM);
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_arguments	*arguments;
	t_data		**data;

	sem_unlink("forks");
	sem_unlink("print");
	arguments = init_arguments(argv, argc);
	check_invalid_argument(arguments);
	data = init_data(arguments);
	create_philosophers(data);
	main_process(arguments, data);
	sem_close(arguments->forks);
	sem_close(data[0]->args->sem_print);
	sem_unlink("forks");
	sem_unlink("print");
}
