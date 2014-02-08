/*
 * main file
 * brain fuck interpreter
 */

#include "instlist.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){

  struct instlist* list = list_init();

  FILE *file;

  if(argc != 2){
    printf("Usage: %s file.exe\n", argv[0]);
    exit(1);
  }
  file = fopen(argv[1],"r");

  if(file == NULL){
    printf("File == NULL");
    exit(1);
  }
  else{
    // everything is good, we can parse the program, then print the
    // instruction list
    parse_prog(file,list);
    list_print(list);
  }

  fclose(file);

  free_list(list);

  return 0;
}
