#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  long int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(long int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, long int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(long int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}


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


void fill_array_numbers(char *numbers,Array *myarr, size_t size){


    initArray(myarr,size);
    char * num_token = strtok(numbers, " ");


    while(num_token != NULL){
        insertArray(myarr, atol(num_token));
        num_token = strtok(NULL, " ");
    }

}