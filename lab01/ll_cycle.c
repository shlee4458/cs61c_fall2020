#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    node *tortoise = head;
    node *hare = head;
    while (1) {

        /** If hare reaches the end, return false*/
        if (hare->next == NULL || hare->next->next == NULL) {
            printf("Not cyclical\n");
            return 0;
        }

        /** Advance the pointer by 2 step v. 1 step */
        hare = hare->next->next;
        tortoise = tortoise->next;

        /** If hare, tortoise point to the same thing, return true */
        if (hare == tortoise) {
            printf("Cyclical\n");
            return 1;
        }
    }
    return 0;
}

int main() {
    
    /* Initiate node one and two */
    struct node *one = (struct node *) malloc(sizeof(struct node));                                                                                                                                                                                                                
    one->next = (struct node *) malloc(sizeof(struct node));
    struct node *two = one->next;

    one->value = 1;
    two->value = 2;
    two->next = NULL;

    free(one);
    free(two);

    /* Test the cyclical */
    int result = ll_has_cycle(one);
    printf("%d\n", result);

    /* Initiate node three */
    struct node *three = (struct node *) malloc(sizeof(struct node));
    two->next = three;

    three->value = 3;
    three->next = one;
    free(three);

    /* Test the non cyclical */
    result = ll_has_cycle(one);
    printf("%d", result);
   
}