/* The jigsaw puzzle solver */
/*     computer science     */
/*            os            */
/*      multi-threaded      */

#include "puzzler.h"

#define DEBUG

int main(int argc, char *argv[])
{
  unsigned short int thread_count;

  if(argc==1){
    thread_count=0;
  }
  else{
    thread_count=(unsigned short int)( atoi(argv[1]) );
  }

#ifdef DEGUG
  printf("Number of threads to solve the problem: %d\n" , thread_count);
#endif

  /* INITIALIZE GLOBAL DOUBLY LINKED LIST */
  head.next = NULL;
  head.prev = NULL;
  sem_init(&head.node_lock,0,1); //leave the start of the list unlocked

  /* GLOBAL GRID */
  grid.cells = NULL; //the pointer is null, not too sure on this one...

  /* GET THE PROBLEM FROM STDIN */
  if( ( get_input() ) == 1 ){
    perror("input error. check the file for proper format");
    exit(1);
  }

#ifdef DEGUG
  print_list();
  print_grid();
#endif
  

  // Solve the problem without using threads
  if (thread_count == 0){
    //solve
  }

  // Define thread attributes
  pthread_attr_t atr;
  pthread_attr_init(&atr);
  pthread_attr_setscope( &atr , PTHREAD_SCOPE_SYSTEM );

  //create threads
  
  //print grid && release memory
  //print_grid();
  //release_memory();

  return 0;
}
  


  

  
   
  
