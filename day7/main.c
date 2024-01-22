#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helper.h"
#include <stdbool.h>

#define INIT_SIZE 10

typedef struct{
    int count[5];
    char card[5];
    int cardNumber;
}hashmap;

void initHashMap(hashmap *h){
    for(int i = 0; i < 5; i++){
        h->count[i] = 0;
        h->card[i] = 'X';
    }
    h->cardNumber = 0;
}


void computeHand(char *hand){

    hashmap handHash;
    initHashMap(&handHash);

    bool new;
    for(int i = 0; i < 5; i++){
        new = true;
        for(int j = 0; j < 5; j++){
            if(hand[i] == handHash.card[j]){
                handHash.count[j]++;
                new = false;
                break;
            } 
        }
        if (new){
            handHash.card[handHash.cardNumber] = hand[i];
            handHash.count[handHash.cardNumber] = 1;
            handHash.cardNumber++;

        }
    }

    //Try a cool trick with squares, cubes and Quaruples?!?! -- use smallest int as 1000
    //Should work would be cool to check tho -- dont forget long int!!

    for(int k = 0; k < 5; k++){
        printf("Count = %d, Card = %c |\n ", handHash.count[k], handHash.card[k]);
    }   
}


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

    //char strength[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

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
        computeHand(hands.sArray[i]);
        printf("\n\n");
    }


    return 1;
}