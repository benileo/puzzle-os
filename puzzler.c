/* The jigsaw puzzle solver */
/*     computer science     */
/*            os            */
/*      multi-threaded      */

#include "puzzler.h"

#define DEBUG

void * puzzle_solver( direction dir );

int main(int argc, char *argv[])
{
  unsigned short int thread_count;

  if(argc==1){
    thread_count=0;
  }
  else{
    thread_count=(unsigned short int)( atoi(argv[1]) );
  }

#ifdef DEBUG
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

#ifdef DEBUG
  print_list();
  print_grid();
  printf("N: %d\nE: %d\n S: %d\n W: %d\n", grid.cells[0][0].n, grid.cells[0][0].e, grid.cells[0][0].s, grid.cells[0][0].w);
#endif
  

  // Solve the problem without using threads
  if (thread_count == 0)
  {
    //direction dir = SE;
    //puzzle_solver( (void*)dir );
  }
  else
  {
    pthread_attr_t atr;
    pthread_attr_init(&atr);
    pthread_attr_setscope( &atr , PTHREAD_SCOPE_SYSTEM );
    pthread_t tpool[thread_count];



  }


  //print_grid();
  //release_memory();

  return 0;
}

  
void * puzzle_solver(direction dir)
{

    // Set the starting point for solving.

    // this depends on the direction that the thread will be solving. 

    int s_row, s_column;

    switch(dir)
    {
      case SE:
        s_row=0;s_column=0;
        break;
      case SW:
        s_row=0;s_column=grid.numcols-1;
        break;
      case NW:
        s_row=grid.numrows-1;s_column=grid.numcols-1;
        break;
      case NE:
        s_row=grid.numrows-1;s_column=0;
        break;
    }


    while
      (

        ( (dir == SE) && )
        ()
        ()
        ()

        )
    {
      
    }
}

  

  
   
  
