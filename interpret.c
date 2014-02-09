/*
 * The interpreter for brainfuck, take a list of instructions
 * and executes them
 */

// return 0 on succes interpretation, and -1 on error
#include "instlist.h"
#include "interpret.h"
#include <stdlib.h>
#include <stdio.h>

struct node* loop2(char* bpointer,  struct loop_* loop);

struct loop_* create_loop(struct node* node);

int interpret(struct instlist* list){

  // allocate memory for the brainfuck environment
  char* bpointer = malloc(2048); // malloc 2 mbyte
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
        //node = loop(bpointer,node);
        node = loop2(bpointer, create_loop(node));
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
struct node* loop2(char* bpointer,  struct loop_* loop){
  struct node* node = loop->start;

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
      if(node != loop->start){
        node = loop2(bpointer, create_loop(node));
      }
      break;
    case LEND:
      //if ( node == loop->end){ // if it is not the end, keep going
        if(*bpointer !=0){
          node = loop->start; // rest back to start of loop code
        }
        else{
          return node; //loop->end; // else return and continiue in interpret
        }
        //      }
      break;
    default:
      printf("default print, we need some cases");
      break;
    }
    //next instruction
    node = node->next;

  }

  // should not return here, since that means there where no LEND
  exit(1);
}

// create a loop, this find the right loop end
struct loop_* create_loop(struct node* node){
  struct loop_* loop = (struct loop_*) malloc(sizeof(struct loop_*));
  loop->start = node;
  // start at -1, since the current node is a LSTART
  // and nest gets incremented
  int nest=-1;

  while(node !=NULL){
    if (node->data == LEND && nest == 0){
      loop->end = node;
      return loop;
    }
    else if(node->data == LEND){
      nest--;
    }
    else if(node->data == LSTART){
      nest++;
    }
    node = node->next;
  }

  printf("could not find nested loop ending ]");
  exit(1);
}
