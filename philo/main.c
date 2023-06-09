/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:58 by kmahdi            #+#    #+#             */
/*   Updated: 2023/06/08 03:10:37 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_created(void *arg)
{
	t_philos	*philos;
	t_data		*data;
	t_data		*next_data;
	int			id;
	long		time;

	philos = (t_philos *) arg;
	data = philos->my_philos[philos->curr_philo];
	id = get_id_value(data, philos);
	next_data = philos->my_philos[id];
	time = get_time_in_ms() - data->args->start_time;
	while (1)
	{
		pick_up_forks(data, next_data, 0);
		pick_up_forks(data, next_data, 1);
		eating(data);
		put_dwon_forks(data, next_data);
		sleeping(data);
		thinking(data);
		if (data->args->meals_nbr && data->meals
			&& data->meals == data->args->meals_nbr)
			break ;
	}
	return (NULL);
}

void	thread_rotaine(t_data **data, int start)
{
	int			i;
	int			philo_nbr;
	t_philos	*philos;

	philo_nbr = data[0]->args->philo_nbr;
	i = start;
	while (i < philo_nbr)
	{
		philos = malloc(sizeof(t_philos));
		philos->my_philos = data;
		philos->curr_philo = i;
		if (pthread_create(data[i]->philosophers, NULL, philo_created,
				philos))
			return ;
		i += 2;
	}
	return ;
}

void	create_philosophers(t_data **data)
{
	thread_rotaine(data, 0);
	my_usleep(2);
	thread_rotaine(data, 1);
}

int	main_thread(t_data **data)
{
	long			time;
	int				philo_nbr;
	int				i;

	i = 0;
	philo_nbr = data[0]->args->philo_nbr;
	while (1)
	{
		pthread_mutex_lock(data[0]->args->mu_print);
		time = get_time_in_ms() - data[0]->args->start_time;
		pthread_mutex_unlock(data[0]->args->mu_print);
		if ((time >= data[0]->args->die_time && time <= data[0]->args->die_time + 10)
			&& ((time - data[i]->last_eat) >= data[i]->args->die_time)
			&& !data[i]->is_eating)
		{
			died(data[i]);
			return (-1);
		}
		if (data[i]->args->meals_nbr && data[i]->meals
			&& data[i]->meals == data[0]->args->meals_nbr)
			break ;
		i++;
		if (i >= philo_nbr)
			i = 0;
		usleep(1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_arguments		*arguments;
	t_data			**data;
	int				i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		arguments = init_arguments(argv, argc);
		if (check_arguments(argv) || check_invalid_argument(arguments))
			return (1);
		data = init_data(arguments);
		create_forks (data);
		arguments->start_time = get_time_in_ms();
		create_philosophers(data);
		if (main_thread(data) == -1)
			return (0);
		while (i < data[0]->args->philo_nbr)
			pthread_join(*(data[i++]->philosophers), NULL);
		i = 0;
		while (i < data[0]->args->philo_nbr)
			pthread_mutex_destroy(data[i++]->forks);
	}
	else
		printf("Invalid argument: Expected [5] or [6], received [%d]\n", argc);
}
