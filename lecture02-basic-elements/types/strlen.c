#include <stdio.h>
#include <string.h>

int main(){
    char str[10] = "hello!";
    int len_of_str = strlen(str);
    int size_of_str = sizeof(str)/sizeof(str[0]);

    printf("The string \"%s\" has a length of %ld \n", str, len_of_str);
    printf("The string \"%s\" is stored in an array of %ld \n", str, size_of_str);

    return 0;
}