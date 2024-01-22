#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helper.h"

#define INIT_SIZE 10




int main(){ 

    FILE *fp;

    fp = fopen("./test.txt", "r");
    if(fp == NULL){
        perror("Error");
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    Array hands;
    Array bids;

    initStringArray(&hands, INIT_SIZE);
    initArray(&bids, INIT_SIZE);

    while ((read = getline(&line, &len, fp)) != -1) {
    
       insertStringArray(&hands, strtok(line, " "));
       insertArray(&bids, atoi(strtok(NULL, " ")));
    }


    for(int i = 0; i < hands.used;i++){
        printf("%s\n",hands.sArray[i]);
    }


    return 1;
}