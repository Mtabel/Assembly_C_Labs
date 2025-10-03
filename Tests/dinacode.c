#include <stdio.h>

int sum_of_digits(int n) {
    if (n < 0) {
        n = -n;
    }
    int s = 0;
    while (n > 0) {
        s = s + (n % 10);
        n = n / 10;
    }
    return s;
}

char* get_suffix(int n) {
    int last_two = n % 100;
    if (last_two >= 11 && last_two <= 13) {
        return "th";
    }
    int last = n % 10;
    if (last == 1) {
        return "st";
    } else if (last == 2) {
        return "nd";
    } else if (last == 3) {
        return "rd";
    } else {
        return "th";
    }
}

int main() {
    int num;
    int index = 1;

    double sum_even = 0, sum_odd = 0;
    int count_even = 0, count_odd = 0;

    while (1) {
        printf("Enter the %d%s value: ", index, get_suffix(index));
        scanf("%d", &num);

        if (num == 0) {
            break;
        }

        int dsum = sum_of_digits(num);

        if (dsum % 2 == 0) {
            sum_even = sum_even + num;
            count_even = count_even + 1;
        } else {
            sum_odd = sum_odd + num;
            count_odd = count_odd + 1;
        }

        index = index + 1;
    }

    if (count_even == 0 && count_odd == 0) {
        printf("There is no average to compute.\n");
    } else {
        if (count_even > 0) {
            double avg_even = sum_even / count_even;
            printf("Average of input values whose digits sum up to an even number: %.2f\n", avg_even);
        }
        if (count_odd > 0) {
            double avg_odd = sum_odd / count_odd;
            printf("Average of input values whose digits sum up to an odd number: %.2f\n", avg_odd);
        }
    }

    return 0;
}