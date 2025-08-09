#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *link;
};

void add_to_head(struct node **head, int data){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->link = *head;
    *head = temp;
}

void add_to_tail(struct node *head, int data){
    struct node *ptr, *temp;
    ptr = head;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->link = NULL;
    while(ptr->link != NULL){
        ptr = ptr->link;
    }
    ptr->link = temp;
}

void add_to_position(struct node *head, int position, int data)
{
    struct node *ptr, *temp;
    ptr = head;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->link = NULL;

    while(position > 2){
        ptr = ptr->link;
        position--;
    }
    temp->link = ptr->link;
    ptr->link = temp;
};

int main(){
    struct node *head = NULL;
    head = (struct node *)malloc(sizeof(struct node));
    head->data = 54;
    head->link = NULL;

    add_to_head(&head, 99);
    add_to_tail(head,12);
    add_to_tail(head,18);
    add_to_position(head,4,24);
    
    struct node* ptr = head;
    while(ptr != NULL){
        printf("%d ",ptr->data);
        ptr = ptr->link;
    }
    return 0;
}