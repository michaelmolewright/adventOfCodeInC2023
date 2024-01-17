#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * get_array_numbers(char * numbers){
    
    int * values = (int*) malloc(strlen(numbers) * sizeof(int));
    
    char * num_token = strtok(numbers, " ");
    int index = 0;
    while(num_token != NULL){
        values[index] = atoi(num_token);
        index = index + 1;
        num_token = strtok(NULL, " ");
    }
    values[index] = -1;

    return values;
}


int calculate_score(char * line){
    char * init_token = strtok(line, ":");
    init_token = strtok(NULL, ":"); // gets the ride hand side of the string

    char * winning_numbers = strtok(init_token, "|");
    char * my_numbers = strtok(NULL, "|");

    int * winning_ints = get_array_numbers(winning_numbers);
    int * my_ints = get_array_numbers(my_numbers);

    int i = 0;
    int j = 0;

    int score = 0;

    while (winning_ints[i] != -1){
        j = 0;
        while(my_ints[j] != -1){
            if (winning_ints[i] == my_ints[j]){
                if (score == 0){
                    score = 1;
                }
                else{
                    score = score * 2;
                }
                break;
            }
            j++;
        }
        i++;
    }
    
    free(winning_ints);
    free(my_ints);


    return score;
}


int calculate_wins(char * line){
    char * init_token = strtok(line, ":");
    init_token = strtok(NULL, ":"); // gets the ride hand side of the string

    char * winning_numbers = strtok(init_token, "|");
    char * my_numbers = strtok(NULL, "|");

    int * winning_ints = get_array_numbers(winning_numbers);
    int * my_ints = get_array_numbers(my_numbers);

    int i = 0;
    int j = 0;

    int wins = 0;

    while (winning_ints[i] != -1){
        j = 0;
        while(my_ints[j] != -1){
            if (winning_ints[i] == my_ints[j]){
                wins++;
                break;
            }
            j++;
        }
        i++;
    }
    
    free(winning_ints);
    free(my_ints);


    return wins;
}

int waterfall_calculation(int * win_array, int * number_cards, int size){
    int i = 0;
    while(win_array[i] != -1){
        for(int ext = 1; ext <= win_array[i]; ext++){
            number_cards[i+ext] += number_cards[i];
            //printf("%d\n",number_cards[i+ext]);
        }
        i++;
    }

    int total = 0;
    for(int i = 0; i <size-1; i++){
        printf("%d \n",number_cards[i]);
        total += number_cards[i];
    }
    return total;
}


int main(int argc, char *argv[])
{
    if(argc == 1){
        return 1;
    }
    FILE *fp;

    fp = fopen("./scratchcards.txt", "r");
    if(fp == NULL){
        perror("Error");
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int cardNo = 1;
    
    if (*argv[1] == '1'){
        int total_score = 0;
        int score_now;
        while ((read = getline(&line, &len, fp)) != -1) {
            score_now = calculate_score(line);
            total_score = total_score + score_now;
            printf("card %d score = %d\n",cardNo,score_now);
            cardNo++;
        }

        printf("total score = %d\n", total_score);
    }
    else if(*argv[1] == '2'){
        int wins;

        int * win_array = (int*) malloc(200 * sizeof(int));

        while ((read = getline(&line, &len, fp)) != -1) {
            wins = calculate_wins(line);
            printf("card %d score = %d\n",cardNo,wins);
            win_array[cardNo-1] = wins;
            cardNo++;
        }
        win_array[cardNo-1] = -1;

        int number_cards[cardNo-1];

        for(int i = 0; i <cardNo-1; i++){
            number_cards[i] = 1;
        }

        int final_score = waterfall_calculation(win_array, number_cards, cardNo);

        printf("final number of scratch cards = %d\n",final_score);
        free(win_array);


    }
    else{
        printf("You need to choose task 1 or 2 by inputting it into cmd line arguments!\nYou inputted %s\n",argv[1]);
        free(line);
        fclose(fp);
        return 1;
    }


    free(line);
    fclose(fp);

    return 1;

}

