/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadija-mahdi <khadija-mahdi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 02:55:47 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/28 17:01:35 by khadija-mah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_arguments	*init_arguments(char **argv, int argc)
{
	t_arguments	*arguments;

	check_arguments(argv, argc);
	arguments = malloc(sizeof(t_arguments));
	arguments->philo_nbr = ft_atoi(argv[1]);
	arguments->die_time = ft_atoi(argv[2]);
	arguments->eat_time = ft_atoi(argv[3]);
	arguments->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
	{
		arguments->mails_nbr = ft_atoi(argv[5]);
		if (!ft_strcmp(argv[5], "0"))
			exit_msg(" ta kifash 0 mile ya rebQ ! \n", 0);
	}
	arguments->start_time = get_timestamp_in_ms();
	arguments->mu_print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(arguments->mu_print, NULL);
	return (arguments);
}

t_data	**init_data(char **argv, int argc)
{
	t_arguments		*arguments;
	t_data			**data;

	arguments = init_arguments(argv, argc);
	data = malloc(sizeof(t_data *) * arguments->philo_nbr);
	int i = 0;
	while( i < arguments->philo_nbr)
	{
		data[i] = malloc(sizeof(t_data));
		data[i]->args = arguments;
		data[i]->forks = malloc(sizeof(pthread_mutex_t));
		data[i]->philosophers = malloc(sizeof(pthread_t));
		data[i]->philo_id = i + 1;
		data[i]->miles = 0;
		// data[i]->die_cheker = 0;
		
		i++;
	}
	return (data);
}

int get_id_value(t_data *data, t_philos	*philos)
{
	int id;

	if (philos->curr_philo + 1  ==  data->args->philo_nbr)
		id = 0;
	else
		id = philos->curr_philo + 1;
	return (id);
}
