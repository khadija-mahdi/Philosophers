/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:02:24 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/01 21:04:47 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_invalid_argument(t_arguments	*arguments)
{
	if (arguments->philo_nbr <= 0)
		exit_msg("ERROR 1 : Invalid argument\n", 1);
	if (arguments->die_time <= 0)
		exit_msg("ERROR 1 : Invalid argument\n", 1);
	if (arguments->eat_time <= 0)
		exit_msg("ERROR 1 : Invalid argument\n", 1);
	if (arguments->sleep_time <= 0)
		exit_msg("ERROR 1 : Invalid argument\n", 1);
}

void	check_plus(char **argv)
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

void	check_arguments(char **argv, int argc)
{
	if (argc == 5 || argc == 6)
		check_plus(argv);
	else
	{
		printf("Invalid argument: Expected [5] or [6], received [%d]\n", argc);
		exit (0);
	}
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
	return (arguments);
}
long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}