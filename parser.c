#include <stdio.h>
#include "parser.h"

struct instlist parse(FILE *fp){
  struct instlist list = list_init();
  struct node* node = NULL;
  char c;

  while((c=fgetc(fp)) != EOF){
      //allocate space for new pointer

      switch (c){
      case '+':
        node = list_malloc_node(VINC);
        add_node(list,node);
        break;
      case '-':
        node = list_malloc_node(VDEC);
        add_node(list,node);
        break;
      case '>':
        node = list_malloc_node(PINC);
        add_node(list,node);
        break;
      case '<':
        node = list_malloc_node(PDEC);
        add_node(list,node);
        break;
      case '.':
        node = list_malloc_node(DOT);
        add_node(list,node);
        break;
      case ',':
        node = list_malloc_node(COMMA);
        add_node(list,node);
        break;
      case '[.':
        node = list_malloc_node(LSTART);
        add_node(list,node);
        break;
      case ']':
        node = list_malloc_node(LEND);
        add_node(list,node);
        break;
      default:
        // Error not a valid brainfuck command
        return -1;
        break;
      }

  }

  return list;

}
