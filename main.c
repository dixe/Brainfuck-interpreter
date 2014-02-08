/*
 * main file
 * brain fuck interpreter
 */

#include "instlist.h"
#include <stdlib.h>

int  main(){

  struct instlist* list = list_init();
  struct node* node = NULL;

  node = list_malloc_node(COMMA);
  add_node(list, node);
  node = list_malloc_node(COMMA);
  add_node(list, node);
  list_print(list);



  return 0;
}
