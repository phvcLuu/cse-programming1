// Lab 3 — Valgrind exercise
// The program prints results that "look correct" but has 4 memory bugs.
//   gcc -Wall -g leaky.c -o leaky
//   valgrind --leak-check=full --track-origins=yes ./leaky
// Fix all the bugs until valgrind reports: 0 errors, no leaks.
//
// Record the bugs you find:
//   Bug 1: line 18, valgrind reports Invalid write of size 1
//          fix: +1 to strlen -> 13 + 1, free mem after used
//   Bug 2: line 27, valgrind reports Uninitialized value was created
//          fix: start for loop at 0
//   Bug 3: line 44, valgrind reports Invalid read of size 4
//          fix: don't free yet
//   Bug 4: free mem in bug 1 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a copy of the string on the heap
char *copy_string(const char *s) {
    char *copy = malloc((strlen(s) + 1) * sizeof(*copy));
    strcpy(copy, s); // strcpy: copy = s + '\0'  ->  14 bytes instead of 13 bytes
    return copy;
}

// Create an array of n elements: element i equals i * i
int *make_squares(int n) {
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)  // a[0] was not initialize in mem
        a[i] = i * i;
    return a;
}

int main() {
    char *name = copy_string("Programming 1");
    printf("name = %s\n", name);
    free(name);
    int *squares = make_squares(5);
    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += squares[i];
    if (sum > 0)
        printf("sum of squares = %d\n", sum);

    printf("first square = %d\n", squares[1]);
    free(squares);

    return 0;
}
