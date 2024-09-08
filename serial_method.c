#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "linked_list/linked_list.h"

#define MAX_VAL 65535 // 2^16 - 1
double calculateConfidenceInterval(double mean, double std_dev, int num_of_runs)
{
    double z = 1.96;  // For 95% confidence level
    return z * (std_dev / sqrt(num_of_runs));
}
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

void calculateStats(double *cpu_time_list, int num_of_runs, double *mean, double *std_dev)
{
    double sum = 0.0;
    double sum_of_squared_diff = 0.0;

    // Calculate the sum of all elements
    for (int i = 0; i < num_of_runs; i++)
    {
        sum += cpu_time_list[i];
    }

    // Calculate the mean (average)
    *mean = sum / num_of_runs;

    // Calculate the sum of squared differences from the mean
    for (int i = 0; i < num_of_runs; i++)
    {
        sum_of_squared_diff += pow(cpu_time_list[i] - *mean, 2);
    }

    // Calculate the standard deviation
    *std_dev = sqrt(sum_of_squared_diff / num_of_runs);
}

int main(int argc, char *argv[])
{
    if (argc != 8)
    {
        printf("Usage: %s <seed> <num_initializations> <num_threads> <num_member> <num_insert> <num_delete>\n", argv[0]);
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

    // Debug output to verify inputs
    // printf("Number of runs: %d\n", num_of_runs);
    // printf("Number of Initializations: %d\n", num_initializations);
    // printf("Number of Threads: %d\n", num_threads);
    // printf("Number of m: %d\n", m);
    // printf("Number of Member Calls: %d\n", num_member);
    // printf("Number of Insert Calls: %d\n", num_insert);
    // printf("Number of Delete Calls: %d\n", num_delete);

    // To measure time
    clock_t start, end;
    double cpu_time_used;
    double cpu_time_list[num_of_runs];

    for (int t = 0; t < num_of_runs; t++)
    {
        LinkedList list;
        initializeList(&list);

        // initialize all the unique values to initial insertion, and future insert functions
        int unique_vals[num_initializations + num_insert];
        generateUniqueRandomValues(unique_vals, (num_initializations + num_insert), 0, MAX_VAL);

        // Split the array
        int *initial_values = unique_vals;                      // First num_initializations elements
        int *insert_values = unique_vals + num_initializations; // Next num_insert elements
        int member_values[num_member];                          // Next num_member elements
        generateUniqueRandomValues(member_values, num_member, 0, MAX_VAL);
        int delete_values[num_delete]; // Next num_delete elements
        generateUniqueRandomValues(delete_values, num_delete, 0, MAX_VAL);

        // Initialize the list
        for (int i = 0; i < num_initializations; i++)
        {
            Insert(&list, initial_values[i]);
        }

        // Start timing
        start = clock();

        // Check membership
        for (int i = 0; i < num_member; i++)
        {
            bool isMember = Member(&list, member_values[i]);
        }

        // Insert
        for (int i = 0; i < num_insert; i++)
        {
            Insert(&list, insert_values[i]);
        }

        // Delete a value
        for (int i = 0; i < num_delete; i++)
        {
            Delete(&list, delete_values[i]);
        }

        // End timing
        end = clock();

        // Calculate total time taken
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        // printf("Total execution time: %f seconds\n", cpu_time_used);
        cpu_time_list[t] = cpu_time_used;

        // Free the linked list memory
        FreeList(&list);
    }

    double mean = 0.0;
    double std_dev = 0.0;

    // Calculate mean and standard deviation
    calculateStats(cpu_time_list, num_of_runs, &mean, &std_dev);
    // Calculate 95% confidence interval
    double confidence_interval = calculateConfidenceInterval(mean, std_dev, num_of_runs);

    // Print the results
    // printf("Mean (Average): %f\n", mean);
    // printf("Standard Deviation: %f\n", std_dev);
    printf("%d, %.6f, %.6f\n", num_threads, mean, std_dev);
    printf("95%% confidence interval: %f ± %f seconds\n", mean, confidence_interval);

    // Check if the margin of error is within ±5%
    double margin_of_error = confidence_interval / mean;
    if (margin_of_error <= 0.05)
    {
        printf("The results are accurate within ±5%% margin.\n");
    }
    else
    {
        printf("The margin of error is greater than ±5%%. More runs may be needed.\n");
    }
    return 0;
}
