#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include "linked_list/linked_list.h"

#define MAX_VAL 65535 // 2^16 - 1

// Global variables
LinkedList list;
int *member_values;
int num_member_per_thread;
int *insert_values;
int num_insert_per_thread;
int *delete_values;
int num_delete_per_thread;
pthread_mutex_t list_mutex; // Mutex for synchronizing access to the linked list

// Function to check if a value already exists in the array
bool isUnique(int *arr, int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            return false;
        }
    }
    return true;
}

// Function to generate unique random values within a specified range
void generateUniqueRandomValues(int *arr, int n, int min_val, int max_val)
{
    int count = 0;
    while (count < n)
    {
        int rand_val = min_val + rand() % (max_val - min_val + 1);
        if (isUnique(arr, count, rand_val))
        {
            arr[count] = rand_val;
            count++;
        }
    }
}

// Thread function for parallel operations
void *threadFunc(void *rank)
{
    long my_rank = (long)rank;

    int mem_start = (my_rank * num_member_per_thread);
    int mem_end = (my_rank + 1) * num_member_per_thread;

    int ins_start = (my_rank * num_insert_per_thread);
    int ins_end = (my_rank + 1) * num_insert_per_thread;

    int del_start = (my_rank * num_delete_per_thread);
    int del_end = (my_rank + 1) * num_delete_per_thread;

    // Member operation
    for (int i = mem_start; i < mem_end; i++)
    {
        pthread_mutex_lock(&list_mutex);
        Member(&list, member_values[i]);
        pthread_mutex_unlock(&list_mutex);
    }

    // Insert operation
    for (int i = ins_start; i < ins_end; i++)
    {
        pthread_mutex_lock(&list_mutex);
        Insert(&list, insert_values[i]);
        pthread_mutex_unlock(&list_mutex);
    }

    // Delete operation
    for (int i = del_start; i < del_end; i++)
    {
        pthread_mutex_lock(&list_mutex);
        Delete(&list, delete_values[i]);
        pthread_mutex_unlock(&list_mutex);
    }

    return NULL;
}

void calculateStats(double *cpu_time_list, int num_of_runs, double *mean, double *std_dev)
{
    double sum = 0.0;
    double sum_of_squared_diff = 0.0;

    for (int i = 0; i < num_of_runs; i++)
    {
        sum += cpu_time_list[i];
    }

    *mean = sum / num_of_runs;

    for (int i = 0; i < num_of_runs; i++)
    {
        sum_of_squared_diff += pow(cpu_time_list[i] - *mean, 2);
    }

    *std_dev = sqrt(sum_of_squared_diff / num_of_runs);
}

int main(int argc, char *argv[])
{
    if (argc != 8)
    {
        printf("Usage: %s <num_of_runs> <num_initializations> <num_threads> <m> <frac_member> <frac_insert> <frac_delete>\n", argv[0]);
        return -1;
    }

    int num_of_runs = strtol(argv[1], NULL, 10);
    int num_initializations = strtol(argv[2], NULL, 10);
    int num_threads = strtol(argv[3], NULL, 10);
    int m = strtol(argv[4], NULL, 10);
    double frac_member = strtod(argv[5], NULL);
    double frac_insert = strtod(argv[6], NULL);
    double frac_delete = strtod(argv[7], NULL);

    int num_member = (int)(m * frac_member);
    int num_insert = (int)(m * frac_insert);
    int num_delete = (int)(m * frac_delete);

    printf("Number of runs: %d\n", num_of_runs);
    printf("Number of Initializations: %d\n", num_initializations);
    printf("Number of Threads: %d\n", num_threads);
    printf("Number of m: %d\n", m);
    printf("Number of Member Calls: %d\n", num_member);
    printf("Number of Insert Calls: %d\n", num_insert);
    printf("Number of Delete Calls: %d\n", num_delete);

    pthread_t threads[num_threads];

    pthread_mutex_init(&list_mutex, NULL);

    clock_t start, end;
    double cpu_time_used;
    double cpu_time_list[num_of_runs];

    for (int t = 0; t < num_of_runs; t++)
    {
        int unique_vals[num_initializations + num_insert];
        generateUniqueRandomValues(unique_vals, (num_initializations + num_insert), 0, MAX_VAL);

        int *initial_values = unique_vals;
        insert_values = unique_vals + num_initializations;
        member_values = (int *)malloc(num_member * sizeof(int));
        generateUniqueRandomValues(member_values, num_member, 0, MAX_VAL);
        delete_values = (int *)malloc(num_delete * sizeof(int));
        generateUniqueRandomValues(delete_values, num_delete, 0, MAX_VAL);

        for (int i = 0; i < num_initializations; i++)
        {
            Insert(&list, initial_values[i]);
        }

        // Calculate operations per thread
        num_member_per_thread = num_member / num_threads;
        num_insert_per_thread = num_insert / num_threads;
        num_delete_per_thread = num_delete / num_threads;

        start = clock();

        for (int i = 0; i < num_threads; i++)
        {
            pthread_create(&threads[i], NULL, threadFunc, (void *)i);
        }

        for (int i = 0; i < num_threads; i++)
        {
            pthread_join(threads[i], NULL);
        }

        end = clock();

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Total execution time: %f seconds\n", cpu_time_used);
        cpu_time_list[t] = cpu_time_used;

        // PrintList(&list);

        // Free the linked list memory
        FreeList(&list);
    }

    double mean = 0.0;
    double std_dev = 0.0;

    calculateStats(cpu_time_list, num_of_runs, &mean, &std_dev);

    printf("Mean (Average): %f\n", mean);
    printf("Standard Deviation: %f\n", std_dev);

    pthread_mutex_destroy(&list_mutex);

    free(member_values);
    free(delete_values);

    return 0;
}
