#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helper.h"


int *collectSeeds(char *line){
    char * init_token = strtok(line, ":");
    init_token = strtok(NULL, ":"); // gets the ride hand side of the string
    
    int *numbers = get_array_numbers(init_token);
    
    return numbers;
}   

int main ()
{ 
    FILE *fp;

    fp = fopen("./testinput.txt", "r");
    if(fp == NULL){
        perror("Error");
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    /*
    
    Basic Idea -- Check if source number (seed then soil then 
    fertilizer ...  ) are in the ranges of numbers line[1] and line[2]

    then map to number to line[0] -- if not in that range then 
    source == source and continue

    */
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }

    free(line);

    fclose(fp);


} 
