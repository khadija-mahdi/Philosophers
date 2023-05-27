/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:58 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/27 07:49:42 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_created(void *arg)
{
	t_philos	*philos;
	t_data		*data;
	t_data		*next_data;
	int				id;
	int				miles;
	long time;
	
	philos = (t_philos *) arg;
	data = philos->my_philos[philos->curr_philo];
	id = get_id_value(data, philos);
	next_data = philos->my_philos[id];

	miles = 0;
	time = get_program_time(data);
	while (1)
	{
		// pthread_mutex_lock(data->args->mu_print);
		// data->args->die_cheker = 0;
		// pthread_mutex_unlock(data->args->mu_print);
		left_forks(data);
		right_fork(data, next_data);
		eating(data);
		pthread_mutex_lock(data->args->mu_print);
		data->args->die_cheker = 1;
		pthread_mutex_unlock(data->args->mu_print);
		pthread_mutex_lock(data->args->mu_print);
		data->args->miles++;
		pthread_mutex_unlock(data->args->mu_print);
		put_dwon_forks(data, next_data);
		sleeping(data);
		thinking(data);
		if (data->args->mails_nbr && data->args->miles && data->args->miles  >=  data->args->mails_nbr)
			break;
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
		{
			printf("failed to creat mutex \n");
			return;
		}
		i++;
	}
}

void start_phlip(t_data **data, int condition)
{
	int			i;
	long		time;
	t_philos	*philos;

	i = 0;
	int philo_nbr = data[0]->args->philo_nbr;
	while (i < philo_nbr)
	{
		if((condition && i % 2 == 0) || (!condition && i % 2 != 0 ))
		{
			philos = malloc(sizeof(t_philos));
			philos->my_philos = data;
			philos->curr_philo = i;
			if (pthread_create(data[i]->philosophers, NULL, philo_created,
					philos))
				return;
		}
		i++;
	}
	while (1)
	{
		time = get_program_time(philos->my_philos[philos->curr_philo]);
		if (time == philos->my_philos[philos->curr_philo]->args->die_time 
			&& !philos->my_philos[philos->curr_philo]->args->die_cheker)
			died(philos->my_philos[philos->curr_philo]);
		if (philos->my_philos[philos->curr_philo]->args->miles == philos->my_philos[philos->curr_philo]->args->mails_nbr)
			break;

	}
	return;
}

void	create_philosophers(t_data **data)
{
		
	start_phlip(data, 1);
	my_usleep(2 * 1000);
	start_phlip(data, 0);
}

int	main(int argc, char **argv)
{
	t_data			**data;

	data = init_data(argv, argc);
	create_forks (data);
	create_philosophers(data);
	int i = 0;
	while (i <  data[0]->args->philo_nbr)
		pthread_join(*(data[i++]->philosophers), NULL);
	i = 0;
	 while (i < data[0]->args->philo_nbr)
	 	pthread_mutex_destroy(data[i++]->forks);
	
}
