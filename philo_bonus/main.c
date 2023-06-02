/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:07:21 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/02 22:27:52 by kmahdi           ###   ########.fr       */
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

void	print_life(t_philos	*philos)
{
	long		time;
	t_data		*data;
	int 		i = 0;

	data = philos->my_philos[philos->curr_philo];
	int id = get_id_value(data, philos);
	data =  philos->my_philos[id];
	while (1)
	{
		// pick up left fork -->
		sem_wait(data->args->forks);
		time = get_program_time(data);
		sem_wait(data->args->sem_print);
		printf("\n%ld philosopher number %d has taken "" a left fork \n\n",time, data->philo_id);
        sem_post(data->args->sem_print);

		// pick up right fork -->
		sem_wait(data->args->forks);
		time = get_program_time(data);
		sem_wait(data->args->sem_print);
		printf("\n%ld philosopher number %d has taken"" a right fork \n\n",time, data->philo_id);
        sem_post(data->args->sem_print);
		data->last_eat = get_program_time(data);

		// eating -->
		time = get_program_time(data);
		sem_wait(data->args->sem_print);
		printf("\n%ld philosopher number %d is"" eating\n\n",time, data->philo_id);
        sem_post(data->args->sem_print);
		usleep(data->args->eat_time * 1000);
		data->meals++;


		// put down forks -->
		sem_post(data->args->forks);
        sem_post(data->args->forks);

		//sleeping :
		time = get_program_time(data);
		sem_wait(data->args->sem_print);
		printf("\n%ld philosopher number %d is"" sleeping \n\n",time, data->philo_id);
        sem_post(data->args->sem_print);
		usleep(data->args->die_time * 1000);

		//  thinking -->
		sem_wait(data->args->sem_print);
		printf("\n%ld philosopher number %d is"" thinking \n\n",time, data->philo_id);
        sem_post(data->args->sem_print);

		// done meals -->
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
		{
			data[i]->philosophers = pid;
		}
		else if (pid == 0)
		{
			philos = malloc(sizeof(t_philos));
			philos->my_philos = data;
			philos->curr_philo = i;
			print_life(philos);
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
	int			status;
	int			i;

	i = 0;
	arguments = init_arguments(argv, argc);
	check_invalid_argument(arguments);
	data = init_data(arguments);
	data[0]->args->forks = sem_open("/my_semaphore", O_CREAT | O_EXCL , 0644, data[0]->args->philo_nbr / 2);
	long time = get_program_time(data[0]);
	printf("time %ld\n", time);
	create_philosophers(data);
    for (int i = 0; i < arguments->philo_nbr; i++)
        waitpid(data[i]->philosophers, &status, 0);
	sem_close(data[0]->args->forks);
    sem_unlink(FORK_SEM_NAME);
	return 0;
}
