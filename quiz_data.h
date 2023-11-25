
#ifndef QUIZ_DATA_H
#define QUIZ_DATA_H

#define QUESTION_COUNT 4

typedef struct {
	char question[256];
	char answer[256];
} Quiz;

extern Quiz quizzes[QUESTION_COUNT];

#endif
