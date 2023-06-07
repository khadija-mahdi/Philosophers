/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 02:55:47 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/07 07:46:09 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arguments(char **argv)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	while (argv && argv[++i] && !ret)
	{
		if (!ft_strcmp(argv[i], "0"))
			ret = ret_msg("ERROR 0: Invalid argument\n");
		else if (argv[i][0] == '+')
		{
			if (!argv[i][1] || argv[i][1] == ' ')
				ret = ret_msg("ERROR : Invalid argument\n");
		}
		else if (!ft_isdigit(argv[i][0]))
			ret = ret_msg("ERROR dg: Invalid argument\n");
		j = 0;
		while (argv[i][++j] && !ret)
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				ret = ret_msg("ERROR str: Invalid argument\n");
		}
	}
	return (ret);
}

int	check_invalid_argument(t_arguments	*arguments)
{
	int		ret;

	ret = 0;
	if (arguments->philo_nbr <= 0)
		ret = ret_msg("ERROR 0: Invalid argument\n");
	else if (arguments->die_time <= 0)
		ret = ret_msg("ERROR 0: Invalid argument\n");
	else if (arguments->eat_time <= 0)
		ret = ret_msg("ERROR 0: Invalid argument\n");
	else if (arguments->sleep_time <= 0)
		ret = ret_msg("ERROR 0: Invalid argument\n");
	return (ret);
}

t_arguments	*init_arguments(char **argv, int argc)
{
	t_arguments	*arguments;

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
		data[i]->forks = malloc(sizeof(pthread_mutex_t));
		data[i]->philosophers = malloc(sizeof(pthread_t));
		data[i]->philo_id = i + 1;
		data[i]->meals = 0;
		data[i]->last_eat = 0;
		i++;
	}
	return (data);
}

void	my_usleep(useconds_t microseconds)
{
	long	time;
	long	start_time;

	start_time = get_time_in_ms();
	time = 0;
	while (time < microseconds)
	{
		usleep(300);
		time = get_time_in_ms() - start_time;
	}
}
