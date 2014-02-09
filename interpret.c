/*
 * The interpreter for brainfuck, take a list of instructions
 * and executes them
 */

// return 0 on succes interpretation, and -1 on error
#include "instlist.h"
#include <stdlib.h>
#include <stdio.h>

struct node* loop(char* bpointer,  struct node* tmp_node);

char* find_loop_end(char* bpointer_, struct node* tmp_node);

int interpret(struct instlist* list){

  // allocate memory for the brainfuck environment
  char* bpointer = malloc(2048); // malloc 2 mbyte
  const char* start = bpointer; // used to make use we stay in our memory space
  struct node* node = list->head; // init node to head

  //init to alle to 0
  for(int i = 0; i<2048;i++){
    bpointer[i] = 0;
  }

  if(node == NULL){
    printf("empty file, interpretation ended");
    free(bpointer);
    return 0;
  }

  /*
   * loop where interpretations happens
   */
  while(node != NULL){
    switch(node->data){
      case COMMA:
        *bpointer = getchar();
        /* when useing getchar(), the enter is still in buffer
         * if we did not do this, the next , would give
         * the user a change to input something
         */
        fflush(stdin);
        break;
      case VINC:
        *bpointer += 1;
        break;
      case DOT:
        putchar(*bpointer);
        break;
      case VDEC:
        *bpointer -= 1;
        break;
      case PINC:
        bpointer++;
        break;
      case PDEC:
        bpointer--;
        break;
      case LSTART:
        find_loop_end(bpointer, node);
        node =loop(bpointer,node);
        break;
      case LEND:
        //DO nothing gets handles in loop() function
        break;
      default:
        printf("default print, we need some cases");
        break;
      }

    //next instruction
    node = node->next;

  }

  // free the memory used by brainfuck
  free(bpointer);
  return 0;

}


//function to handle loop
// takes the global brainfcuk pointer and a new loop pointer
// loop pointer points to end of loop
struct node* loop(char* bpointer,  struct node* tmp_node ){
  struct node* node = tmp_node; // save the node used in interpret

  while(node != NULL){
    switch(node->data){
      case COMMA:
        *bpointer = getchar();
        /* when useing getchar(), the enter is still in buffer
         * if we did not do this, the next , would give
         * the user a change to input something
         */
        fflush(stdin);
        break;
      case VINC:
        *bpointer += 1;
        break;
      case DOT:
        putchar(*bpointer);
        break;
      case VDEC:
        *bpointer -= 1;
        break;
      case PINC:
        bpointer++;
        break;
      case PDEC:
        bpointer--;
        break;
      case LSTART:
        find_loop_end(bpointer, node);
        //        loop(bpointer);
        break;
      case LEND:
        if(*bpointer !=0){
          node = tmp_node; // rest back to start of loop code
        }
        else{
          return node; // else return and continiue in interpret
        }
        break;

      default:
        printf("default print, we need some cases");
        break;
      }

    //next instruction
    node = node->next;

  }


}


// return a pointer to the end of the loop
char* find_loop_end(char* bpointer, struct node* tmp_node) {
  struct node* node = tmp_node; // we don't want do move the node pointer used in interpret
  char* lp = bpointer; //set return pointer to current bpointer
  int done = 0;
  int nest = 0; // keep track of nested loops


  while(node->next != NULL && !done){
    if( node->data == LEND ){
      if(nest == 0){
        done = 1; // we found an loop end
      }
      else{
        // we found a new loop end
        nest--;
      }
    }
    else{
      if(node->data == LSTART){
        nest++;
      }
      node = node->next;
      //increment the return pointer to next address
      lp++;
    }
  }

  return lp;

}
