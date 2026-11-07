
#include "apc.h"

/* Check whether the number is zero */
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

/* Validate input number */
static int valid_number(const char *num)
{
    if (*num == '-' || *num == '+')
        num++;

    if (*num == '\0')
        return 0;

    while (*num != '\0')
    {
        if (*num < '0' || *num > '9')
            return 0;

        num++;
    }

    return 1;
}

int main(void)
{
    char num1[1000], num2[1000];
    char op;

    int neg1 = 0;
    int neg2 = 0;
    int result_negative = 0;
    int comparison;

    Dlist *a = NULL;
    Dlist *b = NULL;
    Dlist *result = NULL;

    printf("Enter: number operator number\n");

    if (scanf("%999s %c %999s", num1, &op, num2) != 3)
    {
        printf("Invalid input\n");
        return FAILURE;
    }

    if (!valid_number(num1) || !valid_number(num2))
    {
        printf("Invalid number\n");
        return FAILURE;
    }

    /* Extract first number sign */
    if (num1[0] == '-')
    {
        neg1 = 1;
        memmove(num1, num1 + 1, strlen(num1));
    }
    else if (num1[0] == '+')
    {
        memmove(num1, num1 + 1, strlen(num1));
    }

    /* Extract second number sign */
    if (num2[0] == '-')
    {
        neg2 = 1;
        memmove(num2, num2 + 1, strlen(num2));
    }
    else if (num2[0] == '+')
    {
        memmove(num2, num2 + 1, strlen(num2));
    }

    a = create_list(num1);
    b = create_list(num2);

    if (a == NULL || b == NULL)
    {
        printf("Memory allocation failed\n");
        free_list(a);
        free_list(b);
        return FAILURE;
    }

    if (is_zero(a))
        neg1 = 0;

    if (is_zero(b))
        neg2 = 0;

    switch (op)
    {
        case '+':

            if (neg1 == neg2)
            {
                result = addition(a, b);
                result_negative = neg1;
            }
            else
            {
                comparison = compare_lists(a, b);

                if (comparison == 0)
                    result = insert_first(NULL, 0);

                else if (comparison > 0)
                {
                    result = subtraction(a, b);
                    result_negative = neg1;
                }
                else
                {
                    result = subtraction(b, a);
                    result_negative = neg2;
                }
            }

            break;

        case '-':

            neg2 = !neg2;

            if (is_zero(b))
                neg2 = 0;

            if (neg1 == neg2)
            {
                result = addition(a, b);
                result_negative = neg1;
            }
            else
            {
                comparison = compare_lists(a, b);

                if (comparison == 0)
                    result = insert_first(NULL, 0);

                else if (comparison > 0)
                {
                    result = subtraction(a, b);
                    result_negative = neg1;
                }
                else
                {
                    result = subtraction(b, a);
                    result_negative = neg2;
                }
            }

            break;

        case '*':

            result = multiplication(a, b);
            result_negative = neg1 ^ neg2;
            break;

        case '/':

            if (is_zero(b))
            {
                printf("Error: Division by zero\n");
                free_list(a);
                free_list(b);
                return FAILURE;
            }

            result = division(a, b);
            result_negative = neg1 ^ neg2;
            break;

        default:

            printf("Invalid operator\n");
            free_list(a);
            free_list(b);
            return FAILURE;
    }

    if (result == NULL)
    {
        printf("Operation failed\n");
    }
    else
    {
        printf("Result: ");

        if (result_negative && !is_zero(result))
            printf("-");

        print_number(result);
        printf("\n");
    }

    free_list(a);
    free_list(b);
    free_list(result);

    return SUCCESS;
}
