#include <stdio.h>

int removeDuplicates(int nums[], int n) {
    if (n == 0) return 0;
    int index = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[index - 1]) {
            nums[index++] = nums[i];
        }
    }
    return index;
}

int main() {
    int nums[] = {1, 1, 2, 3, 3};
    int n = sizeof(nums) / sizeof(nums[0]);
    int newLen = removeDuplicates(nums, n);

    printf("After removing duplicates: ");
    for (int i = 0; i < newLen; i++)
        printf("%d ", nums[i]);
    printf("\n");
    return 0;
}




