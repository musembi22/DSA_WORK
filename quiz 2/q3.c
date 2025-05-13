#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *prev = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Helper and test
void printList(struct ListNode* head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct ListNode* a = malloc(sizeof(struct ListNode));
    struct ListNode* b = malloc(sizeof(struct ListNode));
    struct ListNode* c = malloc(sizeof(struct ListNode));
    a->val = 1; b->val = 2; c->val = 3;
    a->next = b; b->next = c; c->next = NULL;

    struct ListNode* rev = reverseList(a);
    printList(rev);
    return 0;
}
