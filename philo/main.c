/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:58 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/24 23:35:04 by kmahdi           ###   ########.fr       */
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
	long total_microseconds;
	
	philos = (t_philos *) arg;
	data = philos->my_philos[philos->curr_philo];
	id = get_id_value(data, philos);
	next_data = philos->my_philos[id];

	miles = 0;
	while (1)
	{
		left_forks(data);
		if ( data->args->philo_nbr == 1)
		{
			died(data);
			break ;
		}
		right_fork(data, next_data);	
		eating(data);
		miles ++;
		put_dwon_forks(data, next_data);	
		sleeping(data);
		thinking(data);
		// died 
		total_microseconds = get_program_time(data);	
		if ((((total_microseconds >= data->args->die_time) || data->args->die_time <= data->args->eat_time) && !miles))
		{
			died(data);
			break ;
		}	
		// Check termination conditions
		if (total_microseconds >= data->args->eat_time || ( data->args->mails_nbr > 0 && miles >= data->args->mails_nbr))
			break;
		if (miles  < data->args->mails_nbr)
			continue ;
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
	int				i;

	i = 0;
	int philo_nbr = data[0]->args->philo_nbr;
	while (i < philo_nbr)
	{
		if((condition && i % 2 == 0) || (!condition && i % 2 != 0 ))
		{
			t_philos *philos = malloc(sizeof(t_philos));
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
