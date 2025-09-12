#include <stdio.h>

int repNumber()
{
    int reps;
    printf("Enter the number of repetitions: ");
    while (scanf("%d", &reps) != 1 || !(reps > 0)) {
        printf("Invalid input. Please enter a valid integer:");
        // Clear the invalid input from the buffer
        while (getchar() != '\n');
    }
    return reps;
}
int error_line(int passlimit)
{
    int upper_limit = passlimit;
    int reps;
    printf("Enter the Line you would like with errors: ");
    while (scanf("%d", &reps) != 1 || !(reps > 0) || !(reps <= upper_limit)) {
        printf("Invalid input. Please enter a valid integer:");
        // Clear the invalid input from the buffer
        while (getchar() != '\n');
    }
    return reps;
}

int main() {
    printf("Hello, world!\n");

    printf("\n");

    int reps = repNumber();

    printf("\n");

    int line_typo = error_line(reps); 

    printf("\n");


    char phrase[] = "Coding with C is Awesome!";
    char phrase_typo[] = "Cading wiht is C avesone!";

    for (int i = 0; i < reps; i++) {

        if(i == line_typo - 1) {
            printf("%s\n", phrase_typo);
        } else {
            printf("%s\n", phrase);
        }
    }

    
    return 0;
}