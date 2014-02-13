/* The jigsaw puzzle solver */
/*     computer science     */
/*            os            */
/*      multi-threaded      */

#include "puzzler.h"

node_t head;
grid_t grid;

int main(int argc, char *argv[])
{
  unsigned short int thread-count;

  if(argc==1){
    thread-count=0;
  }
  else{
    thread-count=(unsigned short int)( atoi(argv[1]) );
  }

  /* INITIALIZE GLOBAL DOUBLY LINKED LIST */
  head.next = NULL;
  head.prev = NULL;
  sem_init(&head.node_lock,0,1); //leave the start of the list unlocked

  /* GLOBAL GRID */
  grid.cells = NULL; //the pointer is null

  /* GET THE PROBLEM FROM STDIN */
  if( (get_input()) == 1 ){
    perror("input error. check the file for proper format");
    exit(1);
  }

  print_list();

  // Solve the problem without using threads
  if (argc==1){
    // Call solver function
    // print grid print_grid();
    // return 0 exit(0);
  }

  // Define thread attributes
  pthread_attr_t atr;
  pthread_attr_init(&atr);
  pthread_attr_setscope( &atr , PTHREAD_SCOPE_SYSTEM );

  //create threads
  
  //print grid && release memory
  print_grid();
  release_memory();

  return 0;
}
  


  

  
   
  
