/*
 * this is a simple parse for brainfuck
 */


#ifndef PARSER_H
#define PARSER_H

#include "instlist.h"

// takes a file pointer and return a inslist
struct inslist* program parse(FILE *fp);

#endif /*PARSER_H*/
