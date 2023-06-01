/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:07:21 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/01 22:57:24 by kmahdi           ###   ########.fr       */
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
		// data[i]->forks = malloc(sizeof(sem_t));
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

int	get_id_value(t_data *data, t_philos	*philos)
{
	int	id;

	if (philos->curr_philo + 1 == data->args->philo_nbr)
		id = 0;
	else
		id = philos->curr_philo + 1;
	return (id);
}

void	print_life(t_philos	*philos)
{
	long		time;
	t_data		*data;
	int i = 0;

	data = philos->my_philos[philos->curr_philo];
	int id = get_id_value(data, philos);
    t_data *next_data = philos->my_philos[id];
	while (1)
	{
		sem_wait(data->forks);
		time = get_program_time(data);
		printf("\n%ld philosopher number %d has taken"" a fork \n\n",time, data->philo_id);
		sem_wait(next_data->forks);
		time = get_program_time(data);
		printf("\n%ld philosopher number %d has taken"" a fork \n\n",time, data->philo_id);
		time = get_program_time(data);
		printf("\n%ld philosopher number %d is"" eating\n\n",time, data->philo_id);
		usleep(data->args->eat_time * 1000);

		sem_post(data->forks);
        sem_post(next_data->forks);
		time = get_program_time(data);
		printf("\n%ld philosopher number %d is"" sleeping \n\n",time, data->philo_id);
		usleep(data->args->die_time * 1000);
		printf("\n%ld philosopher number %d is"" thinking \n\n",time, data->philo_id);
		i++;
	}
	
}

void	processes_philosophers(t_data **data, int condition)
{
	int			i;
	int			philo_nbr;
	t_philos	*philos;
    
	i = 0;
	philo_nbr = data[0]->args->philo_nbr;
	while (i < philo_nbr)
	{
		pid_t  pid = fork();
		philos = malloc(sizeof(t_philos));
		philos->my_philos = data;
		philos->curr_philo = i;
		if (pid < 0)
			exit_msg("fork failed\n", 1);
		else if (pid)
			data[i]->philosophers = pid;
		else if (pid == 0 && ((condition && i % 2 == 0) || (!condition && i % 2 != 0)))
			print_life(philos);
		i++;
	}
	return ;
}

void	create_philosophers(t_data **data)
{
	processes_philosophers(data, 0);
	sleep(2);
	processes_philosophers(data, 2);
}
int	main(int argc, char **argv)
{
	t_arguments	*arguments;
	t_data		**data;
	int			status;
	int			i;

	i = 0;
	arguments = init_arguments(argv, argc);
	check_invalid_argument(arguments);
	data = init_data(arguments);
	for (int i = 0; i < arguments->philo_nbr; i++)
		data[i]->forks = sem_open("/my_semaphore", O_CREAT, 0644, arguments->philo_nbr - 1);
	create_philosophers(data);
    for (int i = 0; i < arguments->philo_nbr; i++)
        waitpid(data[i]->philosophers, &status, 0);
	for (int i = 0; i < arguments->philo_nbr; i++)
		sem_close(data[i]->forks);
    sem_unlink(FORK_SEM_NAME);
	return 0;
}
