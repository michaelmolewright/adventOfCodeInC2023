#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helper.h"
#include <stdbool.h>

long long int difference(long int a, long int b){
    long int value = 0;
    
    if(a > b){
        value = a - b;
    }
    else{
        value = a - b;
    }

    if (value < 0){value *= -1;}
    return value;
}


long long int processline(long long int *numbers, int size){
    long long int *linedown = (long long int *)malloc(sizeof(long long int) * size);
    int i = 0;
    int zeros = true;
    while(numbers[i+1] != -696969){
        linedown[i] = numbers[i+1] - numbers[i];
        if (linedown[i] != 0){zeros = false;}
        i++;
    }


    linedown[i] = -696969; // main issue was using -1 as the terminating int for the integer array (NEED TO BE A BIT SMARTER ABOUT THIS)
    if(zeros){
        return 0;
    }
    else{
        return linedown[i-1] + processline(linedown, size);
    }
}


int main(int argc, char *argv[]){ 

    FILE *fp;

    fp = fopen("./puzzle.txt", "r");
    if(fp == NULL){
        perror("Error");
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;


    //RECURSION FOR THIS ONE

    long int total = 0;
    int lineNum = 0;
    while((read = getline(&line, &len, fp)) != -1){
        long long int *mynums = get_array_numberslong(line, 200);
        long long int next = processline(mynums, 200);

        int index = 0;
        while(mynums[index] != -696969){
            index++;
        }

        long long int nextNum = mynums[index-1] + next;
        total += nextNum;
        printf("%d, %lld, %lld\n", lineNum++, nextNum, mynums[0]);
        //printf("%d");
    }

    printf("FINAL ANSWER = %ld\n", total);


    fclose(fp);

}