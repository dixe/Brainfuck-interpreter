/*
 * The interpreter for brainfuck, take a list of instructions
 * and executes them
 */

// return 0 on succes interpretation, and -1 on error
#include "instlist.h"
#include "interpret.h"
#include <stdlib.h>
#include <stdio.h>

char* bpointer;

struct node* loop2( struct loop_* loop, const char* start, int debug);

struct loop_* create_loop(struct node* node);

int interpret(struct instlist* list,int debug){

  // allocate memory for the brainfuck environment
  bpointer = malloc(2048); // malloc 2 mbyte
  const char* start = bpointer;
  struct node* node = list->head; // init node to head
  struct loop_* loop = NULL;
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
   * loop where interpretation happens
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
      if(*bpointer !=0){
        node = loop2( create_loop(node), start,debug);
      }
      else{ // create a loop and set next node to the end of the loop
        loop = create_loop(node);
        node = loop->end;
      }
      break;
    case LEND:
      //printf("We hane a LEND in interpreter");
      break;
    case DEBUG:
      if(debug){
        printf("Pointer: %i, value at pointer %i \n", bpointer-start, *bpointer);
        getchar();
        fflush(stdin);
      }
      break;
    default:
      printf("default print, we need some cases, in interpreter");
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
struct node* loop2( struct loop_* loop, const char* start,int debug){

  struct node* node = loop->start;
  struct loop_* tmp_loop = NULL;

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
      if(*bpointer == 0 && node == loop->start){ // loop should not run
        return loop->end; // return end of loop to continiue interpretation
      }
      else if(node != loop->start && *bpointer !=0){ // if we encounter a new loop run that
        node = loop2(create_loop(node), start, debug);
      }
      else if (node!=loop->start){ // create a loop and set next node to the end of the loop
        tmp_loop = create_loop(node);
        node = tmp_loop->end;
      }
      break;
    case LEND:
      if ( node == loop->end){ // if it is not the end, keep going
        if(*bpointer !=0){
          node = loop->start; // rest back to start of loop code
        }
        else{
          return node; //loop->end; // else return and continiue interpret
        }
      }
      break;
    case DEBUG:
      if(debug){
        printf("Pointer: %i, value at pointer %i \n",bpointer - start, *bpointer);
        getchar();
        fflush(stdin);
      }
      break;
    default:
      printf("default print, we need some cases, in loop");
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
