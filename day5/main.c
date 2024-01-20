#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helper.h"


long int *collectSeeds(char *line){
    char * init_token = strtok(line, ":");
    init_token = strtok(NULL, ":"); // gets the ride hand side of the string
    
    long int *numbers = get_array_numbers(init_token, 50);
    
    return numbers;
}


//NOT GONAN WORK way too much memory and time
long int *collectSeedsPart2(char *line){
    char * init_token = strtok(line, ":");
    init_token = strtok(NULL, ":"); // gets the ride hand side of the string
    
    char *num_token = strtok(init_token, " ");
    long int * values = (long int*) malloc(( atol(num_token)) * sizeof(long int));
    int index = 0;

    long int number1, number2;
    while(num_token != NULL){
        number1 = atol(num_token);
        num_token = strtok(NULL, " ");
        number2 = atol(num_token);
        num_token = strtok(NULL, " ");

        for(long int i = 0; i < number2; i++){
            values[index] = number1 + i;
            index++;
        }
    }
    values[index] = -1;


    return values;
}


int main ()
{ 
    FILE *fp;

    fp = fopen("./almanac.txt", "r");
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
     
    read = getline(&line, &len, fp);
    long int *seeds = collectSeeds(line);

    //long int *seeds = collectSeedsPart2(line);

    int *mapped = malloc(sizeof(int) * (seeds[0]));
    int k = 0;
    while(seeds[k] != -1 ){
        mapped[k] = 0;
        k++;
    }
    mapped[k] = -1;

    long int *lineNumbers;
    int i;
    long int newResult;

    while ((read = getline(&line, &len, fp)) != -1) {
        if(strcmp(line, "\n") == 0){
            continue;
        }
        else if(line[0] < 48 || line[0] > 57){
            k = 0;
            while(mapped[k] != -1){
                mapped[k] = 0;
                k++;
            }
        }
        else{
            lineNumbers = get_array_numbers(line, 3);
            i = 0;
            while(seeds[i] != -1){
                if(seeds[i] >= lineNumbers[1] && seeds[i] <= (lineNumbers[1] + lineNumbers[2]) && mapped[i] == 0){
                    newResult = lineNumbers[0] + (seeds[i] - lineNumbers[1]);
                    printf("Seed %d: source = %ld, sink = %ld. extras: %ld %ld %ld\n",i, seeds[i], newResult, lineNumbers[0], lineNumbers[1], lineNumbers[2]);
                    seeds[i] = newResult;
                    mapped[i] = 1;
                }
                
                i++;
            }
        }
    }
    i = 0;
    long int smallest = 0;
    while(seeds[i] != -1){
        if(i == 0){
            smallest = seeds[i];
        }
        printf("%ld\n", seeds[i]);
        if(seeds[i] < smallest){
            smallest = seeds[i];
        }
        i++;
    }

    printf("Smallest location = %ld\n", smallest);   

    free(line);
    free(seeds);
    free(mapped);

    fclose(fp);


} 
