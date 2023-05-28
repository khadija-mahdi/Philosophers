/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadija-mahdi <khadija-mahdi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:29:39 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/28 17:06:46 by khadija-mah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void left_forks(t_data *data)
{
	long total_microseconds;

	pthread_mutex_lock(data->forks);
	total_microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("%ld philosopher number %d has taken a left fork \n\n",total_microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}

void right_fork(t_data *data, t_data *next_data)
{
	long total_microseconds;
	pthread_mutex_lock(next_data->forks);
	total_microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("%ld philosopher number %d has taken a right fork\n\n",total_microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}

void	eating(t_data *data)
{
	long total_microseconds;

	total_microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("%ld philosopher number %d is eating\n\n",total_microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
	my_usleep(data->args->eat_time * 1000);
	data->miles++;
}

void	sleeping(t_data *data)
{
	long total_microseconds;

	total_microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("%ld philosopher number %d is sleeping \n\n",total_microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
	my_usleep (data->args->sleep_time  * 1000);
}

void	thinking(t_data *data)
{
	long total_microseconds;

	total_microseconds = get_program_time(data);
	pthread_mutex_lock(data->args->mu_print);
	printf("%ld philosopher number %d is thinking \n\n",total_microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}
