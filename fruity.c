#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Author: dkutosi
// Assignment : Zero
// Date: February 6, 2016


// This program reads standard input line by line. It then compares how many of the same thing
// are exactly the same in nature, and calculates a percentage of similar string. The program
// should print out each unique item line by line along with how many items they are and the
// percentage total of each item

struct node{
	char word[80];
	float total;
	float avg;
	struct node *next;
} *head;

void display(struct node *head);
struct node* weights(struct node *head);
struct node* makeList(struct node *start);

float totalNode;

// This function when called will start with and empty node, scan for
//input, and use that input to create a dynamic linked list


struct node* makeList(struct node *start){

	char data[80];
	char fruit[80];
    
	float average;
	float found;

	struct node *current;
	current = (struct node *)malloc(sizeof(struct node));
    	totalNode = 0;
	average =0;


	while(scanf(" %s", &fruit) != EOF){
		totalNode = totalNode+ 1;
		found = 0;

		struct node *temp;
		temp = (struct node *)malloc(sizeof(struct node));

		strcpy(temp -> word, fruit);
		temp->next=NULL;
		current = head;

		if (head->word == NULL){
		  temp -> total = 1;
		  head=temp;

	   }

	   else{
		   current = head;
		   if(strcmp(current->word, temp -> word) == 0){
			   head -> total = head -> total +1;
		   }
		   else{
			   while(current -> next != NULL && found = 0){

				   int x = (strcmp(current-> next->word, temp -> word));
				   if(x == 0){

					   current ->next-> total = current ->next-> total+1;
					   found = 1;
				   }
				   current = current->next;
			   }
			   if(found == 0){
				   current -> next= temp;
				   current-> next-> total = 1;
			   }
		   }
	   }
	}
	current = head;
	return current;
}

//Method takes a node and gets the pecentage of the number of similar strings entered with the total number of
// unique strings
struct node* weights(struct node *head){

	struct node *thisOne;
	thisOne = (struct node *)malloc(sizeof(struct node));
	thisOne = head;

	while(thisOne -> word != NULL){
		thisOne -> avg = (thisOne -> total / totalNode)*100;
		thisOne = thisOne -> next;
	}
	return head;


}

// Method takes in the head node of a linked list. The method that tranverses the list
// printing the data contained within the list.
void display(struct node *head){

	struct node *thisOne;
	thisOne = (struct node *)malloc(sizeof(struct node));
	thisOne = head;


	while(thisOne -> word != NULL){
		printf("\n%s\t%5.0f \t %5.1f%%", thisOne -> word, thisOne->total, thisOne-> avg );
		thisOne = thisOne -> next;
	}
}


int main(int argc, char* argv[])
{
    struct node *start;
	struct node *weighted;
	struct node *using;

	using = makeList(start);
	weighted = weights(using);
	display(weighted);

	return 0;
}
