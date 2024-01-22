#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helper.h"
#include <stdbool.h>

#define INIT_SIZE 10

int simulateRace(long int time, long int distance){
    int variations = 0;

    for(int i = 1; i < time; i++){
        if ((time - i)*i > distance){
            variations += 1;
        }
    }
    return variations;

}

int main(){ 

    FILE *fp;

    fp = fopen("./puzzle.txt", "r");
    if(fp == NULL){
        perror("Error");
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    Array times;
    Array distances;
    char *init_token;

    int lineNum = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (lineNum == 0){
            init_token = strtok(line, ":");
            init_token = strtok(NULL, ":");
            fill_array_numbers(init_token, &times, INIT_SIZE);
            lineNum++;
        }
        else{
            init_token = strtok(line, ":");
            init_token = strtok(NULL, ":");
            fill_array_numbers(init_token, &distances, INIT_SIZE);
        }

    }
    int wins;
    int answer = 1;
    for(int i = 0; i < times.used; i++){
        wins = simulateRace(times.array[i], distances.array[i]);
        printf("time: %ld, Record Distance: %ld, Ways to win: %d\n", times.array[i], distances.array[i], wins);
        answer *= wins;
    }

    printf("Final Answer = %d\n", answer);



    freeArray(&times);
    freeArray(&distances);




    return 1;
}