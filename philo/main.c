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
	struct timeval start_time, current_time;

    gettimeofday(&start_time, NULL);
	data = (t_data *) arg;
	while (1)
	{
		sleep(1);
		long total_microseconds = running_time(start_time, current_time);
		pthread_mutex_lock(data->forks);
		printf(" %ld philosopher number %d has taken a fork\n",total_microseconds, data->args->philo_nbr);
		usleep(data->args->eat_time);
		pthread_mutex_unlock(data->forks);
	}
	return (NULL);
}

pthread_mutex_t	*create_forks(t_data *data)
{
	int				i;

	i = -1;
	while (++i < data->args->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
	}
	return (data->forks);
}

pthread_t	*create_philosophers(t_data *data)
{
	int				i;

	i = -1;
	data->philosophers = malloc(sizeof(pthread_t) * data->args->philo_nbr);
	while (++i < data->args->philo_nbr)
	{
		if (pthread_create(&data->philosophers[i], NULL, philo_created,
				&data->forks))
			return (0);
		if (pthread_join(data->philosophers[i], NULL))
			return (0);
	}
	return (data->philosophers);
}

int	main(int argc, char **argv)
{
	t_data			*data;

	data = init_data(argv, argc);
	data->philosophers = create_philosophers(data);
	data->forks = create_forks (data);
}
