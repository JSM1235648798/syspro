#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL) {
        perror("malloc");
        exit(1);
    }

    p->data = data;
    p->next = NULL;

    if (*tail == NULL) {
        *head = p;
        *tail = p;
    } else {
        (*tail)->next = p;
        *tail = p;
    }
}

int delete(struct node **head, struct node **tail)
{
    struct node *p;
    int value;

    if (*head == NULL)
        return -1;

    p = *head;
    value = p->data;
    *head = p->next;
    if (*head == NULL)
        *tail = NULL;
    free(p);
    return value;
}

int main()
{
    struct node *head = NULL, *tail = NULL;
    int x;

    while (scanf("%d", &x) == 1 && x > 0)
        addq(&head, &tail, x);

    printf("Print queue\n");
    while (head != NULL)
        printf("%d\n", delete(&head, &tail));

    return 0;
}

