/*

  Copyright © 2016 Syed Arsal Abbas.

*/

#include "a7Defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ARR  64
#define MAX_STR  32

void readString(char*);
void readInt(int*);
void initCat(int, char*, GenderType, CatType**);
void initAllCats(CatListType**);
void print(CatType*);
void printCats(CatListType*);
void freeCats(CatListType*);
void Add(CatType*, CatListType*);

int main(void){
	
	CatListType *catPtr;
  	catPtr = malloc(sizeof(CatListType));
   
  	initAllCats(&catPtr);
  	printCats(catPtr);
  	freeCats(catPtr);
  
  	return 0;
}
 
/*
Function:  initAllCats
Purpose :  dynamically allocates the linked list structure and initializes the fields
*/
void initAllCats(CatListType** catPtr){
	//setting both head and tail to null
  	(*catPtr)->head = NULL; 
  	(*catPtr)->tail = NULL;
 
  	CatType *cat;
  	int id;
  	char name[MAX_STR];
  	int genderInt;
  	GenderType gender;
 
  	while (1){
  		printf("Enter the name of the Cat or type 'quit' to quit: ");
  		readString(name);
  
  		if(strcmp(name, "quit") == 0){
   	 		printf("You entered to Quit \n");
    		return;
  		}
 
  		printf("Please enter a unique ID for the Cat: ");
  		readInt(&id);
   
		//error checking for the Gender to only input 0(male) or 1(feMale)
   		while(1){
      		printf("Print 0 for male, print 1 for female: ");
      		readInt(&genderInt);
      
	  		if(genderInt == 0 || genderInt == 1){
				break;
      		}
      		printf("Please enter a valid input!!!!\n");
    	} 
		
		gender = genderInt;
 
  		initCat(id, name, gender, &cat);
  		Add(cat, *catPtr);
  		printCats(*catPtr);
  	}
}
 
/*
Function:   initCat
Purpose :   allocates memory for CatType.
*/
void initCat(int id, char* name, GenderType gender, CatType** cat){
	*cat = (CatType*) malloc(sizeof(CatType));
 	(*cat)->id = id;
  	strcpy((*cat)->name, name);
  	(*cat)->gender = gender;
}
 
/*
Function:   Add
Purpose :   Creates a new NodeType, adds properties of cat to it and adds it to the current linked list based on name alphabetical order.
out		:   A linked list with one more node.
*/
void Add(CatType *cat, CatListType* catPtr){
	NodeType* node = malloc(sizeof(NodeType)); 
	NodeType* currentNode = catPtr->head;
 
  	node->data = cat;
  	node->prev = NULL;
  	node->next = NULL;
 
  	//add node in the list
  	if (catPtr->head == NULL){ 
    	printf("Node goes at the head\n");
    	catPtr->head = node;
    	catPtr->tail = node;
    	return;
	
  	} 	
  	
	//node goes before the head
  	if (strcmp(cat->name, catPtr->head->data->name) < 0){ 
    	node->next = catPtr->head;
    	catPtr->head->prev = node;
    	catPtr->head = node;
    	return;
	
  	}
  
	//node goes in the middle
	while (currentNode != NULL){
		if (strcmp(cat->name, currentNode->data->name) <= 0) {
	        node->next = (*currentNode).next;
	        node->prev = currentNode;
	        (*currentNode).next = node;
	        return;
		
      	}
	  	
		//node goes to the tail
      	if (currentNode->next == NULL){ 
	        catPtr->tail->next = node;
	        node->prev = catPtr->tail;
	        catPtr->tail = node;
	        return;
			
		}
      
	  currentNode = currentNode->next;
	}
}
 
/*
Function:  freeCats
Purpose :  Deallocates memory
*/
void freeCats(CatListType* catPtr){
	NodeType *node;
 
  	while (catPtr->head != NULL){
		node = catPtr->head;
    	catPtr->head = catPtr->head->next;
   	 	free(node);	
	}
}
 
/*
Function:  print
Purpose :  prints the a CatType pointer's information.
*/
void print(CatType* cat){
	
	char gender[MAX_STR];
  
  	if (cat->gender == 0){
     	strcpy(gender, "MALE");
	}
	else{
		strcpy(gender, "FEMALE");
	}
	  
	printf("Name of your cat is: %s \n", cat->name);
	printf("ID of your cat is: %d \n", cat->id);
	printf("And the cat is a %s.\n \n", gender);
	    
}
 
/*
Function:  printCats
Purpose:   prints all data for every CatType in the linked list
*/
void printCats(CatListType* catPtr){
	
	if (catPtr->head == NULL){
    	printf("head is a null \n");
    	return;
  	}
 
  	NodeType* currentNode = catPtr->head;
  
	int i=1;
  	
	printf("\nLIST OF CATS IN ALPHABATICAL ORDER!!! \n");
  	
	while(currentNode != NULL){
    	printf("Cat #%d: \n", i);
    	print(currentNode->data);
    	i++;
    	currentNode = currentNode->next;
	
  	}
 
  	currentNode = catPtr->tail;
  
  	printf("LIST OF CATS IN REVERSE: \n");
  	
	while(currentNode != NULL){
    	i--;
    	printf("Cat #%d: \n", i);
    	print(currentNode->data);
    	currentNode = currentNode->prev;	
  	}
}
 
/*
Function:  readString
Purpose :  reads a string from standard input
out     :  string read in from the user
*/
void readString(char *str){
  char tmpStr[MAX_STR];
  fgets(tmpStr, sizeof(tmpStr), stdin);
  tmpStr[strlen(tmpStr)-1] = '\0';
  strcpy(str, tmpStr);
}
 
/*
Function:  readInt
Purpose :  reads an integer from standard input
out     :  integer read in from the user
*/
void readInt(int *x){
  char str[MAX_STR];
  readString(str);
  sscanf(str, "%d", x);
}
