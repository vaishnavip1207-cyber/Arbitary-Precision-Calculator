
#include "apc.h"

static int is_zero(const Dlist *head)
{
    while (head != NULL)
    {
        if (head->data != 0)
            return 0;

        head = head->link;
    }

    return 1;
}

Dlist *division(const Dlist *a, const Dlist *b)
{
    if (b == NULL || is_zero(b))
        return NULL;

    if (a == NULL || is_zero(a))
        return insert_first(NULL, 0);

    if (compare_lists(a, b) < 0)
        return insert_first(NULL, 0);

    int len = 0;

    const Dlist *temp = a;

    while (temp != NULL)
    {
        len++;
        temp = temp->link;
    }

    int *digits = malloc(len * sizeof(int));
    int *quotient = calloc(len, sizeof(int));

    if (digits == NULL || quotient == NULL)
    {
        free(digits);
        free(quotient);
        return NULL;
    }

    temp = a;

    for (int i = 0; i < len; i++)
    {
        digits[i] = temp->data;
        temp = temp->link;
    }

    Dlist *remainder = NULL;

    /* Process dividend from most significant digit */
    for (int i = len - 1; i >= 0; i--)
    {
        if (remainder == NULL)
        {
            remainder = insert_first(NULL, digits[i]);

            if (remainder == NULL)
                goto error;
        }
        else if (is_zero(remainder))
        {
            remainder->data = digits[i];
        }
        else
        {
            remainder = insert_first(remainder, digits[i]);

            if (remainder == NULL)
                goto error;
        }

        while (compare_lists(remainder, b) >= 0)
        {
            Dlist *new_rem = subtraction(remainder, b);

            if (new_rem == NULL)
                goto error;

            free_list(remainder);
            remainder = new_rem;
            quotient[i]++;
        }
    }

    free_list(remainder);
    remainder = NULL;

    Dlist *head = NULL;
    Dlist *tail = NULL;

    /* Convert quotient digits to LSF-first linked list */
    for (int i = 0; i < len; i++)
    {
        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
        {
            free_list(head);
            goto error;
        }

        new->data = quotient[i];
        new->link = NULL;

        if (head == NULL)
            head = new;
        else
            tail->link = new;

        tail = new;
    }

    /* Remove most-significant zeros */
    while (head->link != NULL && tail->data == 0)
    {
        Dlist *t = head;

        while (t->link != tail)
            t = t->link;

        free(tail);
        tail = t;
        tail->link = NULL;
    }

    free(digits);
    free(quotient);

    return head;

error:
    free_list(remainder);
    free(digits);
    free(quotient);
    return NULL;
}
