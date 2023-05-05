/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:50 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/04 21:02:09 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_arguments
{
	int		philo_nbr;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		mails_nbr;
	int		forks;
}	t_arguments;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		is_string_digits(char *str);
void	exit_msg(char *msg, int i);
size_t	ft_strlen(const char *c);
int		ft_strcmp(char *s1, char *s2);
void	check_arguments(char **argv, int argc);

#endif