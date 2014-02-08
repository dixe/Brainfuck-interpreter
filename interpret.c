/*
 * The interpreter for brainfuck, take a list of instructions
 * and executes them
 */

// return 0 on succes interpretation, and -1 on error
#include "instlist.h"
#include <stdlib.h>
#include <stdio.h>

int interpret(struct instlist* list){

  // allocate memory for the brainfuck environment
  char* bpointer = malloc(2048); // malloc 2 mbyte
  const char* start = bpointer; // used to make use we stay in our memory space
  struct node* node = list->head; // init node to head

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
        // when useing getchar(), the enter is still in buffer
        // if we did not do this, the next , would give user a change to input something
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
        printf("[ ");
        break;
      case LEND:
        printf("] ");
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
void loop(char* bpointer, char* lpointer){

}


// return a pointer to the end of the loop
char* find_loop_end() {
  return NULL;

}
