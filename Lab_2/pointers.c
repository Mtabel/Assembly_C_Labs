#include <stdio.h>
int main() {
int x, y, *px, *py;
int arr[10];

x = 0,y = 0; //initialize all variables to 0

for(int i=0; i<10; i++) {
    arr[i] = 0;
}
printf("Memory Location of x: %p\n", &x);
printf("Memory Location of y: %p\n", &y);

px = &x;
py = &y;

printf("Value of px: %d, and the address is %p\n", *px, px);
printf("Value of px: %d, and the address is %p\n", *py, py);


// Demonstrating pointer arithmetic TPS 3.6
printf("arr: %p\n", arr);
for(int i=0; i<10; i++) {
    printf("arr[%d]: %d\n", i, *(arr + i));
}

// TPS 3.7
printf("First element of arr: %d\n", *arr);

// TPS 3.8
for(int i=0; i<10; i++) {
    printf("arr[%d]: %p\n", i, arr + i);
}
return 0;
}