#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* add_Empty(struct Node* Last, int data)
{
    if(Last != NULL)
    {
        return Last;
    }

    struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));

    new_Node->data = data;
    Last = new_Node;
    Last->next = Last;

    return Last;
}

struct Node* insert_begin(struct Node* Last, int data)
{
    if(Last == NULL)
    {
        return add_Empty(Last,data);
    }

    struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));

    new_Node->data = data;
    new_Node->next = Last->next;
    Last->next = new_Node;

    return Last;
}

struct Node* insert_end(struct Node* Last, int data)
{
    if(Last == NULL)
    {
        return add_Empty(Last,data);
    }
    struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));
    new_Node->data = data;

    new_Node->next = Last->next;

    Last->next = new_Node;
    Last = new_Node;

    return Last;
}

void traverse(struct Node* last)
{
  struct Node* p;

  if (last == NULL) 
  {
  printf("The list is empty");
  return;
  }

  p = last->next;

  do 
  {
  printf("%d ", p->data);
  p = p->next;

  } while (p != last->next);
}

void Node_delete(struct Node** Last, int key)
{
    if (*Last == NULL) 
        return;

  // if the list contains only a single node
  if ((*Last)->data == key && (*Last)->next == *Last) 
  {
    free(*Last);
    *Last = NULL;
    return;
  }

  struct Node *temp = *Last, *d;

  if((*Last)->data == key)
  {
    while(temp->next != *Last)
    {
        temp = temp->next;
    }

    temp->next = (*Last)->next;
    free(*Last);
    *Last = temp->next;
  }

  while(temp->next != *Last && temp->next->data != key) {
  temp = temp->next;
  }

  // if node to be deleted was found
  if (temp->next->data == key) {
  d = temp->next;
  temp->next = d->next;
  free(d);
  }
}

int searchNode(struct Node** head_ref, int k)
{
    struct Node* current = *head_ref;

    while(current != NULL)
    {
        if(current->data == k)
        {
            return 1;
        }
        current = current->next;
        break;
    }
    return 0;
}

int main()
{
    struct Node* Last = NULL;
    int element;

    printf("Please enter an element to insert at the end of Linked list: \n");
    scanf("%d", &element);

    // This will inialize Node with element
    Last = add_Empty(Last, element);
    scanf("%d", &element);
    /*This will push new element before the previous node
      EX: (insert_begin -> add_empty) */
    Last = insert_begin(Last, element);
    scanf("%d", &element);
    Last = insert_end(Last, element);
    scanf("%d", &element);
    Last = insert_begin(Last,element);

    printf("Linked List is: \n");
    traverse(Last);
    printf("\n");

    printf("Linked List after deletion \n");
    Node_delete(&Last,2);

    traverse(Last);
    printf("\n");

    int find;
    printf("Please enter an element to find: \n");
    scanf("%d", &find);
    
    if (searchNode(&Last, find)) 
    {
        printf("\n%d is found", find);
    } 
    else 
    {
        printf("\n%d is not found", find);
        return 0;
    }

    return 0;

}
