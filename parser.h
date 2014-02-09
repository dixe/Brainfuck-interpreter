/*
 * this is a simple parse for brainfuck
 */


#ifndef PARSER_H
#define PARSER_H

#include "instlist.h"
#include <stdio.h>

// takes a file pointer and a instruction list pointer
void parse_prog(FILE *fp, struct instlist* list);

#endif /*PARSER_H*/
