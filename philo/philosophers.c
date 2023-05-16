/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:55:28 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/16 03:58:39 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <pthread.h>

#define N 5   // Number of philosophers

pthread_mutex_t forks[N];  // Mutex locks for each fork

void get_forks(int i) {
    // Philosopher i picks up the forks with indices i and (i+1)%N
    pthread_mutex_lock(&forks[i]);
    pthread_mutex_lock(&forks[(i+1)%N]);
}

void put_forks(int i) {
    // Philosopher i puts down the forks with indices i and (i+1)%N
    pthread_mutex_unlock(&forks[i]);
    pthread_mutex_unlock(&forks[(i+1)%N]);
}

void* philosopher(void* arg) {
    int i = *(int*) arg;
    while (1) {
        // Philosopher i is thinking
        // ...

        // Philosopher i wants to eat
        get_forks(i);

        // Philosopher i is eating
        // ...

        // Philosopher i has finished eating
        put_forks(i);
    }
}

// int main() {
//     int i;
//     pthread_t threads[N];

//     // Initialize mutex locks for each fork
//     for (i = 0; i < N; i++) {
//         pthread_mutex_init(&forks[i], NULL);
//     }

//     // Create threads for each philosopher
//     for (i = 0; i < N; i++) {
//         pthread_create(&threads[i], NULL, philosopher, &i);
//     }

//     // Wait for threads to finish
//     for (i = 0; i < N; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     // Destroy mutex locks for each fork
//     for (i = 0; i < N; i++) {
//         pthread_mutex_destroy(&forks[i]);
//     }

//     return 0;
// }

