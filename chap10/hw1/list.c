#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL) {
        perror("malloc");
        exit(1);
    }
    p->data = data;
    p->next = *top;
    *top = p;
}

int pop(struct node **top)
{
    struct node *p;
    int value;

    if (*top == NULL)
        return -1;

    p = *top;
    value = p->data;
    *top = p->next;
    free(p);
    return value;
}

int main()
{
    struct node *top = NULL;
    int x;

    while (scanf("%d", &x) == 1 && x > 0)
        push(&top, x);

    printf("Print stack\n");
    while (top != NULL)
        printf("%d\n", pop(&top));

    return 0;
}

