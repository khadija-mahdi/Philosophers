/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:49:07 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/06 02:14:29 by kmahdi           ###   ########.fr       */
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
	arguments->forks = sem_open("forks", O_CREAT | O_EXCL,
			0644, (arguments->philo_nbr / 2));
	if (arguments->forks == SEM_FAILED)
		exit_msg("sem_forks error", 1);
	arguments->sem_print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (arguments->sem_print == SEM_FAILED)
		exit_msg("sem_printf error", 1);
	return (arguments);
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

void	print_state(t_data *data, char *msg)
{
	long	time;

	time = get_program_time(data);
	sem_wait(data->args->sem_print);
	printf("\n%ld philosopher number %d %s\n\n", time, data->philo_id, msg);
	sem_post(data->args->sem_print);
}
