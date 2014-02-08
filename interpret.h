/*
 * The interpreter for brainfuck, take a list of instructions
 * and executes them
 */

#ifndef INTERPRET_H
#define  INTERPRET_H

// return 0 on succes interpretation, and -1 on error
int interpret(struct instlist* list);

#endif /* INTERPRET_H */
