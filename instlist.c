#include "instlist.h"
#include <stdlib.h>
#include <stdio.h>


int add_node( struct instlist* list, struct node* node){
  if (list == NULL){
    // error
    return -1;
  }
  if (node == NULL){
    // error
    return -1;
  }

  struct node* tmp = list->head;

  int length =1;

  if(tmp ==NULL){
    //empty list, insert node as head
    list->head = node;
  }
  else{
    // non-empty list find last node and append
    while (tmp->next !=NULL){
      tmp = tmp->next;
      length++;
    }
    tmp->next = node;
    length++;
  }

  return length;
}

//init
struct instlist* list_init(){
  struct instlist* list = (struct instlist*) malloc(sizeof(struct instlist));

  if (list == NULL){

    exit(-1);
  }

  list->head = NULL;

  return list;

}

//free used memory
void free_list(struct instlist* list){
  if (list != NULL){
    struct node* node = list->head;
    struct node* tmp = NULL;

    while(node != NULL){
      tmp = node;
      node = node->next;
      free(tmp);
    }

    free(list);

  }
}

struct node* list_malloc_node(instruction data){
  struct node* node = (struct node*)malloc(sizeof(struct node));
  if (node == NULL){
    exit(-1);
  }

  node->data = data;
  node->next = NULL;

  return node;
}


void list_print(struct instlist* list){

struct node* tmp = list->head;


  if(tmp == NULL){
    //empty list, say so
    printf("empty list :(");
  }
  else{
    // non-empty list find last node and append
    while (tmp != NULL){
      switch(tmp->data){
      case COMMA:
        printf("Comma ");
        break;
      case VINC:
        printf("Plus ");
        break;
      case DOT:
        printf("Dot ");
        break;
      case VDEC:
        printf("Minus ");
        break;
      case PINC:
        printf("> ");
        break;
      case PDEC:
        printf("< ");
        break;
      case LSTART:
        printf("[ ");
        break;
      case LEND:
        printf("] ");
        break;
      default:
        printf("defaultprint, we need some cases");
        break;
      }
      tmp = tmp->next;
    }

  }

}
