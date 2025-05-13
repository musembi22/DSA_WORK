#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* detectCycle(struct ListNode* head) {
    struct ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return NULL;
}

// Test setup
int main() {
    struct ListNode* n1 = malloc(sizeof(struct ListNode));
    struct ListNode* n2 = malloc(sizeof(struct ListNode));
    struct ListNode* n3 = malloc(sizeof(struct ListNode));
    struct ListNode* n4 = malloc(sizeof(struct ListNode));
    n1->val = 3; n2->val = 2; n3->val = 0; n4->val = -4;
    n1->next = n2; n2->next = n3; n3->next = n4; n4->next = n2; // cycle at pos 1

    struct ListNode* cycleStart = detectCycle(n1);
    if (cycleStart)
        printf("Cycle starts at node with value: %d\n", cycleStart->val);
    else
        printf("No cycle\n");

    return 0;
}
