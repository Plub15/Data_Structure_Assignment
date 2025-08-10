#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

struct node{
    int data;
    struct node *link;
};

int printer(struct node *head, struct node *extra)
{
	FILE *fp = fopen("img.dot","w");
	if(fp == NULL)
	{
		printf("Error: no permission to create files\n");
		return 1;
	}

	int node_cnt = 0;

	//Graphviz graph start
	fprintf(fp,"digraph LL{\n rankdir=\"LR\";\n");
	fprintf(fp,"node [shape=Mdiamond] head;");
	while(head != NULL)
	{
		fprintf(fp,"node [shape=\"rect\"] n%d [label=\"%d\"];\n",node_cnt, head->data);
		if(node_cnt == 0)
		{
			fprintf(fp,"head -> n0;\n");
		}
		else
		{	
			fprintf(fp,"n%d -> n%d;\n",node_cnt - 1,node_cnt);
		}
		
		//if we have provided an extra pointer
		if(extra == head)
		{
		  fprintf(fp,"node [shape=Mdiamond] p;");
		  fprintf(fp,"p -> n%d;",node_cnt);
		}
		node_cnt++;
		head = head->link;
	}
	//Graphviz graph end
	fprintf(fp,"}\n");
	fclose(fp);
	system("dot -Tpng img.dot > img.png");
	printf("Graph saved as img.png\n");
	return 0;
}

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

void remove_from_head(struct node **head){
    if(*head == NULL)
        printf("List is already empty");
    else
    {
        struct node *temp = *head;
        *head = (*head)->link;
        free(temp);
    }
}

void remove_from_tail(struct node *head){
    if(head == NULL)
        printf("List is already empty");
    else if(head->link == NULL)
    {
        free(head);
    }
    else
    {
        struct node *secondlastptr = head, *lastptr = head;
        while(lastptr->link != NULL)
        {
            secondlastptr = lastptr;
            lastptr = lastptr->link;
        }
        secondlastptr->link = NULL;
        free(lastptr);
    }

}

void remove_from_position(struct node *head,int position){
    if(head == NULL)
        printf("List is already empty");
    else
    {
        struct node *current = head, *previous = head;
        while(position > 1)
        {
            previous = current;
            current = current->link;
            position--;
        }
        previous->link = current->link;
        free(current);
    }
}

int main(){
    struct node *head = NULL;
    head = (struct node *)malloc(sizeof(struct node));
    head->data = 54;
    head->link = NULL;

    add_to_head(&head, 99);
    add_to_tail(head,12);
    add_to_tail(head,18);
    add_to_position(head,3,24);
    remove_from_head(&head);
    remove_from_tail(head);
    remove_from_position(head,3);

    struct node* ptr = head;
    while(ptr != NULL){
        printf("%d ",ptr->data);
        ptr = ptr->link;
    }
    printer(head, head->link);
    return 0;
}