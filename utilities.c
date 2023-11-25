// utilities.c
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utilities.h"
#include <ctype.h>
void shuffle_questions(Quiz *quizzes, int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Quiz temp = quizzes[i];
        quizzes[i] = quizzes[j];
        quizzes[j] = temp;
    }
}

void handle_alarm(int sig) {
	(void)sig;
    	printf("\nTime's up!\n");
}


int case_insensitive_compare(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return 0;
        }
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

// Trims leading and trailing spaces from a string
void trim(char *str) {
    int i;
    int begin = 0;
    int end = strlen(str) - 1;

    while (isspace((unsigned char) str[begin])) {
        begin++;
    }

    while ((end >= begin) && isspace((unsigned char) str[end])) {
        end--;
    }

    // Shift all characters back to the start of the string array.
    for (i = begin; i <= end; i++) {
        str[i - begin] = str[i];
    }

    str[i - begin] = '\0'; // Null terminate string.
}



