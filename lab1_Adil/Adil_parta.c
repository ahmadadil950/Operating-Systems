#include <stdio.h>
#include <stdlib.h>

/*Creating the node*/
struct Node
{
    int data;
    struct Node* next;
};

void insert_begin(struct Node** head_ref, int new_data) 
{
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

  new_node -> data = new_data;

  new_node->next = (*head_ref);

  (*head_ref) = new_node;
}

void insert_after(struct Node* prev_node, int new_data) 
{
  if (prev_node == NULL) 
  {
  printf("the given previous node cannot be NULL");
  return;
  }

  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = new_data;
  new_node->next = prev_node->next;
  prev_node->next = new_node;
}

void insert_end(struct Node** head_ref, int new_data) 
{
  struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));
  struct Node* last = *head_ref;

  new_Node->data = new_data;
  new_Node->next = NULL;

  if (*head_ref == NULL) {
  *head_ref = new_Node;
  return;
  }

  while (last->next != NULL) last = last->next;

  last->next = new_Node;
  return;
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
    }
    return 0;
}

void traverse(struct Node** head_ref)
{
    struct Node* temp = *head_ref;
    printf("\n\nList elements are - \n");
    while(temp != NULL)
    {
        printf("%d --->",temp->data);
        temp = temp->next;
    }
}

void print_linkedlist(struct Node* node)
{
    while(node != NULL)
    {
        printf("%d", node->data);
        node = node->next;
    }
}

void delete(struct Node** head_ref, int key)
{
    struct Node* temp = *head_ref, *prev;

    if(temp != NULL && temp->data == key)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    if(temp == NULL)
        return;

    while(temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    free(temp);
}


void sortList(struct Node** head_ref)
{
    struct Node *current = *head_ref, *index = NULL;
    int temp;

    if(head_ref == NULL)
    {
        return;
    }
    else{
        while(current != NULL)
        {
          index = current->next;

          while(index != NULL)
          {
            if(current->data > index->data)
            {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }

            index = index->next;
          }
          current = current->next;
        }
    }
}

int main()
{
    struct Node* head = NULL;
    int element;

    printf("Please enter an element to insert at the end of Linked list: \n");
    scanf("%d", &element);

    insert_begin(&head, element);
    scanf("%d", &element);
    insert_begin(&head, element);
    scanf("%d", &element);
    insert_after(head->next, element);
    insert_begin(&head,262);
    insert_end(&head,98);

    traverse(&head);
    printf("\n");

    printf("linked list after deletion:");
    delete(&head, 262);
    traverse(&head);
    printf("\n");

    int find;
    printf("Please enter an item to find \n");
    scanf("%d", &find);

    if (searchNode(&head, find)) 
    {
        printf("\n%d is found", find);
    } 
    else 
    {
        printf("\n%d is not found", find);
    }
    printf("\n");

    sortList(&head);
    printf("Sorted Linked list");
    traverse(&head);

}
