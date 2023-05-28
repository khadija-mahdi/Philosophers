/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadija-mahdi <khadija-mahdi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:58 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/28 17:02:38 by khadija-mah      ###   ########.fr       */
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
		left_forks(data);
		right_fork(data, next_data);
		data->die_cheker = get_program_time(data);
		pthread_mutex_lock(data->args->mu_print);
		printf("last eat : %ld philosopher  : %d  \n\n",data->die_cheker, data->philo_id);
		pthread_mutex_unlock(data->args->mu_print);
		eating(data);
		put_dwon_forks(data, next_data);
		sleeping(data);
		thinking(data);
		if (data->args->mails_nbr && data->miles && data->miles  ==  data->args->mails_nbr)
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
			return;
		i++;
	}
}

void start_phlip(t_data **data, int condition)
{
	int			i;
	t_philos	*philos;

	i = 0;
	int philo_nbr = data[0]->args->philo_nbr;
	while (i < philo_nbr)
	{
		if((condition && i % 2 == 0) || (!condition && i % 2 != 0))
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
	return;
}

void	create_philosophers(t_data **data)
{
	long		time;

	start_phlip(data, 2);
	my_usleep(2 * 1000);
	start_phlip(data, 0);
	int philo_nbr = data[0]->args->philo_nbr;
	int i = 0;
	while (1)
	{
		time = get_program_time(data[0]);
		// printf("time %ld , chker  %ld , died cond : == %ld\n", time, data[i]->die_cheker, (time - data[i]->die_cheker));
		if ((time - data[i]->die_cheker) > data[i]->args->die_time)
		{
			died(data[i]);
		}
		if (data[i]->args->mails_nbr && data[i]->miles && data[i]->miles == data[0]->args->mails_nbr)
			break;
		i++;
		if(i >= philo_nbr)
			i = 0;
	}
}

int	main(int argc, char **argv)
{
	t_data			**data;

	data = init_data(argv, argc);
	create_forks (data);
	create_philosophers(data);
	//check
	int i = 0;
	while (i <  data[0]->args->philo_nbr)
		pthread_join(*(data[i++]->philosophers), NULL);
	i = 0;
	 while (i < data[0]->args->philo_nbr)
	 	pthread_mutex_destroy(data[i++]->forks);
	
}
