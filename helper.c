#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *get_array_numbers(char *numbers){
    
    int * values = (int*) malloc(strlen(numbers) * sizeof(int));
    
    char * num_token = strtok(numbers, " ");
    int index = 0;
    while(num_token != NULL){
        values[index] = atoi(num_token);
        index = index + 1;
        num_token = strtok(NULL, " ");
    }
    values[index] = -1;

    return values;
}