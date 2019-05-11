#include <stdio.h>
#include <inttypes.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>
char * str;
mpz_t temp;
uint_fast8_t * longestNum;
int longestNumOfSteps = 0;
uint_fast8_t * currentNum;
int numLength = 0;
int NUMBER_OF_DIGITS;
void printBigNum(mpz_t num) {
    mpz_get_str(str, 10, num);
    printf("%s\n", str);
}
int lastNumOfDigits = 0;

void printArray(uint_fast8_t * array) {
    for (int x = NUMBER_OF_DIGITS-1; x >= 0; x--) {
        printf("%i", array[x]);
    }
    printf("\n");
}

void check(mpz_t num) {
    int steps = -1;
    do {
        char localStr[NUMBER_OF_DIGITS+2];
        mpz_get_str(str, 10, num);
        numLength = strlen(str);
        if (numLength > lastNumOfDigits) {
            lastNumOfDigits = numLength;
            printf("current Number of digits: %i\n", lastNumOfDigits);
        }
        strcpy(localStr, str);
        mpz_set_ui(num, 1);
        mpz_set_ui(temp, 1);
        for (int x = 0; x < numLength; x++) {
            mpz_mul_ui(temp, num, localStr[x] - '0');
            mpz_set(num, temp);
            // printf("num inside:");
            // printBigNum(num);
        }
        steps += 1;
        // printf("numLength: %i, str: %s, num:", numLength, str);
        // printBigNum(num);
    } while (numLength > 1);
    if (steps > longestNumOfSteps) {
        longestNumOfSteps = steps;
        for (int x = 0; x < NUMBER_OF_DIGITS; x++) {
            longestNum[x] = currentNum[x];
        }
        printf("new longest: ");
        printArray(longestNum);
    }
}
void goThoughAllNumbers(uint8_t base, int nest) {
    mpz_t number;
    mpz_init(number);
    for (uint8_t d = base; d < 10; d++) {
        currentNum[NUMBER_OF_DIGITS-1-nest] = d;
        if (nest < NUMBER_OF_DIGITS-1) {
            goThoughAllNumbers(d, nest+1);
        } else if (d != 0) {
            mpz_set_ui(number, 0);
            for (int x = NUMBER_OF_DIGITS-1; x > -1; x--) {
                mpz_mul_ui(temp, number, 10);
                mpz_set(number, temp);
                mpz_add_ui(temp, number, currentNum[x]);
                mpz_set(number, temp);
            }
            // printf("current: ");
            // printArray(currentNum);
            check(number);
        }
    }
    mpz_clear(number);
}

int main(int argc, char *argv[]) {
    if( argc == 2 ) {
      printf("starting with number of digits: %s\n", argv[1]);
    }
    else if( argc > 2 ) {
        printf("Too many arguments.\n");
    }
    else {
        printf("One argument expected (Number of digits).\n");
    }
    NUMBER_OF_DIGITS = atoi(argv[1]);
    str = malloc((NUMBER_OF_DIGITS+2)*sizeof(char));
    longestNum = malloc((NUMBER_OF_DIGITS)*sizeof(uint_fast8_t));
    currentNum = malloc((NUMBER_OF_DIGITS)*sizeof(uint_fast8_t));
    mpz_init(temp);
    goThoughAllNumbers(0, 0);
    printf("longest Number: ");
    printArray(longestNum);
    printf("steps: %i\n", longestNumOfSteps);
    mpz_clear(temp);
}
