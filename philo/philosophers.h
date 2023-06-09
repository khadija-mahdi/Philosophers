/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:50 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/08 01:07:24 by kmahdi           ###   ########.fr       */
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
	int					forks;
	long				start_time;
	pthread_mutex_t		*mu_print;
}	t_arguments;

typedef struct s_data
{
	pthread_mutex_t		*forks;
	pthread_t			*philosophers;
	int					philo_id;
	struct s_arguments	*args;
	int					meals;
	long				last_eat;
	int					is_eating;

}	t_data;

typedef struct m_philos
{
	t_data	**my_philos;
	int		curr_philo;
}		t_philos;

int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				is_string_digits(char *str);
int				ret_msg(char *msg);
size_t			ft_strlen(const char *c);
int				ft_strcmp(char *s1, char *s2);
t_arguments		*init_arguments(char **argv, int argc);
t_data			**init_data(t_arguments	*arguments);
void			*philo_created(void *arg);
long			get_time_in_ms(void);
void			my_usleep(useconds_t microseconds);
void			eating(t_data *data);
void			sleeping(t_data *data);
void			died(t_data *data);
void			thinking(t_data *data);
void			put_dwon_forks(t_data *data, t_data *next_data);
int				get_id_value(t_data *data, t_philos	*philos);
void			pick_up_forks(t_data *data, t_data *next_data, int left);
void			create_forks(t_data **data);
int				check_invalid_argument(t_arguments	*arguments);
int				check_arguments(char **argv);

#endif