/* The jigsaw puzzle solver */
/*     computer science     */
/*            os            */
/*      multi-threaded      */

#include "puzzler.h"

#define DEBUG

void * puzzle_solver( direction dir );
void find_piece(int row, int column);

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

  /* INITIALIZE THE FIRST NODE IN THE LIST */
  head.next = NULL;
  head.prev = NULL;
  head.n=-1;head.e=-1;head.w=-1;head.s=-1;
  sem_init(&head.node_lock,0,1);

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
      puzzle_solver( SE );
  }
  else
  {
    pthread_attr_t atr;
    pthread_attr_init(&atr);
    pthread_attr_setscope( &atr , PTHREAD_SCOPE_SYSTEM );
    pthread_t tpool[thread_count];
  }


  print_grid();
  release_memory();

  return 0;
}

void * puzzle_solver(direction dir)
{
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
     ( (dir == SE) && (s_row < grid.numrows) ) ||
     ( (dir == SW) && (s_row < grid.numrows) ) ||
     ( (dir == NW) && (s_row >= 0) ) ||
     ( (dir == NE) && (s_row >= 0) ) 
     )
  {

    //if you can get the lock and the piece is not found
    if ( 
     ( sem_trywait( &(grid.cells[s_column][s_row].cell_lock) ) == 0 ) &&
     ( grid.cells[s_column][s_row].n == -1 || grid.cells[s_column][s_row].e == -1 || 
       grid.cells[s_column][s_row].w == -1 || grid.cells[s_column][s_row].s == -1 )
     )
    {
      find_piece( s_row , s_column );
      sem_post(&(grid.cells[s_column][s_row].cell_lock));
      switch(dir)
      {
        case SE:
          if(s_column == grid.numcols-1){
            s_row++;s_column=0;
          }else{
            s_column++;
          }
        break;

        case SW:
          if(s_column == 0){
            s_row++;s_column=grid.numcols-1;
          }else{
            s_column--;
          }
          break;

        case NW:
          if(s_column == 0){
            s_row--;s_column=grid.numcols-1;
          }else{
            s_column--;
          }
          break;

        case NE:
          if(s_column == grid.numcols-1){
            s_row--;s_column=0;
          }else{
            s_column++;
          }
          break;
      }
    }
    else
    {
      switch(dir)
      {
        case SE:
        s_row++;s_column=0;
        break;
        case SW:
        s_row++;s_column=grid.numcols-1;
        break;
        case NW:
        s_row--;s_column=grid.numcols-1;
        break;
        case NE:
        s_row--;s_column=0;
        break;
      }
    }
  }  


  return NULL;
}


void find_piece(int row, int column)
{
  int found=0;
  node_t *runner=head.next;

  //Get the lock to the head
  sem_wait( &(head.node_lock) );

  //find the piece 
  while( !found ) 
  {

#ifdef DEBUG
    if (runner == NULL) printf("unable to find piece...about to seg-fault\n");
#endif

    sem_wait( &(runner->node_lock));
    if( 
      (grid.cells[column][row].n == runner->n && grid.cells[column][row].e == runner->e) ||
      (grid.cells[column][row].n == runner->n && grid.cells[column][row].w == runner->w) ||
      (grid.cells[column][row].s == runner->s && grid.cells[column][row].e == runner->e) ||
      (grid.cells[column][row].s == runner->s && grid.cells[column][row].w == runner->w) ||
      (column > 0 && row > 0 && grid.cells[column][row-1].s == runner->n && grid.cells[column-1][row].e == runner->w) ||
      (column < grid.numcols-1 && row > 0 && grid.cells[column][row-1].s == runner->n && grid.cells[column+1][row].w == runner->e) ||
      (column < grid.numcols-1 && row < grid.numrows-1  && grid.cells[column][row+1].n == runner->s && grid.cells[column+1][row].w == runner->e) ||
      (column > 0 && row < grid.numrows-1 && grid.cells[column][row+1].n == runner->s && grid.cells[column-1][row].e == runner->w) ||
      (column > 0 && row==0 && grid.cells[column][row].n == runner->n && grid.cells[column-1][row].e == runner->w ) ||
      (column == 0 && row!=0 && grid.cells[column][row-1].s == runner->n && grid.cells[column][row].w == runner->w) 
      )
    {
      found=1;
    }
    else{
      sem_post( &(runner->prev->node_lock) );
      runner=runner->next;
    }
  }

  // Fill in the piece to the grid
  grid.cells[column][row].n = runner->n;
  grid.cells[column][row].w = runner->w;
  grid.cells[column][row].e = runner->e;
  grid.cells[column][row].s = runner->s;
  strcpy( grid.cells[column][row].name, runner->name );

#ifdef DEBUG
  printf("%s\n", runner->name);
#endif

  //Unlink and free the item from the list
  runner->prev->next = runner->next;
  sem_post( &(runner->prev->node_lock) );
  free(runner);
}



