#include <stdio.h>
#include <stdbool.h>

bool containsDuplicate(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] == arr[j])
                return true;
    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Contains duplicate? %s\n", containsDuplicate(arr, n) ? "Yes" : "No");
    return 0;
}
