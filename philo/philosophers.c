/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:55:28 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/30 23:38:59 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_id_value(t_data *data, t_philos	*philos)
{
	int	id;

	if (philos->curr_philo + 1 == data->args->philo_nbr)
		id = 0;
	else
		id = philos->curr_philo + 1;
	return (id);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_program_time(t_data *data)
{
	long	total_microseconds;
	long	microseconds;

	microseconds = get_time_in_ms();
	total_microseconds = microseconds - data->args->start_time;
	return (total_microseconds);
}

void	put_dwon_forks(t_data *data, t_data *next_data)
{
	pthread_mutex_unlock(data->forks);
	pthread_mutex_unlock(next_data->forks);
}

void	create_forks(t_data **data)
{
	int	i;
	int	philo_nbr;

	i = 0;
	philo_nbr = data[0]->args->philo_nbr;
	while (i < philo_nbr)
	{
		if (pthread_mutex_init(data[i]->forks, NULL))
			return ;
		i++;
	}
}
