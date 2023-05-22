/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:58 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/22 22:21:14 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


long running_time(struct timeval start_time, struct timeval current_time) 
{
    gettimeofday(&current_time, NULL);
    long seconds = current_time.tv_sec - start_time.tv_sec;
    long microseconds = current_time.tv_usec - start_time.tv_usec;
    if (microseconds < 0)
	{
        seconds--;
        microseconds += 1000000;
    }
    long total_microseconds = (seconds * 1000000) + microseconds;
	return (total_microseconds);
}

void	*philo_created(void *arg)
{
	t_data			*data;
	int i = 0;
	struct timeval start_time, current_time;

    gettimeofday(&start_time, NULL);
	data = (t_data *) arg;
	while (1)
	{
		long total_microseconds = running_time(start_time, current_time);
		pthread_mutex_lock(data->forks);
		printf(" %ld philosopher number %d has taken a fork\n",total_microseconds, data->philo_id);
		usleep(data->args->eat_time);
		pthread_mutex_unlock(data->forks);
	}
	return (NULL);
}

void 	create_forks(t_data **data)
{
	int				i;

	i = 0;
	int philo_nbr = data[0]->args->philo_nbr;
	while (i < philo_nbr)
	{
		if (pthread_mutex_init(data[i]->forks, NULL))
			return;
		i++;
	}
}

void	create_philosophers(t_data **data)
{
	int				i;

	i = 0;
	int philo_nbr = data[0]->args->philo_nbr;
	while (i < philo_nbr)
	{
		if (pthread_create(data[i]->philosophers, NULL, philo_created,
				data[i]))
			return;
		i++;
	}
	return;
}

int	main(int argc, char **argv)
{
	t_data			**data;

	data = init_data(argv, argc);
	create_forks (data);
	create_philosophers(data);
	int i = 0;
	while (i < data[0]->args->philo_nbr)
		pthread_join(*(data[i++]->philosophers), NULL);
	
}