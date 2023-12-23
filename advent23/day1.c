#include <stdio.h>
#include <string.h>

int part1() {
    FILE *fp = fopen("input.txt", "r"); // Declare File stream, input is always "input.txt"
    int firstInt;
    int lastInt;
    int currentChar = fgetc(fp); // Get first character
    int sum = 0;
    while (currentChar != EOF) { // While not the end of the file
        firstInt = -1;
        lastInt = -1;
        while (currentChar != '\n' && currentChar != EOF) {
            if (currentChar - '0' >= 0 && currentChar - '0' <= 9) {
                if (firstInt == -1) {
                    firstInt = currentChar - '0';
                } else {
                    lastInt = currentChar - '0';
                }
            }
            currentChar = fgetc(fp);
        }
        if (lastInt != -1) {
            sum = sum + (firstInt*10) + lastInt;
        } else if (firstInt != -1) {
            sum = sum + (firstInt*10) + firstInt;
        }
        currentChar = fgetc(fp);
    }
    fclose(fp);
    return sum;
}
// Part 2 --------------------------------------------------------------------------------------------------------------
typedef struct {
    char *first;
    char *last;
} twoPos;

/**
 * Finds the first and/or last occurance of find in str and returns their pointer locations;
 * @param str the string to search through
 * @param find the substring to find
 * @return twoPos a struct containing two pointers to the first and last occurance of the find str;
 */
twoPos twoStrInStr(char *str, char *find) {
    twoPos found;
    char *tryfind;
    found.first = strstr(str, find);
    found.last = NULL;
    if (found.first != NULL) {
        tryfind = strstr(found.first+1, find);
        while (tryfind != NULL) {
            found.last = tryfind;
            tryfind = strstr(tryfind+1, find);
        }
    }
    return found;
}
/**
 * outputs 2 digit value representing first and last found values in string
 * @param line
 * @return first*10 + last (or first if last not found)
 */
int firstAndLast(char *line) {
    char *WORDS[] ={ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" }; // declare word form
    char *NUMBERS[] ={"1", "2", "3", "4", "5", "6", "7", "8", "9"}; // declare digit form
    char *first = line+100;
    int firstValue = 0;
    char *last = line-1;
    int lastValue = 0;
    for (int i = 0; i < 9; i++) {
        twoPos values = twoStrInStr(line, WORDS[i]);
        if (values.first != NULL) {
            if (values.first < first) {
                first = values.first;
                firstValue = i+1;
            } if (values.first > last) {
                last = values.first;
                lastValue = i+1;
            }
        } if (values.last != NULL) {
            if (values.last > last) {
                last = values.last;
                lastValue = i+1;
            }
        } values = twoStrInStr(line, NUMBERS[i]);
        if (values.first != NULL) {
            if (values.first < first) {
                first = values.first;
                firstValue = i+1;
            } if (values.first > last) {
                last = values.first;
                lastValue = i+1;
            }
        } if (values.last != NULL) {
            if (values.last > last) {
                last = values.last;
                lastValue = i+1;
            }
        }
    }
    return (firstValue*10) + lastValue;
}

int part2() {
    FILE *fp = fopen("input.txt", "r");
    char currentLine[100];
    int sum = 0;
    int total = 0;
    int line = 0;
    while (fgets(currentLine, 100, fp) != NULL) {
        line++;
        total = firstAndLast(currentLine);
        sum = sum + total;
        printf("Line %d: %s \nFound Total: %d\n", line, currentLine, total);
    }
    return sum;
}

int main() {
    printf("Sum of All Calibration Values: %d\n", part1());
    printf("Sum of All Calibration Values with words: %d", part2());
}