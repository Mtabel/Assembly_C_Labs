#include <stdio.h>

float calc_average(int numbers[], int EvenOrOdd) {
    int count = 0;
    int opperation_count = 0;
    int sum = 0;
    if(numbers[count] == 0) {
        printf("There is no average to compute.\n");
        return -1;
    }
    if(EvenOrOdd == 0) // Even
    {   
        while (numbers[count] != 0) {
            if(numbers[count] % 2 == 0) {
                sum += numbers[count];
                opperation_count++;
            }
            count++;
        }
    }
    else if (EvenOrOdd == 1) // Odd
    {
        while (numbers[count] != 0) {
            if(numbers[count] % 2 != 0) {
                sum += numbers[count];
                opperation_count++;
            }
            count++;
        }
    }
    return (float)sum / opperation_count;
}

int main() {
    int numbers[100];
    int count = 0;
    
    for(int i = 0; i < 100; i++) {
        printf("Enter integer %d (or 0 to stop): ", i + 1);
        scanf("%d", &numbers[i]);
        if(numbers[i] == 0) {
            break;
        }
        count++;
    }

    printf("\n");
    
    if(count == 0) {
        printf("There is no average to compute.\n");
        return 0;
    }

    printf("Average of input values whose digits sum up to an even number: %.2f\n", calc_average(numbers, 0));
    printf("Average of input values whose digits sum up to an odd number: %.2f\n", calc_average(numbers, 1));

    return 0;
}