/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:49:07 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/07 21:28:02 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

t_arguments	*init_arguments(char **argv, int argc)
{
	t_arguments	*arguments;

	check_arguments(argv, argc);
	arguments = malloc(sizeof(t_arguments));
	arguments->start_time = get_time_in_ms();
	arguments->philo_nbr = ft_atoi(argv[1]);
	arguments->die_time = ft_atoi(argv[2]);
	arguments->eat_time = ft_atoi(argv[3]);
	arguments->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		arguments->meals_nbr = ft_atoi(argv[5]);
	else
		arguments->meals_nbr = 0;
	if (arguments->philo_nbr > 1)
		arguments->forks = sem_open("forks", O_CREAT | O_EXCL,
				0644, (arguments->philo_nbr / 2));
	else
		arguments->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, 1);
	if (arguments->forks == SEM_FAILED)
		exit_msg("sem_forks error", 1);
	arguments->sem_print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (arguments->sem_print == SEM_FAILED)
		exit_msg("sem_printf error", 1);
	return (arguments);
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

void	print_state(t_data *data, char *msg)
{
	long	time;

	time = get_time_in_ms() - data->args->start_time;
	sem_wait(data->args->sem_print);
	printf("%ld philosopher number %d %s\n", time, data->philo_id, msg);
	sem_post(data->args->sem_print);
}

void	my_usleep(useconds_t microseconds)
{
	long	time;
	long	start_time;

	start_time = get_time_in_ms();
	time = 0;
	while (time < microseconds)
	{
		usleep(250);
		time = get_time_in_ms() - start_time;
	}
}
