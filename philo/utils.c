/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:53:07 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/24 23:34:38 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_msg(char *msg, int i)
{
	printf("%s", msg);
	exit(i);
}

void	check_plus(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv && argv[i])
	{
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

void	check_arguments(char **argv, int argc)
{
	int	i;

	if (argc == 5 || argc == 6)
	{
		if (!ft_strcmp(argv[1], "0"))
			exit_msg("ERROR : Invalid argument\n", 1);
		check_plus(argv);
	}
	else
	{
		printf("Invalid argument: Expected [5] or [6], received [%d]\n", argc);
		exit (0);
	}
}

void died(t_data *data)
{
	long total_microseconds;

	total_microseconds = get_program_time(data);
	
	pthread_mutex_lock(data->args->mu_print);
	printf("%ld philosopher number %d is died\n\n", total_microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}

void put_dwon_forks(t_data *data, t_data *next_data)
{
	pthread_mutex_unlock(next_data->forks);
	pthread_mutex_unlock(data->forks);	

}
