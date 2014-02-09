/*
 * The interpreter for brainfuck, take a list of instructions
 * and executes them
 */

#ifndef INTERPRET_H
#define  INTERPRET_H

#include "parser.h" // need struct node
#include "instlist.h"

struct loop_{
  struct node* end; // the node that end this loop
  struct node* start; // start of loop
};

// return 0 on succes interpretation, and -1 on error
int interpret(struct instlist* list);



#endif /* INTERPRET_H */
