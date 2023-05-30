/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:53:07 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/30 04:15:04 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_msg(char *msg, int i)
{
	printf("%s", msg);
	exit(i);
}

void	my_usleep(int time)
{
	long	r_time;

	while (1)
	{
		usleep(time);
		r_time = get_time_in_ms();
		if (r_time >= time)
			break ;
	}
}
