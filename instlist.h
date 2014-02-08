
/*
 * the different types of instructions there are
 */
typedef enum {COMMA, DOT, PINC, PDEC, VINC, VDEC, LSTART, LEND} instruction;

// linked list of instructions
struct node {
  instruction data;
  struct node* next;
};


struct instlist{
  struct node* head;
};

// returns length of list after appeding
int add_node( struct instlist* list, struct node* node);

//init
struct instlist* list_init();

//free used memory
void free_list(struct instlist* list);

// create a new node
struct node* list_malloc_node(instruction data);


//print the list
void list_print(struct instlist* list);
