/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 02:55:47 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/16 03:02:56 by kmahdi           ###   ########.fr       */
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
		arguments->mails_nbr = ft_atoi(argv[5]);
	return (arguments);
}

t_data	*init_data(char **argv, int argc)
{
	t_arguments		*arguments;
	t_data			**data;

	arguments = init_arguments(argv, argc);
	data = malloc(sizeof(t_data *) * arguments->philo_nbr);
	int i = 0;
	while( i < arguments->philo_nbr)
	{
		t_data *dt = malloc(sizeof(t_data));
		dt->args = init_arguments(argv, argc);
		dt->forks = malloc(sizeof(pthread_mutex_t));
		dt->philosophers = malloc(sizeof(pthread_t));
		data[i] = dt;
		i++;
	}
	return (data);
}
