/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:55:28 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/29 20:19:57 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_program_time(t_data *data)
{
	long	total_microseconds;
	long	microseconds;

	microseconds = get_timestamp_in_ms();
	total_microseconds = microseconds - data->args->start_time;
	return (total_microseconds);
}

void	my_usleep(int time)
{
	long	r_time;

	while (1)
	{
		usleep(time);
		r_time = get_timestamp_in_ms();
		if (r_time >= time)
			break ;
	}
}
