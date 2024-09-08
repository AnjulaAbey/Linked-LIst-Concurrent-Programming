# Concurrent Programming Lab - Performance Measurement

## Overview

This program measures the execution time of different operations (`Member`, `Insert`, `Delete`) on a linked list using multi-threading. It compares performance across various configurations of threads and operation ratios while ensuring that results are accurate within ±5% and a 95% confidence level.

## Requirements

### Prerequisites

Ensure that you have the following installed on your machine:

- **GCC (GNU Compiler Collection)**
- **POSIX Threads (pthread) Library**
- **Make (optional)**

You can install them on Ubuntu using:

```bash
sudo apt-get update
sudo apt-get install build-essential
```

### 1. Serial program

#### Compilcation

To compile the code, run the following command in the project directory:

```bash
gcc -o serial_method serial_method.c linked_list/linked_list.c -lm
```

This will generate an executable file named `serial_method`.


#### Usage

##### Running the program

The program accepts the following command-line arguments:

```bash
./serial_method <num_of_runs> <num_initializations> <num_threads> <m> <frac_member> <frac_insert> <frac_delete>
```
| Argument            | Description                                                                             |
|---------------------|-----------------------------------------------------------------------------------------|
| `<num_of_runs>`      | Number of times to repeat the experiment to ensure accurate measurements.               |
| `<num_initializations>` | Number of initial insertions into the linked list.                                    |
| `<num_threads>`      | Number of threads to run concurrently.                                                  |
| `<m>`                | Total number of operations (Member, Insert, Delete) to perform.                         |
| `<frac_member>`      | Fraction of `m` operations that are `Member` operations (between 0 and 1).              |
| `<frac_insert>`      | Fraction of `m` operations that are `Insert` operations (between 0 and 1).              |
| `<frac_delete>`      | Fraction of `m` operations that are `Delete` operations (between 0 and 1).              |

##### Example Commands
Case 1: 80% Member, 10% Insert, 10% Delete, 4 Threads

```bash
./serial_method 10 1000 4 10000 0.8 0.1 0.1
```

#### Example Output 

```yaml
4, 0.034865, 0.000000
95% confidence interval: 0.034865 ± 0.000000 seconds
The results are accurate within ±5% margin.
```

### 2. Parallel program (based on Pthreads) with one mutex for the entire linked list

#### Compilcation

To compile the code, run the following command in the project directory:

```bash
gcc -o mutex_method serimutex_methodal_method.c linked_list/linked_list.c -lm
```

This will generate an executable file named `mutex_method`.


#### Usage

##### Running the program

The program accepts the following command-line arguments:

```bash
./mutex_method <num_of_runs> <num_initializations> <num_threads> <m> <frac_member> <frac_insert> <frac_delete>
```
| Argument            | Description                                                                             |
|---------------------|-----------------------------------------------------------------------------------------|
| `<num_of_runs>`      | Number of times to repeat the experiment to ensure accurate measurements.               |
| `<num_initializations>` | Number of initial insertions into the linked list.                                    |
| `<num_threads>`      | Number of threads to run concurrently.                                                  |
| `<m>`                | Total number of operations (Member, Insert, Delete) to perform.                         |
| `<frac_member>`      | Fraction of `m` operations that are `Member` operations (between 0 and 1).              |
| `<frac_insert>`      | Fraction of `m` operations that are `Insert` operations (between 0 and 1).              |
| `<frac_delete>`      | Fraction of `m` operations that are `Delete` operations (between 0 and 1).              |

##### Example Commands
Case 1: 80% Member, 10% Insert, 10% Delete, 4 Threads

```bash
./mutex_method 10 1000 4 10000 0.8 0.1 0.1
```

#### Example Output 

```yaml
4, 0.034865, 0.000000
95% confidence interval: 0.034865 ± 0.000000 seconds
The results are accurate within ±5% margin.
```

### 3. Parallel program (based on Pthreads) with read-write locks for the entire linked list

#### Compilcation

To compile the code, run the following command in the project directory:

```bash
gcc -o rw_locks_method rw_locks_method.c linked_list/linked_list.c -lm
```

This will generate an executable file named `serial_method`.


#### Usage

##### Running the program

The program accepts the following command-line arguments:

```bash
./rw_locks_method <num_of_runs> <num_initializations> <num_threads> <m> <frac_member> <frac_insert> <frac_delete>
```
| Argument            | Description                                                                             |
|---------------------|-----------------------------------------------------------------------------------------|
| `<num_of_runs>`      | Number of times to repeat the experiment to ensure accurate measurements.               |
| `<num_initializations>` | Number of initial insertions into the linked list.                                    |
| `<num_threads>`      | Number of threads to run concurrently.                                                  |
| `<m>`                | Total number of operations (Member, Insert, Delete) to perform.                         |
| `<frac_member>`      | Fraction of `m` operations that are `Member` operations (between 0 and 1).              |
| `<frac_insert>`      | Fraction of `m` operations that are `Insert` operations (between 0 and 1).              |
| `<frac_delete>`      | Fraction of `m` operations that are `Delete` operations (between 0 and 1).              |

##### Example Commands
Case 1: 80% Member, 10% Insert, 10% Delete, 4 Threads

```bash
./serial_method 10 1000 4 10000 0.8 0.1 0.1
```

#### Example Output 

```yaml
4, 0.034865, 0.000000
95% confidence interval: 0.034865 ± 0.000000 seconds
The results are accurate within ±5% margin.
```
