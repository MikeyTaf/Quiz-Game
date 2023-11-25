#ifndef UTILITIES_H
#define UTILITIES_H

#include "quiz_data.h"

int case_insensitive_compare(const char *str1, const char *str2);
void shuffle_questions(Quiz *quizzes, int n);
void handle_alarm(int sig);
void trim(char *str);

#endif
