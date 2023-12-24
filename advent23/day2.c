#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IMPOSSIBLE 0
#define POSSIBLE 1

int gamePossible(char *str) {
    // Define variables
    char *COLORS[] = {"red", "green", "blue"};
    long VALUES[] = {12, 13, 14};
    long count;
    char *color;

    // Tokenize the string into numbers and colors
    str = strtok(str, ":"); // remove "Game x:"
    str = strtok(NULL, ":");
    char *token = strtok(str, ";, \n"); // tokenize string

    // While there are still tokens
    while (token != NULL) {
        count = strtol(token, NULL, 10); // get the count token
        color = strtok(NULL, ";, \n"); // get the color token
        for (int i = 0; i < 3; i++) { // Loop through colors
            if (strcmp(color, COLORS[i]) == 0) {  // check if the color is right
                if (count > VALUES[i]) { // Check if the count exceeds the maximum
                    return IMPOSSIBLE;
                }
            }
        }
        token = strtok(NULL, ";, \n"); // get the next token
    }
    return 1;
}

int part1() {
    FILE *fp = fopen("input.txt", "r");
    char buffer[400];
    int counter = 1;
    int sum = 0;
    while (fgets(buffer, 400, fp) != NULL) {
        if (gamePossible(buffer) == POSSIBLE) {
            sum += counter;
        }

        counter++;
    }
    return sum;
}

// Part 2 --------------------------------------------------------------------------------------------------------------

typedef struct {
    long red;
    long green;
    long blue;
}cubeCounts;

cubeCounts gameMinimums(char *str) {
    // Define Variables
    char *COLORS[] = {"red", "green", "blue"};
    long values[] = {0, 0, 0};
    long count; // first token will be an integer
    char *color; // get the next token which will be the colour
    str = strtok(str, ":"); // remove "Game x:"
    str = strtok(NULL, ":");
    char *token = strtok(str, ";, \n"); // tokenize string
    // Define cubes
    cubeCounts cubes;

    while (token != NULL) { // Loop through tokens
        count = strtol(token, NULL, 10); // get the count number
        color = strtok(NULL, ";, \n"); // get the color token
        for (int i = 0; i < 3; i++) { // Loop through colors
            if (strcmp(color, COLORS[i]) == 0) {  // check if the color is right
                if (values[i] < count) { // if the current count is greater than the associated colors value then switch
                    values[i] = count;
                }
            }
        }
        token = strtok(NULL, ";, \n"); // get the next token
    }
    cubes.red = values[0];
    cubes.green = values[1];
    cubes.blue = values[2];
    return cubes;
}

long part2() {
    FILE *fp = fopen("input.txt", "r");
    char buffer[400];
    long sum = 0;
    cubeCounts cubes; // initalize cubes
    while (fgets(buffer, 400, fp) != NULL) {
        cubes = gameMinimums(buffer);
        sum += cubes.red * cubes.green * cubes.blue;
    }
    return sum;
}

int main() {
    printf("The sum of possible game ID's are: %d\n", part1());
    printf("The sum of game powers are: %ld", part2());
    return 0;
}