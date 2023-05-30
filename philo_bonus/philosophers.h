/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:50 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/30 05:27:41 by kmahdi           ###   ########.fr       */
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
	int					philo_nbr;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					meals_nbr;
}	t_arguments;

int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				is_string_digits(char *str);
void			exit_msg(char *msg, int i);
size_t			ft_strlen(const char *c);
int				ft_strcmp(char *s1, char *s2);
void			check_arguments(char **argv, int argc);
void			exit_msg(char *msg, int i);
void			check_invalid_argument(t_arguments	*arguments);
t_arguments		*init_arguments(char **argv, int argc);

#endif