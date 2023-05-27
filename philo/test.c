/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:29:31 by kmahdi            #+#    #+#             */
/*   Updated: 2023/05/26 22:24:07 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_NAME_LENGTH 20

typedef struct {
    int id;
    pthread_mutex_t* left_fork;
    pthread_mutex_t* right_fork;
} Philosopher;

typedef struct {
    Philosopher* philosophers;
    pthread_mutex_t* forks;
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_each_philosopher_must_eat;
} DiningTable;

int get_timestamp_in_ms() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_log(int timestamp, int philosopher_id, const char* action) {
    printf("%d %d %s\n", timestamp, philosopher_id, action);
    fflush(stdout);
}

void* philosopher_thread(void* arg) {
    Philosopher* philosopher = (Philosopher*) arg;
    DiningTable* table = (DiningTable*) philosopher;

    int num_times_ate = 0;
    int timestamp;

    while (1) {
        // Thinking
        timestamp = get_timestamp_in_ms();
        print_log(timestamp, philosopher->id, "is thinking");
        usleep(rand() % 2000 + 1000);  // Sleep for 1-3 seconds

        // Pick up forks
        timestamp = get_timestamp_in_ms();
        pthread_mutex_lock(philosopher->left_fork);
        print_log(timestamp, philosopher->id, "has taken a fork");

        timestamp = get_timestamp_in_ms();
        pthread_mutex_lock(philosopher->right_fork);
        print_log(timestamp, philosopher->id, "has taken a fork");

        // Eating
        timestamp = get_timestamp_in_ms();
        print_log(timestamp, philosopher->id, "is eating");
        usleep(table->time_to_eat * 1000);  // Sleep for time_to_eat milliseconds
        num_times_ate++;

        // Put down forks
        pthread_mutex_unlock(philosopher->left_fork);
        pthread_mutex_unlock(philosopher->right_fork);

        // Check termination conditions
        if (table->num_times_each_philosopher_must_eat > 0 &&
            num_times_ate >= table->num_times_each_philosopher_must_eat) {
            break;  // Finished eating required number of times
        }

        if (table->time_to_die > 0 && get_timestamp_in_ms() - timestamp > table->time_to_die)
		{
            timestamp = get_timestamp_in_ms();
            print_log(timestamp, philosopher->id, "died");
            break;  // Philosopher died
        }

        // Sleeping
        timestamp = get_timestamp_in_ms();
        print_log(timestamp, philosopher->id, "is sleeping");
        usleep(table->time_to_sleep * 1000);  // Sleep for time_to_sleep milliseconds
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    int num_philosophers = atoi(argv[1]);
   
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);
    int num_times_each_philosopher_must_eat = (argc == 6) ? atoi(argv[5]) : -1;

    // Initialize dining table
    DiningTable table;
    table.num_philosophers = num_philosophers;
    table.time_to_die = time_to_die;
    table.time_to_eat = time_to_eat;
    table.time_to_sleep = time_to_sleep;
    table.num_times_each_philosopher_must_eat = num_times_each_philosopher_must_eat;

    // Create an array of mutex locks for forks
    pthread_mutex_t forks[num_philosophers];
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    table.forks = forks;

    // Create an array of philosophers
    Philosopher philosophers[num_philosophers];
    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i].id = i + 1;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
    }
    table.philosophers = philosophers;

    // Create threads for philosophers
    pthread_t philosopher_threads[num_philosophers];
    for (int i = 0; i < num_philosophers; i++) {
        pthread_create(&philosopher_threads[i], NULL, philosopher_thread, (void*) &philosophers[i]);
    }

    // Wait for philosophers to finish
    for (int i = 0; i < num_philosophers; i++) {
        pthread_join(philosopher_threads[i], NULL);
    }

    // Clean up mutex locks
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
