#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
struct Node
{
    char data[20];
    struct Node *next;
    struct Node *prev;
};

int isEmpty(struct Node *start)
{
    if (start == NULL)
    {
        return 1;
    }
    return 0;
}

int isFull(struct Node *ptr)
{
    if (ptr == NULL)
    {
        return 1;
    }
    return 0;
}

int insAtBeg(struct Node **start, struct Node **end, char value[], int *count)
{
    struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
    if (nn != NULL)
    {
        strcpy(nn->data, value);
        nn->next = *start;
        if ((*end) == NULL)
        {
            (*end) = nn;
        }
        else{
            (*start)->prev = nn;
        }
        nn->prev = *end;
        (*start) = nn;
        (*end) -> next = *start;
        (*count)++;
        return 1;
    }
    return 0;
}

int insAtEnd(struct Node **start, struct Node **end, char value[], int *count)
{
    if (isEmpty(*start))
    {
        return insAtBeg(start, end, value, count);
    }
    else
    {
        struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
        if (nn != NULL)
        {
            strcpy(nn->data, value);
            nn->next = *start;
            nn->prev = (*end);
            (*end)->next = nn;
            (*end) = nn;
            (*count)++;
            return 1;
        }
    }
    return 0;
}

int insAtPos(struct Node **start, struct Node **end, char value[], int position, int *count) 
{
    if (position == 1)
    {
        return insAtBeg(start, end, value, count);
    }
    else if (position == (*count) + 1)
    {
        return insAtEnd(start, end, value, count);
    }
    else if (position <= 0 || position > (*count) + 1)
    {
        printf("Invalid Position Number\n");
        return 0;
    }
    else
    {
        int i;
        struct Node *search;
        struct Node *nn = (struct Node *)malloc(sizeof(struct Node));
        if (((*count) / 2) <= position)
        {
            search = *start;
            for (i = 1; i < position - 1; i++)
            {
                search = search->next;
            }
            if (nn != NULL)
            {
                strcpy(nn->data, value);
                nn->prev = search;
                nn->next = search->next;
                search->next = nn;
                (nn->next)->prev = nn;
                (*count)++;
                return 1;
            }
        }
        else
        {
            search = *end;
            for (i = 1; i < position - 1; i++)
            {
                search = search->prev;
            }
            if (nn != NULL)
            {
                strcpy(nn->data, value);
                nn->next = search;
                nn->prev = search -> prev;
                search->prev = nn;
                (nn->prev)->next = nn;
                (*count)++;
                return 1;
            }
        }
    }
    return 0;
}

int delfromBeg(struct Node **start, struct Node **end, int *count)
{
    if (*start == NULL)
    {
        printf("List is empty. Cannot delete.\n");
        return 0;
    }

    struct Node *temp = *start;
    *start = (*start)->next;
    if (*start == temp)
    {
        *start = NULL;
        *end = NULL;
    }
    else{
        (*end)->next = *start;
        (*start)->prev = *end;
    }

    free(temp);
    (*count)--;
    temp = NULL;
    return 1;
}

int delfromEnd(struct Node **start, struct Node **end, int *count)
{
    struct Node *temp;
    if (*start == NULL)
    {
        printf("List is empty. Cannot delete.\n");
        return 0;
    }

    temp = *end;

    if ((*start)->next == *start)
    {
        *start = NULL;
        *end = NULL;
    }
    else
    {
        *end = temp->prev;
        (*end)->next = *start;
        (*start)->prev = *end;
    }

    free(temp);
    (*count)--;
    temp = NULL;
    return 1;
}

int delfromPos(struct Node **start, struct Node **end, int position, int *count)
{
    if (position == 1)
    {
       return delfromBeg(start, end, count);
    }
    else if (position == (*count) + 1)
    {
       return delfromEnd(start, end, count);
    }
    else if (position <= 0 || position > (*count) + 1)
    {
        printf("Invalid Position Number\n");
        return 0;
    }
    else
    {
        int i;
        struct Node *search, *temp;

        if (((*count) / 2) <= position)
        {
            search = *start;
            for (i = 1; i < position - 1; i++)
            {
                search = search->next;
            }
            temp = search->next;
            search -> next = temp->next;
            (temp->next)->prev = search;
        }
        else
        {
            search = *end;
            for (i = 1; i < position - 1; i++)
            {
                search = search->prev;  
            }
            temp = search->prev;
            search -> prev = temp->prev;
            (temp->prev)->next = search;
        }
        free(temp);
        temp = NULL;
        search = NULL;
        (*count)--;
        return 1;
    }
    return 0;
}

void display(struct Node *start)
{
    struct Node *ptr = start;
    if (ptr == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    do 
    {
        printf("%s\n", ptr->data);
        ptr = ptr->next;
    }while(ptr != start);
}

char *LinearSearch(struct Node *start, char key[])
{
    struct Node *ptr = start;
    if (ptr == NULL)
    {
        printf("List is Empty\n");
        return NULL;
    }

    do{
        if (ptr->data == key)
        {
            return ptr->data;
        }
        ptr = ptr->next;
    }while (ptr != start);
    return NULL;
}

int main()
{
    struct Node *start = NULL, *end = NULL;
    int count = 0, pos;
    char ch, ch2, val[20];

    do
    {
        printf("Press 1: Insert\nPress 2: Delete\nPress 3: Display List\nPress 4: Search\nPress 5: Exit\n\n");
        ch = getch();
        if (ch == '1')
        {
            printf("Enter String to be Inserted\n");
            gets(val);
            printf("Press 1: Insert At Begin\t\tPress 2: Insert At Position\t\tPress 3: Insert At End\n\n");
            ch2 = getch();
            if (ch2 == '1')
            {
                if (insAtBeg(&start, &end, val, &count))
                {
                    printf("Insertion Successfull\n");
                }
            }
            else if (ch2 == '2')
            {
                printf("Enter Position\n");
                scanf("%d", &pos);

                if (insAtPos(&start, &end, val, pos, &count))
                {
                    printf("Insertion Successfull\n");
                }
            }
            else if (ch2 == '3')
            {
                if (insAtEnd(&start, &end, val, &count))
                {
                    printf("Insertion Successfull\n");
                }
            }
            else
            {
                printf("Invalid Option\n");
            }
        }
        else if (ch == '2')
        {
            printf("Press 1: Delete At Begin\t\tPress 2: Delete At Position\t\tPress 3: Delete At End\n\n");
            ch2 = getch();
            if (ch2 == '1')
            {
                if (delfromBeg(&start, &end, &count))
                {
                    printf("Deletion Successfull\n");
                }
            }
            else if (ch2 == '2')
            {
                printf("Enter Position\n");
                scanf("%d", &pos);
                if (delfromPos(&start, &end, pos, &count))
                {
                    printf("Deletion Successfull\n");
                }
            }
            else if (ch2 == '3')
            {
                if (delfromEnd(&start, &end, &count))
                {
                    printf("Deletion Successfull\n");
                }
            }
            else
            {
                printf("Invalid Option\n");
            }
        }
        else if (ch == '3')
        {
            printf("Displaying Linked List\n");
            display(start);
        }
        else if (ch == '4')
        {
            printf("Enter Value to be Searched\n");
            gets(val);

            if (LinearSearch(start, val) == NULL)
            {
                printf("Element Not Available\n");
            }
            else
            {
                printf("%s is available in list\n", val);
            }
        }
        else if (ch == '5')
        {
            while (start != NULL)
            {
                delfromBeg(&start, &end, &count);
            }
            printf("Exiting From Program\n");
        }
        else
        {
            printf("Invalid Option\n");
        }
    } while (ch != '5');
}