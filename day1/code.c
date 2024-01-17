#include <stdio.h>
#include <stdlib.h>


int main ()
{ 
    FILE *fp;

    fp = fopen("./input.txt", "r");
    if(fp == NULL){
        perror("Error");
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }

    free(line);
    

    fclose(fp);


} 
