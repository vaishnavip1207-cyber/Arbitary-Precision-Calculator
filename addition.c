
#include "apc.h"

Dlist *addition(const Dlist *a, const Dlist *b)
{
    Dlist *result = NULL;
    Dlist *tail = NULL;
    int carry = 0;

    while (a != NULL || b != NULL || carry != 0)
    {
        int sum = carry;

        if (a != NULL)
        {
            sum += a->data;
            a = a->link;
        }

        if (b != NULL)
        {
            sum += b->data;
            b = b->link;
        }

        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
        {
            free_list(result);
            return NULL;
        }

        new->data = sum % 10;
        new->link = NULL;
        carry = sum / 10;

        if (result == NULL)
            result = new;
        else
            tail->link = new;

        tail = new;
    }

    if (result == NULL)
        result = insert_first(NULL, 0);

    return result;
}
