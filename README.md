# Concurrent_Programming_Lab1

serial compile:
gcc -o serial_program serial_method.c linked_list/linked_list.c

./serial_program 20 1000 4 10000 0.99 0.005 0.005

mutex :
gcc -o mutex_program mutex_method.c -lpthread linked_list/linked_list.c
