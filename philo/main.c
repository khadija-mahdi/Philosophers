/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:58 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/16 03:58:25 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_created(void *arg)
{
	t_data			*data;

	data = (t_data *) arg;
	printf(" philosopher number %d has taken a fork\n",data->args->philo_nbr);
	pthread_mutex_lock(data->forks);
	usleep(data->args->eat_time * 1000);
	pthread_mutex_unlock(data->forks);
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


// void	*philo_created(void *arg)
// {
// 	t_data			*data;
// 	struct timeval	start_time;
// 	struct timeval	end_time;
// 	long			elapsed_time;

// 	gettimeofday(&start_time, NULL);
// 	data = (t_data *) arg;
// 	printf(" %ld philosopher number %d has taken a fork\n", elapsed_time ,data->args->philo_nbr);
// 	pthread_mutex_lock(data->forks);
// 	printf(" %ld philosopher number %d has taken a fork\n", elapsed_time ,data->args->philo_nbr);
// 	usleep(data->args->eat_time * 1000);
// 	pthread_mutex_unlock(data->forks);
// 	gettimeofday(&end_time, NULL);
//     elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000;
//     elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000;
// 	printf(" %ld philosopher number %d has taken a fork\n", elapsed_time ,data->args->philo_nbr);
//     // printf("Elapsed time: %ld ms\n", elapsed_time);
// 	return (NULL);
// }