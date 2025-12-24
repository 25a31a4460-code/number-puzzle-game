#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void playGame();
void viewScoreboard();

int main() {
    int choice;

    while (1) {
        printf("\n===== NUMBER PUZZLE GAME =====\n");
        printf("1. Play Game\n");
        printf("2. View Scoreboard\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                viewScoreboard();
                break;
            case 3:
                printf("Thank you for playing!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void playGame() {
    int number, guess, attempts = 0;
    char name[50];

    printf("\nEnter your name: ");
    scanf("%s", name);

    srand(time(0));
    number = rand() % 100 + 1;

    printf("I have chosen a number between 1 and 100.\n");

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess > number)
            printf("Too high!\n");
        else if (guess < number)
            printf("Too low!\n");
        else
            printf("Correct! You guessed it in %d attempts.\n", attempts);

    } while (guess != number);

    // Save score to file
    FILE *fp = fopen("scores.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s %d\n", name, attempts);
        fclose(fp);
    } else {
        printf("Error saving score!\n");
    }
}

void viewScoreboard() {
    FILE *fp;
    char name[50];
    int attempts;

    fp = fopen("scores.txt", "r");
    if (fp == NULL) {
        printf("\nNo scores available yet.\n");
        return;
    }

    printf("\n===== SCOREBOARD =====\n");
    printf("Name\tAttempts\n");

    while (fscanf(fp, "%s %d", name, &attempts) != EOF) {
        printf("%s\t%d\n", name, attempts);
    }

    fclose(fp);
}