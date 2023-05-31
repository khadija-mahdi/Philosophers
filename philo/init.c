/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 02:55:47 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/31 22:52:22 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_arguments(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv && argv[i])
	{
		if (!ft_strcmp(argv[i], "0"))
			exit_msg("ERROR : Invalid argument\n", 1);
		if (argv[i][0] == '+')
		{
			if (!argv[i][1] || argv[i][1] == ' ')
				exit_msg("ERROR : Invalid argument\n", 1);
		}
		else if (!ft_isdigit(argv[i][0]))
			exit_msg("ERROR : Invalid argument\n", 1);
		j = 1;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				exit_msg("ERROR : Invalid argument\n", 1);
			j++;
		}
		i++;
	}
}

void	check_invalid_argument(t_arguments	*arguments)
{
	if (arguments->philo_nbr <= 0)
		exit_msg("ERROR : Invalid argument\n", 1);
	if (arguments->die_time <= 0)
		exit_msg("ERROR : Invalid argument\n", 1);
	if (arguments->eat_time <= 0)
		exit_msg("ERROR : Invalid argument\n", 1);
	if (arguments->sleep_time <= 0)
		exit_msg("ERROR : Invalid argument\n", 1);
}

t_arguments	*init_arguments(char **argv, int argc)
{
	t_arguments	*arguments;

	if (argc == 5 || argc == 6)
		check_arguments(argv);
	else
	{
		printf("Invalid argument: Expected [5] or [6], received [%d]\n", argc);
		exit (1);
	}
	arguments = malloc(sizeof(t_arguments));
	arguments->start_time = get_time_in_ms();
	arguments->philo_nbr = ft_atoi(argv[1]);
	arguments->die_time = ft_atoi(argv[2]);
	arguments->eat_time = ft_atoi(argv[3]);
	arguments->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		arguments->meals_nbr = ft_atoi(argv[5]);
	arguments->mu_print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(arguments->mu_print, NULL);
	return (arguments);
}

t_data	**init_data(char **argv, int argc)
{
	t_arguments		*arguments;
	t_data			**data;
	int				i;

	i = 0;
	arguments = init_arguments(argv, argc);
	check_invalid_argument(arguments);
	data = malloc(sizeof(t_data *) * arguments->philo_nbr);
	while (i < arguments->philo_nbr)
	{
		data[i] = malloc(sizeof(t_data));
		data[i]->args = arguments;
		data[i]->forks = malloc(sizeof(pthread_mutex_t));
		data[i]->philosophers = malloc(sizeof(pthread_t));
		data[i]->philo_id = i + 1;
		data[i]->meals = 0;
		data[i]->last_eat = 0;
		i++;
	}
	return (data);
}

void	my_usleep(useconds_t microseconds, t_data *data)
{
	(void) data;
	usleep(microseconds);
}

// void	usleep(int time, t_data *data)
// {
// 	// long	r_time;
// 	(void)	data;
// 	// while (1)
// 	// {
// 		usleep(time);
// 		// r_time = get_program_time(data);
// 		// printf("r_time : %ld time %d\n", r_time, time);
// 		// if ((r_time * 1000 ) >= time)
// 	// 		break ;
// 	// }
// }
