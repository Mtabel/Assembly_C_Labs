#include <stdio.h>
char* get_suffix(int n){
    int last_two = n % 100;
    if (last_two >= 11 && last_two <= 13){
        return "th";
    }
    int last = n % 10;
    if (last == 1){
        return "st";
    } else if (last == 2){
        return "nd";
    } else if (last == 3){
        return "rd";
    } else {
        return "th";
    }
}

int get_input(int numbers[100])
{
    int count = 0;
    for(int i = 0; i < 100; i++) {
        printf("Enter integer %d%s (or 0 to stop): ", i + 1, get_suffix(i + 1));
        scanf("%d", &numbers[i]);
        if(numbers[i] == 0) {
            break;
        }
        count++;
    }
    printf("\n");
    return count;
}


void get_even_odd_sums(int numbers[], int count, int even_sums[], int *even_count, int odd_sums[],int *odd_count)
{
    int even_tally = 0;
    int odd_tally = 0;

    for(int i = 0; i < count; i++)
    {
        int sum = 0;
        int original_number = numbers[i];
        if(original_number < 0) {
            numbers[i] = -numbers[i]; // Make it positive for digit sum calculation
        }
        while(numbers[i] > 0)
        {
            sum += numbers[i] % 10;
            numbers[i] /= 10;
        }
        if(sum % 2 == 0)
        {
            even_sums[even_tally] = original_number;
            even_tally++;
            (*even_count)++;
        }
        else
        {
            odd_sums[odd_tally] = original_number;
            odd_tally++;
            (*odd_count)++;
        }


    }
    // printf("Even Sums: %d, Odd Sums: %d", even_tally, odd_tally);
    // printf("\n");
    // printf("Even Count: %d, Odd Count: %d", *even_count, *odd_count);


    
}

void take_average(int arr[], int size)
{
    if(size == 0) {
        // printf("No elements to compute average.\n");
        return;
    }
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += arr[i];
    }
    double average = (double)sum / size;
    printf("%.2f\n", average);
}

void set_array(int arr[], int size, int value)
{
    for(int i = 0; i < size; i++) {
        arr[i] = value;
    }
}

void print_array(int arr[], int size)
{
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main() {
    int numbers[100];
    int even_sums[100];
    int odd_sums[100];

    int count = 0;
    int even_count = 0;
    int odd_count = 0;
    

    set_array(numbers, 100, 0);
    set_array(even_sums, 100, 0);
    set_array(odd_sums, 100, 0);

    count = get_input(numbers);

    //print_array(numbers, count);

    get_even_odd_sums(numbers, count, even_sums, &even_count, odd_sums, &odd_count);
    
    //print_array(even_sums, even_count);
    //print_array(odd_sums, odd_count);

    
    if(count == 0) {
        printf("There is no average to compute.\n");
        return 1;
    }
    else
    {
        if(even_count != 0)
        {
            printf("Average of input values whose digits sum up to an even number:");
            take_average(even_sums, even_count);
        }
        if(odd_count != 0)
        {
            printf("Average of input values whose digits sum up to an odd number:");
            take_average(odd_sums, odd_count);
        }
    }

    return 0;
}