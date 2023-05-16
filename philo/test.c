/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:29:31 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/15 23:42:35 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void *threads(void *t)
{
	int mutex = (int )t;
	int i = 0;
	while (i < 100)
	{
		pthread_mutex_lock(&mutex);
		printf("in lock :%d\n", mutex);
		pthread_mutex_unlock(&mutex);
		printf("after lock :%d\n",mutex);
		i++;
	}
	printf("we creadted thredes :) !!");
}

int	main(void)
{
	pthread_mutex_t	mutex;
	pthread_t	t1;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, &threads, &mutex);
	pthread_join(t1, NULL);
	pthread_mutex_destroy(&mutex);
}