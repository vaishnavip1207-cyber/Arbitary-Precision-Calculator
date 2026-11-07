
#include "apc.h"

Dlist *subtraction(const Dlist *a, const Dlist *b)
{
    Dlist *result = NULL;
    Dlist *tail = NULL;
    int borrow = 0;

    while (a != NULL)
    {
        int d1 = a->data;
        int d2 = (b != NULL) ? b->data : 0;

        int diff = d1 - d2 - borrow;

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
        {
            free_list(result);
            return NULL;
        }

        new->data = diff;
        new->link = NULL;

        if (result == NULL)
            result = new;
        else
            tail->link = new;

        tail = new;

        a = a->link;

        if (b != NULL)
            b = b->link;
    }

    if (result == NULL)
        return insert_first(NULL, 0);

    /* Remove unnecessary most-significant zeros */
    while (result->link != NULL && tail->data == 0)
    {
        Dlist *temp = result;

        while (temp->link != tail)
            temp = temp->link;

        free(tail);
        tail = temp;
        tail->link = NULL;
    }

    return result;
}
