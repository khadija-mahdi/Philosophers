/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadija-mahdi <khadija-mahdi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:14:58 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/24 18:06:38 by khadija-mah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"




// long running_time(struct timeval start_time, struct timeval current_time) 
// {
//     gettimeofday(&current_time, NULL);
//     long seconds = current_time.tv_sec - start_time.tv_sec;
//     long microseconds = current_time.tv_usec - start_time.tv_usec;
//     if (microseconds < 0)
// 	{
//         seconds--;
//         microseconds += 1000000;
//     }
//     long total_microseconds = get_program_time(data);tal_microseconds);
// }

long get_timestamp_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
long get_program_time(t_data *data)
{
	struct timeval tv;
	long total_microseconds;
	long	microseconds;

    gettimeofday(&tv, NULL);
	microseconds = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	total_microseconds = microseconds - data->args->start_time;
	return (total_microseconds);
}

void	my_usleep(int time)
{
	long r_time;
	while (1)
	{
		usleep(time);
		r_time = get_timestamp_in_ms();
		if (r_time >= time)
			break ;
	}
}

void left_forks(t_data *data, long total_microseconds)
{
	pthread_mutex_lock(data->args->mu_print);
	printf("%ld philosopher number %d has taken a left fork \n\n",total_microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}

void right_fork(t_data *data, long total_microseconds)
{
	pthread_mutex_lock(data->args->mu_print);
	printf("%ld philosopher number %d has taken a right fork\n\n",total_microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
}

void	eating(t_data *data, long total_microseconds)
{
	pthread_mutex_lock(data->args->mu_print);
	printf("%ld philosopher number %d is eting\n\n",total_microseconds, data->philo_id);
	pthread_mutex_unlock(data->args->mu_print);
	my_usleep(data->args->eat_time * 1000);
}

void	*philo_created(void *arg)
{
	t_philos	*philos;
	t_data		*data;
	t_data		*next_data;
	int 			i;
	int				id;
	int				miles;
	long total_microseconds;
	

	i = 0;
	philos = (t_philos *) arg;
	data = philos->my_philos[philos->curr_philo];
	if (philos->curr_philo + 1  ==  data->args->philo_nbr)
		id = 0;
	else
		id = philos->curr_philo + 1;
	next_data = philos->my_philos[id];

	miles = 0;
	while (1)
	{
		// Pick up forks
			//lift_fork;
		pthread_mutex_lock(data->forks);
		total_microseconds = get_program_time(data);	
		left_forks(data, total_microseconds);
	
			//right_fork
		pthread_mutex_lock(next_data->forks);
		total_microseconds = get_program_time(data);	
		right_fork(data, total_microseconds);
		
		// Eating
		total_microseconds = get_program_time(data);	
		eating(data, total_microseconds);
		miles ++;
		
		// Put down forks
		total_microseconds = get_program_time(data);	
		pthread_mutex_unlock(next_data->forks);
		pthread_mutex_unlock(data->forks);	

		// Sleeping
		total_microseconds = get_program_time(data);	
		pthread_mutex_lock(data->args->mu_print);
		printf("%ld philosopher number %d is sleeping \n\n",total_microseconds, data->philo_id);
		pthread_mutex_unlock(data->args->mu_print);
		my_usleep (data->args->sleep_time  * 1000);
		
		// Thinking
		total_microseconds = get_program_time(data);	
		pthread_mutex_lock(data->args->mu_print);
		printf("%ld philosopher number %d is thinking \n\n",total_microseconds, data->philo_id);
		pthread_mutex_unlock(data->args->mu_print);
		
		// Check termination conditions
		total_microseconds = get_program_time(data);	
		if (total_microseconds >= data->args->eat_time || ( data->args->mails_nbr > 0 && miles >= data->args->mails_nbr))
			break;
		if ((data->args->mails_nbr > 0 && total_microseconds >= data->args->die_time) || data->args->die_time <= data->args->eat_time)
		{
			total_microseconds = get_program_time(data);	
			pthread_mutex_lock(data->args->mu_print);
			printf("%ld philosopher number %d is died\n\n", total_microseconds, data->philo_id);
			pthread_mutex_unlock(data->args->mu_print);
			break ;
		}
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
	// while (1)
	// {
	// 	long i = get_program_time(data[0]);
	// 	printf("time %ld\n", i);
	// }
	
}
