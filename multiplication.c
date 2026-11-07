
#include "apc.h"

Dlist *multiplication(const Dlist *a, const Dlist *b)
{
    if (a == NULL || b == NULL)
        return insert_first(NULL, 0);

    int len1 = 0, len2 = 0;

    const Dlist *temp = a;

    while (temp != NULL)
    {
        len1++;
        temp = temp->link;
    }

    temp = b;

    while (temp != NULL)
    {
        len2++;
        temp = temp->link;
    }

    int *result = calloc(len1 + len2, sizeof(int));

    if (result == NULL)
        return NULL;

    int *n1 = malloc(len1 * sizeof(int));
    int *n2 = malloc(len2 * sizeof(int));

    if (n1 == NULL || n2 == NULL)
    {
        free(result);
        free(n1);
        free(n2);
        return NULL;
    }

    temp = a;

    for (int i = 0; i < len1; i++)
    {
        n1[i] = temp->data;
        temp = temp->link;
    }

    temp = b;

    for (int i = 0; i < len2; i++)
    {
        n2[i] = temp->data;
        temp = temp->link;
    }

    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            result[i + j] += n1[i] * n2[j];
        }
    }

    for (int i = 0; i < len1 + len2 - 1; i++)
    {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    int len = len1 + len2;

    while (len > 1 && result[len - 1] == 0)
        len--;

    Dlist *head = NULL;
    Dlist *tail = NULL;

    for (int i = 0; i < len; i++)
    {
        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
        {
            free_list(head);
            free(result);
            free(n1);
            free(n2);
            return NULL;
        }

        new->data = result[i];
        new->link = NULL;

        if (head == NULL)
            head = new;
        else
            tail->link = new;

        tail = new;
    }

    free(result);
    free(n1);
    free(n2);

    return head;
}
