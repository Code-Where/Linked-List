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

void removeDuplicates(term *start){
    term *e1 = start, *e2, *temp;
    while (e1 != NULL)
    {
        e2 = e1 -> next;
        while(e2 != NULL)
        {
            if(e1->power == e2->power)
            {
                e1->coeff += e2->coeff;
                temp = e2;
                e2 = e2->next;
                e1->next = temp->next;
                free(temp);
            }
            else{
                e2 = e2->next;
            }
        }
        e1 = e1->next;
    }
}

term *multiplication(term *eq1, term *eq2, term **end)
{
    term *temp = NULL, *tempeq;
    while (eq1 != NULL)
    {
        tempeq = eq2;
        while(tempeq != NULL)
        {
            insAtEnd(&temp, end, (eq1->coeff)*(tempeq->coeff), (eq1->power)+(tempeq->power));
            tempeq = tempeq->next;
        }
        eq1 = eq1->next;
    }
    removeDuplicates(temp);
    return temp;
}

int main()
{
    term *eq1 = NULL, *eq2 = NULL, *prod = NULL, *eq1end = NULL, *eq2end = NULL, *prodend = NULL;
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

    printeqs(eq1);
    printeqs(eq2);
    printf("Multiplication of Above equations are\n");
    prod = multiplication(eq1, eq2, &prodend);
    printeqs(prod);
    freeAll(&eq1);
    freeAll(&eq2);
    freeAll(&prod);
}
