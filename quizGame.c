// main.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include "quiz_data.h"
#include "utilities.h"

jmp_buf env;
extern Quiz quizzes[QUESTION_COUNT];

int main() {
    char user_answer[256], continue_game[10];
    int score = 0;
    int question_counter = 0;
    int time_limit = 10; // Example time limit

    shuffle_questions(quizzes, QUESTION_COUNT);

    signal(SIGALRM, handle_alarm);

    for (int i = 0; i < QUESTION_COUNT; i++) {
        printf("\nQuestion: %s\n", quizzes[i].question);
        alarm(time_limit); // Start the timer

        if (setjmp(env) == 0) {
            printf("You have %d seconds. Your answer: ", time_limit);
            fgets(user_answer, 256, stdin);
            user_answer[strcspn(user_answer, "\n")] = 0; // Remove newline character

	    trim(user_answer);

	    char modified_user_answer[260];
	    snprintf(modified_user_answer, sizeof(modified_user_answer), "'%s'",user_answer);


	    printf("User answer: '%s'\n", user_answer);
	    printf("Correct answer: '%s'\n", quizzes[i].answer);

            alarm(0); // Stop the timer

            if (case_insensitive_compare(quizzes[i].answer, user_answer) == 0) {
                printf("Correct!\n");
                score++;
            } else {
                printf("Wrong! The correct answer is %s\n", quizzes[i].answer);
            }
        } else {
            // Timer expired, skip to the next question
            printf("Skipping to the next question.\n");
        }

	question_counter++;

	if(question_counter % 10 == 0 && i != QUESTION_COUNT - 1) {
		printf("Your score right now is: %d. Do you want to continue the quiz? (Yes/No): ", score);
		fgets(continue_game, 10, stdin);
		continue_game[strcspn(continue_game, "\n")] = 0;

		if (case_insensitive_compare(continue_game, "no") == 0) {

			printf("You have chosen to end the quiz. Your final score is %d.\n", score);
			break;
		}
	}
    }

    printf("\nGame Over! Your score: %d\n", score);
    return 0;
}

