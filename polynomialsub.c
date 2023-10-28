#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
struct Term
{
    int coeff;
    int power;
    struct Term *next;
};
typedef struct Term term;

int isEmpty(term *start)
{
    if (start == NULL)
    {
        return 1;
    }
    return 0;
}

int insert(term **start, term **end, int coeff, int pow)
{
    term *nn = (term *)malloc(sizeof(term));
    if (nn != NULL)
    {
        nn->coeff = coeff;
        nn->power = pow;
        nn->next = (*start);
        if (*start == NULL)
        {
            *end = nn;
        }
        (*start) = nn;
        return 1;
    }
    return 0;

}

int insAtEnd(term **start, term **end, int coeff, int pow)
{
    if (*end == NULL && *start == NULL)
    {
        return insert(start, end, coeff, pow);
    }
    else
    {
        term *nn = (term *)malloc(sizeof(term));
        if (nn != NULL)
        {
            nn->coeff = coeff;
            nn->power = pow;
            nn->next = NULL;
            (*end)->next = nn;
            (*end) = nn;
            return 1;
        }
    }
    return 0;
}

int freeAll(term **start)
{
    term *temp;
    if ((*start) == NULL)
    {
        return 0;
    }
    while ((*start) != NULL)
    {
        temp = *start;
        (*start) = (*start)->next;
        free(temp);
    }
    return 1;
}
void printeqs(term *start)
{
    term *ptr = start;
    while (ptr != NULL)
    {
        if (ptr->power != 0)
        {
            if (ptr->coeff > 0)
            {  
                if (ptr != start)
                {
                    printf("+ %dx^%d ", ptr->coeff, ptr->power);
                }
                else{
                    printf("%dx^%d ", ptr->coeff, ptr->power);
                }
            }
            else if (ptr->coeff < 0)
            {
                printf("- %dx^%d ", ((-1)*ptr->coeff), ptr->power);
            }
        }
        else
        {
            if (ptr->coeff > 0)
            {
                printf("+ %d", (ptr->coeff));
            }
            else if (ptr->coeff < 0)
            {
                printf("- %d", ((-1)*ptr->coeff));
            }
        }
        ptr = ptr->next;
    }
    printf("\n");
}

term *addition(term *eq1, term *eq2, term **end)
{
    term *temp = NULL;
    while (eq1 != NULL && eq2 != NULL)
    {
        if (eq1->power > eq2->power)
        {
            insAtEnd(&temp, end, eq1->coeff, eq1->power);
            eq1 = eq1->next;
        }
        else if (eq1->power < eq2->power)
        {
            insAtEnd(&temp, end, eq2->coeff, eq2->power);
            eq2 = eq2->next;
        }
        else
        {
            insAtEnd(&temp, end, (eq1->coeff) - (eq2->coeff), eq1->power);
            eq1 = eq1->next;
            eq2 = eq2->next;
        }
        
    }
    while (eq1 != NULL)
    {
        insAtEnd(&temp, end, eq1->coeff, eq1->power);
        eq1 = eq1->next;
    }
    while (eq2 != NULL)
    {
        insAtEnd(&temp, end, eq2->coeff, eq2->power);
        eq2 = eq2->next;
    }
    return temp;
}

int main()
{
    term *eq1 = NULL, *eq2 = NULL, *res = NULL, *eq1end = NULL, *eq2end = NULL, *resend = NULL;
    int pow, i, coeff;
    do
    {
        printf("Enter highest power of x of first equation (Upto 10)\n");
        scanf("%d", &pow);
    } while (pow < 0 || pow > 10);

    printf("Enter First Equation\n");

    for (i = 0; i <= pow; i++)
    {
        printf("Enter Coefficient of x^%d\n", i);
        scanf("%d", &coeff);
        if (coeff != 0 || i == 0)
        {
            insert(&eq1, &eq1end, coeff, i);
        }
    }

    do
    {
        printf("Enter highest power of x of second equation (Upto 10)\n");
        scanf("%d", &pow);
    } while (pow < 0 || pow > 10);

    printf("Enter Second Equation\n");

    for (i = 0; i <= pow; i++)
    {
        printf("Enter Coefficient of x^%d\n", i);
        scanf("%d", &coeff);
        if (coeff != 0 || i == 0)
        {
            insert(&eq2, &eq2end, coeff, i);
        }
    }
    printf("Equation first:\t");
    printeqs(eq1);
    printf("Equation second:\t");
    printeqs(eq2);
    printf("Subtraction of Above equations are\n");
    res = addition(eq1, eq2, &resend);
    printeqs(res);
    freeAll(&eq1);
    freeAll(&eq2);
    freeAll(&res);
}
