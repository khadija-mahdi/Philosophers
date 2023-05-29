/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:58 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/30 00:52:07 by kmahdi           ###   ########.fr       */
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
	time = get_program_time(data);
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

void	start_phlip(t_data **data, int condition)
{
	int			i;
	int			philo_nbr;
	t_philos	*philos;

	philo_nbr = data[0]->args->philo_nbr;
	i = 0;
	while (i < philo_nbr)
	{
		if ((condition && i % 2 == 0) || (!condition && i % 2 != 0))
		{
			philos = malloc(sizeof(t_philos));
			philos->my_philos = data;
			philos->curr_philo = i;
			if (pthread_create(data[i]->philosophers, NULL, philo_created,
					philos))
				return ;
		}
		i++;
	}
	return ;
}

void	create_philosophers(t_data **data)
{
	int			i;
	long		time;
	int			philo_nbr;

	start_phlip(data, 2);
	my_usleep(2 * 1000);
	start_phlip(data, 0);
	philo_nbr = data[0]->args->philo_nbr;
	i = 0;
	while (1)
	{
		time = get_program_time(data[0]);
		if ((time == data[0]->args->die_time) && (data[i]->meals == 0))
			died(data[i]);
		if (data[i]->args->meals_nbr && data[i]->meals
			&& data[i]->meals == data[0]->args->meals_nbr)
			break ;
		i++;
		if (i >= philo_nbr)
			i = 0;
	}
}

int	main(int argc, char **argv)
{
	t_data			**data;
	int				i;

	i = 0;
	data = init_data(argv, argc);
	create_forks (data);
	create_philosophers(data);
	while (i < data[0]->args->philo_nbr)
		pthread_join(*(data[i++]->philosophers), NULL);
	i = 0;
	while (i < data[0]->args->philo_nbr)
		pthread_mutex_destroy(data[i++]->forks);
}
