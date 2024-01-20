#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int *get_array_numbers(char *numbers, int size){
    
    long int * values = (long int*) malloc((size + 1) * sizeof(long int));
    
    char * num_token = strtok(numbers, " ");
    int index = 0;
    while(num_token != NULL){
        values[index] = atol(num_token);
        index = index + 1;
        num_token = strtok(NULL, " ");
    }
    values[index] = -1;

    return values;
}