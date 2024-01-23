#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helper.h"
#include <stdbool.h>

#define INIT_SIZE 2000

typedef struct{
    int count[5];
    char card[5];
    int cardNumber;
    int rank[5];
}hashmap;

void initHashMap(hashmap *h){
    for(int i = 0; i < 5; i++){
        h->count[i] = 0;
        h->rank[i] = 0;
        h->card[i] = 'X';
    }
    h->cardNumber = 0;
}

int lookupValue(char card){
    char cardType[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    //long int strength[13] = {1009, 1012, 1018, 1024, 1030, 1037, 1046, 1055, 1064, 1073, 1082, 1090, 1100};
    for (int i = 0; i< 13; i++){
        if (cardType[i] == card){
            return i;
        }
    }
    return -1;
}

int computeHand(char *hand){

    hashmap handHash;
    initHashMap(&handHash);

    bool new;
    for(int i = 0; i < 5; i++){
        new = true;
        for(int j = 0; j < 5; j++){
            if(hand[i] == handHash.card[j]){
                handHash.count[j]++;
                //handHash.value[j] *= lookupValue(hand[i]);
                new = false;
                break;
            }
        }
        if (new){
            handHash.card[handHash.cardNumber] = hand[i];
            handHash.count[handHash.cardNumber] = 1;
            //handHash.value[handHash.cardNumber] *= lookupValue(hand[i]);
            handHash.cardNumber++;

        }
    }

    //Try a cool trick with squares, cubes and Quaruples?!?! -- use smallest int as 1000
    //Should work would be cool to check tho -- dont forget long int!! 
    //Found out it doesnt work without carefully selected integers, can NOT be bother to do the numerical optimisation

    // 0,1,2,3,4,5,6 -- high card, pair, two pair, triple, full house, quads, fives
    int totalValue = 0;
    for(int k = 0; k < 5; k++){
        if (handHash.count[k] > 1){
            int addition = 1;
            for(int i = 0; i < handHash.count[k]; i++){
                addition *= 3;
            }
            totalValue += addition;
        }
    }

    // 0,1,2,3,4,5,6 -- high card, pair, two pair, triple, full house, quads, fives
    switch (totalValue)
    {
    case 9:
        return 1;
    case 18:
        return 2;
    case 27:
        return 3;
    case 36:
        return 4;
    case 81:
        return 5;
    case 243:
        return 6;
    
    default:
        return 0;
    }
 
}

int compareHands(char *hand1, char *hand2){
    int val1 = computeHand(hand1);
    int val2 = computeHand(hand2);
    if(val1 > val2){
        return 1;
    }
    else if(val1 < val2){
        return 0;
    }
    else{
        int card1Val,card2Val;
        for(int i = 0; i<5; i++){
            card1Val = lookupValue(hand1[i]);
            card2Val = lookupValue(hand2[i]);
            if(card1Val > card2Val){
                return 1;
            }
            else if(card1Val < card2Val){
                return 0;
            }
            else{
                continue;
            }
        }
    }
    return 0;
}

int lookupValue2(char card){
    char cardType[13] = { 'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};
    //long int strength[13] = {1009, 1012, 1018, 1024, 1030, 1037, 1046, 1055, 1064, 1073, 1082, 1090, 1100};
    for (int i = 0; i< 13; i++){
        if (cardType[i] == card){
            return i;
        }
    }
    return -1;
}

int computeHand2(char *hand){

    hashmap handHash;
    initHashMap(&handHash);

    bool new;
    for(int i = 0; i < 5; i++){
        new = true;
        for(int j = 0; j < 5; j++){
            if(hand[i] == handHash.card[j]){
                handHash.count[j]++;
                //handHash.value[j] *= lookupValue(hand[i]);
                new = false;
                break;
            }
        }
        if (new){
            handHash.card[handHash.cardNumber] = hand[i];
            handHash.count[handHash.cardNumber] = 1;
            //handHash.value[handHash.cardNumber] *= lookupValue(hand[i]);
            handHash.cardNumber++;

        }
    }

    int numberJs = 0;
    for (int i = 0; i < 5; i++){
        if(handHash.card[i] == 'J' ){
            numberJs = handHash.count[i];
        }
    }

    int totalValue = 0;
    for(int k = 0; k < 5; k++){
        if (handHash.count[k] > 1 && handHash.card[k] != 'J'){
            int addition = 1;
            for(int i = 0; i < handHash.count[k]; i++){
                addition *= 3;
            }
            totalValue += addition;
        }
    }

    switch (totalValue)
    {
    case 9:
        if(numberJs == 1){
            return 3; 
        }
        else if (numberJs == 2){
            return 5; 
        }
        else if (numberJs == 3){
            return 6; 
        }
        else{
            return 1;
        }
    case 18:
        if(numberJs == 1){
            return 4; 
        }
        else{
            return 2;
        }
    case 27:
        if(numberJs == 1){
            return 5; 
        }
        else if (numberJs == 2){
            return 6; 
        }
        else{
            return 3;
        }
    case 36:
        return 4;
    case 81:
        if(numberJs == 1){
            return 6; 
        }
        return 5;
    case 243:
        return 6;
    case 0:
        if(numberJs == 5){
            return 6;
        }
        else if (numberJs == 4){
            return 6;
        }
        else if (numberJs == 3){
            return 5;
        }
        else if (numberJs == 2){
            return 3;
        }
        else if (numberJs == 1){
            return 1;
        }
        else {
            return 0;
        }
    default:
        return 0;
    }
 
}

int compareHands2(char *hand1, char *hand2){
    int val1 = computeHand2(hand1);
    int val2 = computeHand2(hand2);
    if(val1 > val2){
        return 1;
    }
    else if(val1 < val2){
        return 0;
    }
    else{
        int card1Val,card2Val;
        for(int i = 0; i<5; i++){
            card1Val = lookupValue2(hand1[i]);
            card2Val = lookupValue2(hand2[i]);
            if(card1Val > card2Val){
                return 1;
            }
            else if(card1Val < card2Val){
                return 0;
            }
            else{
                continue;
            }
        }
    }
    return 0;
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
   
    /*
    char cardType[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    long int strength[13] = {1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012};
    */

    Array hands;
    Array bids;

    initStringArray(&hands, INIT_SIZE);
    initArray(&hands, INIT_SIZE);
    initArray(&bids, INIT_SIZE);

    while ((read = getline(&line, &len, fp)) != -1) {
       insertStringArray(&hands, strtok(line, " "));
       insertArray(&bids, atoi(strtok(NULL, " ")));
    }

    //int overallRank, handRank;
    char *temphand;
    int tempbid;


    for(int i = 0; i < hands.used;i++){
        printf("HAND - %s, BID - %ld\n",hands.sArray[i], bids.array[i]);
    }
    printf("\n");

    for(int i = 0; i < hands.used;i++){
        for(int j = 0; j < hands.used;j++){
            if (compareHands2(hands.sArray[j], hands.sArray[i]))
                {
                    temphand = hands.sArray[j];
                    hands.sArray[j] = hands.sArray[i];
                    hands.sArray[i] = temphand;

                    tempbid = bids.array[j];
                    bids.array[j] = bids.array[i];
                    bids.array[i] = tempbid;
                }
        }    
        //insertArray(&hands, computeHand(hands.sArray[i]) );
        //printf("HAND - %s    VALUE - %d\n",hands.sArray[i], computeHand(hands.sArray[i]));
    }

    long int total = 0;
    for(int i = 0; i < hands.used;i++){
        total += ( bids.array[i] * (i + 1) );
        printf("HAND - %s, BID - %ld, VALUE - %d\n",hands.sArray[i], bids.array[i], computeHand(hands.sArray[i]));
    }

    printf("TOTAL = %ld\n", total);

    freesArray(&hands);
    freeArray(&bids);

    if (argc > 1){
        printf("value of hand - %s = %d\n\n ", argv[1], computeHand2(argv[1]));
    } 

    return 1;
}