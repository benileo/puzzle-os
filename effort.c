/* The jigsaw puzzle solver */
/*     computer science     */
/*            os            */
/*      multi-threaded      */

#include "puzzle.h"

int main(int argc, char *argv[])
{
 
  /* INITIALIZE GLOBAL DOUBLY LINKED LIST */
  head.next = NULL;
  head.prev = NULL;
  sem_init( &head.node_lock, 0, 1);

  /* GLOBAL GRID */
  grid.cells = NULL;

  /* GET THE PROBLEM FROM STDIN */
  if( (get_input()) == 1 ) return 1;

  // Solve the problem without using threads
  if (argc==1){
    // Call solver function
    // print grid print_grid();
    // return 0 exit(0);
  }

  // Create thread pool
  pthread_t thread_pool[atoi(argv[1])];

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
  


  

  
   
  
