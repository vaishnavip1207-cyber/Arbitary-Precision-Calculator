
#include "apc.h"

/* Insert a digit at the beginning */
Dlist *insert_first(Dlist *head, int digit)
{
    Dlist *new = malloc(sizeof(Dlist));

    if (new == NULL)
        return NULL;

    new->data = digit;
    new->link = head;

    return new;
}

/* Insert a digit at the end */
Dlist *insert_last(Dlist *head, int digit)
{
    Dlist *new = malloc(sizeof(Dlist));

    if (new == NULL)
        return head;

    new->data = digit;
    new->link = NULL;

    if (head == NULL)
        return new;

    Dlist *temp = head;

    while (temp->link != NULL)
        temp = temp->link;

    temp->link = new;

    return head;
}

/* Create a linked list from a number string */
Dlist *create_list(const char *num)
{
    Dlist *head = NULL;
    Dlist *tail = NULL;

    int len = strlen(num);

    for (int i = len - 1; i >= 0; i--)
    {
        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
        {
            free_list(head);
            return NULL;
        }

        new->data = num[i] - '0';
        new->link = NULL;

        if (head == NULL)
            head = new;
        else
            tail->link = new;

        tail = new;
    }

    return head;
}

/* Free the entire linked list */
void free_list(Dlist *head)
{
    while (head != NULL)
    {
        Dlist *temp = head;
        head = head->link;
        free(temp);
    }
}

/* Count digits */
static int count_nodes(const Dlist *head)
{
    int count = 0;

    while (head != NULL)
    {
        count++;
        head = head->link;
    }

    return count;
}

/* Compare digits from most significant to least significant */
static int compare_digits(const Dlist *a, const Dlist *b, int count)
{
    if (count == 0)
        return 0;

    int result = compare_digits(a->link, b->link, count - 1);

    if (result != 0)
        return result;

    if (a->data > b->data)
        return 1;

    if (a->data < b->data)
        return -1;

    return 0;
}

/* Compare two positive numbers */
int compare_lists(const Dlist *a, const Dlist *b)
{
    int len1 = count_nodes(a);
    int len2 = count_nodes(b);

    /* Remove unnecessary most-significant zeros */
    while (len1 > 1)
    {
        const Dlist *temp = a;

        for (int i = 1; i < len1; i++)
            temp = temp->link;

        if (temp->data != 0)
            break;

        len1--;
    }

    while (len2 > 1)
    {
        const Dlist *temp = b;

        for (int i = 1; i < len2; i++)
            temp = temp->link;

        if (temp->data != 0)
            break;

        len2--;
    }

    if (len1 > len2)
        return 1;

    if (len1 < len2)
        return -1;

    if (len1 == 0)
        return 0;

    return compare_digits(a, b, len1);
}

/* Print digits in normal order */
static void print_reverse(const Dlist *head, int count)
{
    if (count == 0)
        return;

    print_reverse(head->link, count - 1);
    printf("%d", head->data);
}

/* Print the complete number */
void print_number(const Dlist *head)
{
    if (head == NULL)
    {
        printf("0");
        return;
    }

    int len = count_nodes(head);

    /* Ignore unnecessary leading zeros */
    while (len > 1)
    {
        const Dlist *temp = head;

        for (int i = 1; i < len; i++)
            temp = temp->link;

        if (temp->data != 0)
            break;

        len--;
    }

    print_reverse(head, len);
}
