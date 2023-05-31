/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:29:39 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/31 21:47:20 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pick_up_forks(t_data *data, t_data *next_data, int left)
{
	long	microseconds;

	if (left == 0)
		pthread_mutex_lock(data->forks);
	else
		pthread_mutex_lock(next_data->forks);
	microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("\n%ld philosopher number %d has taken"
		" a fork \n\n", microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}

void	eating(t_data *data)
{
	long	microseconds;

	microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("\n%ld philosopher number %d is"
		" eating\n\n", microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
	usleep(data->args->eat_time * 1000);
	data->meals++;
}

void	sleeping(t_data *data)
{
	long	microseconds;

	microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("\n%ld philosopher number %d is"
		" sleeping \n\n", microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
	usleep(data->args->sleep_time * 1000);
}

void	thinking(t_data *data)
{
	long	microseconds;

	microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("\n%ld philosopher number %d is"
		" thinking \n\n", microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}

void	died(t_data *data)
{
	long	microseconds;

	microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("\n%ld philosopher number %d is"
		" died\n\n", microseconds, data->philo_id);
	exit (0);
}
