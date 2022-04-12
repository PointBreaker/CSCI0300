#include <stdio.h>
#include <stdlib.h>

/**
 * TODO:
 * In this file, you will write two functions:
 *
 * 1. reverse_arr: will take in two inputs a char* array and the number of
 * elements in the array. It's responsible for reversing the input array. You
 * should be modifying this array in place. Meaning that you shouldn't returning
 * anything from this function.
 *
 * 2. swap: will take in two elements from the array and swap them. Returns
 * nothing.
 *
 * Example:
 * Given an array ["hello", "my", "name", "is"], after calling reverse_arr
 * will result in ["is", "name", "my", "hello"]
 */

void swap(char *a[], char *b[]) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}
void reverse_arr(char** arr, int num) {
    for (int i = 0, j = num - 1; i < j; i++, j--) {
        swap(&arr[i], &arr[j]);
    }
}
