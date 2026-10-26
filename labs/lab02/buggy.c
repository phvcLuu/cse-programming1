// Lab 2 — Debugging exercise
// This program compiles but produces WRONG results. There are 4 bugs.
// Use gdb or VS Code (breakpoints, step, watch) to find them; do NOT add printf.
//
// Record the bugs you find:
//   Bug 1: line 16, symptom: wrong starting index, fix int i = 0
//   Bug 2: line 26, symptom: initial max should be a[0]
//   Bug 3: line 22, symptom: int / int no floating point, fix: cast (float) before return
//   Bug 4: line 34, symptom: excessive loops, loop half of the string: i <= len/2
#include <stdio.h>

#define N 5

int sum_array(int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

double average(int a[], int n) {
    return (float) sum_array(a, n) / n;
}

int max_array(int a[], int n) {
    int max = a[0];
    for (int i = 0; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

void reverse_string(char s[], int len) {
    for (int i = 0; i <= len/2; i++) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

int main() {
    int data[N] = {10, 20, 30, 40, 51};
    int temps[N] = {-5, -3, -8, -1, -9}; // winter temperatures

    printf("sum = %d\n", sum_array(data, N));
    printf("average = %.2f\n", average(data, N));
    printf("max = %d\n", max_array(data, N));
    printf("max temp = %d\n", max_array(temps, N));

    char word[] = "hello";
    reverse_string(word, 5);
    printf("reversed: %s\n", word);

    return 0;
}
