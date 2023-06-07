/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:29:39 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/07 01:23:43 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pick_up_forks(t_data *data, t_data *next_data, int left)
{
	long	microseconds;

	if (left == 0)
		pthread_mutex_lock(data->forks);
	else
	{
		pthread_mutex_lock(next_data->forks);
	}
	pthread_mutex_lock(data->args->mu_print);
	microseconds = get_time_in_ms() - data->args->start_time;
	printf("%ld philosopher number %d has taken"
		" a fork \n", microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}

void	eating(t_data *data)
{
	long	microseconds;

	data->last_eat = get_time_in_ms() - data->args->start_time;
	pthread_mutex_lock(data->args->mu_print);
	microseconds = get_time_in_ms() - data->args->start_time;
	printf("%ld philosopher number %d is"
		" eating\n", microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
	my_usleep(data->args->eat_time);
	data->meals++;
}

void	sleeping(t_data *data)
{
	long	microseconds;

	pthread_mutex_lock(data->args->mu_print);
	microseconds = get_time_in_ms() - data->args->start_time;
	printf("%ld philosopher number %d is"
		" sleeping \n", microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
	my_usleep(data->args->sleep_time);
}

void	thinking(t_data *data)
{
	long	microseconds;

	pthread_mutex_lock(data->args->mu_print);
	microseconds = get_time_in_ms() - data->args->start_time;
	printf("%ld philosopher number %d is"
		" thinking \n", microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}

void	died(t_data *data)
{
	long	microseconds;

	pthread_mutex_lock(data->args->mu_print);
	microseconds = get_time_in_ms() - data->args->start_time;
	printf("%ld philosopher number %d"
		" died\n", microseconds, data->philo_id);
}
