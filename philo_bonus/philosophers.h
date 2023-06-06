/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:50 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/05 22:22:54 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <semaphore.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_arguments
{
	int					philo_nbr;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					meals_nbr;
	long				start_time;
	sem_t				*forks;
	sem_t				*sem_print;
	int					status;
	int					chker;
}	t_arguments;

typedef struct s_data
{
	pid_t				philosophers;
	int					philo_id;
	struct s_arguments	*args;
	int					meals;
	long				last_eat;

}	t_data;

typedef struct m_philos
{
	t_data	**my_philos;
	int		curr_philo;
}		t_philos;

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
long			get_time_in_ms(void);
t_data			**init_data(t_arguments	*arguments);
void			print_state(t_data *data, char *msg);
int				get_id_value(t_data *data, t_philos *philos);
void			print_die(t_data *data);
void			my_usleep(useconds_t microseconds);

#endif