// Lab 2 — Arrays and Strings
// Compile and run:  gcc -Wall -Wextra -g lab02.c -o lab02 && ./lab02
// Task: implement the functions marked TODO until all tests PASS.
#include <stdio.h>
#include <string.h> // used only in main for testing

// ---------------------------------------------------------------------------
// Simple test harness (no need to modify)
static int passed = 0, total = 0;
#define CHECK(expr)                                 \
    do {                                            \
        total++;                                    \
        if (expr) {                                 \
            passed++;                               \
            printf("  PASS  %s\n", #expr);          \
        } else {                                    \
            printf("  FAIL  %s\n", #expr);          \
        }                                           \
    } while (0)

static int same_array(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}
// ---------------------------------------------------------------------------

#define ROWS 3
#define COLS 4

// 2.1 Maximum value of the array (n >= 1)
int array_max(int a[], int n) {
    int max = a[0];
    for (int i = 0; i < n; ++i){
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

// 2.2 Arithmetic mean (n >= 1)
double array_mean(int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i){
        sum += a[i];
    }
    return (float) sum/n;
}

// 2.3 Reverse the array in place: {1, 2, 3} -> {3, 2, 1}
void reverse_array(int a[], int n) {
    for (int i = 0; i < n/2; ++i){
        int tmp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = tmp;
    }
}

// 2.4 Number of occurrences of value in the array
int count_value(int a[], int n, int value) {
    int count = 0;
    for (int i = 0; i < n; ++i){
        if (a[i] == value)
            count++;
    }
    return count;
}

// 2.5 Max along an axis (Lecture 3):
//   axis = 0: max of each COLUMN -> out has COLS elements
//   axis = 1: max of each ROW -> out has rows elements
void max_2d(int a[][COLS], int rows, int axis, int out[]) {
    int n;
    if (axis){
        n = rows;
        for (int i = 0; i < rows; ++i){
            out[i] = a[i][0];
            for (int j = 1; j < COLS; j++){
                if (a[i][j] > out[i])
                    out[i] = a[i][j];
            }
        }
    }else{
        n = COLS;
        for (int i = 0; i < COLS; ++i){
            out[i] = a[0][i];
            for (int j = 1; j < rows; j++){
                if (a[j][i] > out[i])
                    out[i] = a[j][i];
            }
        }
    }

    for (int i = 0; i < n; ++i){
        printf("  %d ", out[i]);
    }
    printf("\n");
}

// 2.6 Matrix multiplication: C = A x B, where A is 2x3, B is 3x2, C is 2x2
void matmul(int A[2][3], int B[3][2], int C[2][2]) {
    // TODO: C[i][j] = sum over k of A[i][k] * B[k][j]
    for (int l = 0; l < 2; ++l){        // row of A
        for (int k = 0; k < 2; ++k){    // col of A
            for (int i = 0; i < 3; ++i){
                C[l][k] += A[l][i] * B[i][k];
            }
        }
    }
}

// 2.7 Implement strlen yourself (do NOT use <string.h>)
int my_strlen(const char s[]) {
    // TODO: count until you reach '\0'
    int count = 0;
    while (s[count] != '\0') {
        count++;
    }
    return count;
}

// 2.8 Convert lowercase letters to uppercase in place, leaving other characters unchanged
void to_upper(char s[]) {
    // TODO: 'a' - 'A' == 32 (ASCII table)
    int lens = my_strlen(s);
    for (int i = 0; i < lens; ++i){
        // check lower case char
        if (s[i] >= 'a' && s[i] <= 'z'){
            s[i] = s[i] - 'a' + 'A';
        }
    }
}

// 2.9 Return 1 if s is a palindrome ("racecar", "abba", ""), otherwise 0
int is_palindrome(const char s[]) {
    int len = my_strlen(s);
    for (int i = 0; i < len/2; ++i){
        if (s[i] != s[len - 1 - i])
            return 0;
    }
    return 1;
}

// 2.10 Count words; words are separated by one or more spaces ' '
//      "  hello   world " -> 2
int count_words(const char s[]) {
    // TODO: count the "word starts": a non-' ' character preceded by ' ' (or the start of the string)
    int count = 0;
    
    for (int i = 0; s[i] != '\0'; ++i){
        if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
            count++;
    }

    return count;
}

int main() {
    printf("2.1 array_max\n");
    int a1[] = {3, 9, -2, 7};
    int neg[] = {-5, -3, -8};
    CHECK(array_max(a1, 4) == 9);
    CHECK(array_max(neg, 3) == -3);

    printf("2.2 array_mean\n");
    int a2[] = {1, 2, 3, 4};
    CHECK(array_mean(a2, 4) == 2.5);
    CHECK(array_mean(neg, 3) > -5.34 && array_mean(neg, 3) < -5.33);

    printf("2.3 reverse_array\n");
    int r1[] = {1, 2, 3, 4, 5}, e1[] = {5, 4, 3, 2, 1};
    int r2[] = {1, 2, 3, 4}, e2[] = {4, 3, 2, 1};
    reverse_array(r1, 5);
    reverse_array(r2, 4);
    CHECK(same_array(r1, e1, 5));
    CHECK(same_array(r2, e2, 4));

    printf("2.4 count_value\n");
    int a4[] = {1, 2, 1, 3, 1};
    CHECK(count_value(a4, 5, 1) == 3);
    CHECK(count_value(a4, 5, 9) == 0);

    printf("2.5 max_2d\n");
    int m[ROWS][COLS] = {{1, 8, 3, 4}, 
                         {5, 2, 7, 0}, 
                         {9, 6, 1, 2}};
    int cols[COLS] = {0}, rows[ROWS] = {0};
    int ecols[] = {9, 8, 7, 4}, erows[] = {8, 7, 9};
    max_2d(m, ROWS, 0, cols);
    max_2d(m, ROWS, 1, rows);
    CHECK(same_array(cols, ecols, COLS));
    CHECK(same_array(rows, erows, ROWS));

    printf("2.6 matmul\n");
    int A[2][3] = {{1, 2, 3}, 
                   {4, 5, 6}};
    int B[3][2] = {{7, 8}, 
                   {9, 10}, 
                   {11, 12}};
    int C[2][2] = {{0}};
    matmul(A, B, C);
    CHECK(C[0][0] == 58 && C[0][1] == 64);
    CHECK(C[1][0] == 139 && C[1][1] == 154);

    printf("2.7 my_strlen\n");
    CHECK(my_strlen("") == 0);
    CHECK(my_strlen("hello") == 5);

    printf("2.8 to_upper\n");
    char s8[] = "Hello, World 2024!";
    to_upper(s8);
    CHECK(strcmp(s8, "HELLO, WORLD 2024!") == 0);

    printf("2.9 is_palindrome\n");
    CHECK(is_palindrome("racecar") == 1);
    CHECK(is_palindrome("abba") == 1);
    CHECK(is_palindrome("") == 1);
    CHECK(is_palindrome("abca") == 0);

    printf("2.10 count_words\n");
    CHECK(count_words("hello world") == 2);
    CHECK(count_words("  hello   world ") == 2);
    CHECK(count_words("") == 0);
    CHECK(count_words("   ") == 0);
    CHECK(count_words("C") == 1);

    printf("\nResult: %d/%d PASS\n", passed, total);
    return passed == total ? 0 : 1;
}
