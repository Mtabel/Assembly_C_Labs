#include <stdio.h>

int return_hights_place(int number) // returns the highest place value of a number
{
    int result = 0;
    while (number > 0)
    {
        number /= 10;
        result++;
    }
    return result;
}
int return_number_readyToPaste(int number_to_add, int number)
{
    int highest_place = return_hights_place(number_to_add); // make space for the new number
    int result = 0;
    for (int i = 0; i < highest_place; i++)
    {
        number *= 10;
    }
    printf("Number after shifting: %d\n", number); // Debugging line
    printf("Number to add: %d\n", number_to_add); // Debugging line
    result += number_to_add;
    result += number;
    return result;
}

int main(void) {
    printf("Result: %d\n", return_number_readyToPaste( 11111,9999)); // Should print 5
    return 0;
}