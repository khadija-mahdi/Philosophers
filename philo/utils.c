/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:53:07 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/04 18:56:08 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_string_digits(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	exit_msg(char *msg, int i)
{
	printf("%s", msg);
	exit(i);
}

void	check_arguments(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc != 6)
	{
		printf("Invalid argument: Expected [6], received [%d]\n", argc);
		exit (0);
	}
	while (i < 6)
	{
		if (!ft_strcmp(argv[i], "0"))
			exit_msg("Invalid arguments: '0' not a valid", 0);
		if (!is_string_digits(argv[1]))
			exit_msg("Invalid philosophers: Expected a positive number", 0);
		else if (!is_string_digits(argv[2]))
			exit_msg("Invalid die_time: Expected a positive number", 0);
		else if (!is_string_digits(argv[3]))
			exit_msg("Invalid eat_time: Expected a positive number", 0);
		else if (!is_string_digits(argv[4]))
			exit_msg("Invalid sleep_time: Expected a positive number", 0);
		else if (!is_string_digits(argv[5]))
			exit_msg("Invalid mails: Expected a positive number", 0);
		i++;
	}
}
