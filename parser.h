/*
 * this is a simple parse for brainfuck
 */


#ifndef PARSER_H
#define PARSER_H

#include "instlist.h"
#include <stdio.h>

// takes a file pointer and return a inslist
struct instlist* parse_prog(FILE *fp, struct instlist* list);

#endif /*PARSER_H*/
