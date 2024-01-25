#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helper.h"
#include <stdbool.h>


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


    while((read = getline(&line, &len, fp)) != -1){
        printf("%s",line );
    }


    fclose(fp);

}