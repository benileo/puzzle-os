/* The jigsaw puzzle solver */
/*     computer science     */
/*            os            */
/*      multi-threaded      */

#include "puzzler.h"

int
get_input(){

  int i;
  int return_value;
  char buffer[MAXLINELEN];
  cell_t *space;
  char *token;
  char *ssp;

  // Parse the first line. Num rows and columns. 
  fgets( buffer , MAXLINELEN - 1 , stdin );
  buffer[MAXLINELEN] = '\0';
  sscanf(buffer, "%d %d", &(grid.numcols) , &(grid.numrows) );

  // Allocate space for all the cells in the grid
  space = (cell_t *) malloc( (grid.numrows)*(grid.numcols) * sizeof( cell_t ) ) ;

  // Allocate space for some pointers that will define the rows in the grid
  // Return a pointer to that space 
  grid.cells = (cell_t **)malloc( (grid.numcols) * sizeof( cell_t *) );
  
  if( (space != NULL) && (grid.cells != NULL) ){

    // You have an array of numcol pointers
    // For each column you have the address of the first element of the column is the i*number of rows
    // this is a weird way to do it, up and down, I would have done it side to side. 
    for(i = 0; i < (grid.numcols) ; i++ ){
      grid.cells[i] = space + i*(grid.numrows);
    }
    
    for(i = 0; i < ((grid.numcols)  * (grid.numrows)) ; i++){
      space[i].n = NO_PIECE_INDEX;
      space[i].w = NO_PIECE_INDEX;
      space[i].s= NO_PIECE_INDEX;
      space[i].e = NO_PIECE_INDEX;
      space[i].name = (char *)malloc( MAXLINELEN * sizeof(char) );
      strcpy( space[i].name , "" ); 
      sem_init( &space[i].cell_lock , 0 , 1 ); //Leave all cells unlocked. 
    }

    // Fill in the top row of the grid
    fgets(buffer, MAXLINELEN, stdin);
    ssp = NULL;
    token = strtok_r(buffer, " \n", &ssp);
    for(i = 0; i < grid.numcols; i++){
      grid.cells[i][0].n = atoi(strtok_r( NULL, " \n", &ssp));
    }
    
    // Fill in the bottom of the grid
    fgets(buffer, MAXLINELEN, stdin );
    ssp = NULL;
    token = strtok_r(buffer, " \n", &ssp);
    for (i = 0; i < grid.numcols; i++ ){
      grid.cells[i][grid.numrows-1].s = atoi( strtok_r(NULL, " \n", &ssp ) );
    }
    
    // Fill in the left side
    fgets(buffer, MAXLINELEN, stdin );
    ssp = NULL;
    token = strtok_r(buffer, " \n", &ssp);
    for (i = 0; i < grid.numrows; i++ ){
      grid.cells[0][i].w = atoi( strtok_r(NULL, " \n", &ssp ) );
    }
    
    // Fill in the right side
    fgets(buffer, MAXLINELEN, stdin );
    buffer[MAXLINELEN] = '\0';
    ssp = NULL;
    token = strtok_r(buffer, " \n", &ssp);
    for (i = 0; i< grid.numrows; i++){
      grid.cells[grid.numcols - 1][i].e = atoi( strtok_r(NULL, " \n", &ssp ) );
    }
    
    /* Create Doubly Linked List to hold the pieces */

    for(i = 0; i < (grid.numcols * grid.numrows); i++){
      fgets(buffer, MAXLINELEN - 1, stdin);
      buffer[MAXLINELEN] = '\0';
      
      node_t *new = (node_t *)malloc(sizeof(node_t));
      new->name = (char *)malloc(sizeof(char)*MAXLINELEN);
      
      if ( sscanf(buffer, "%s %d %d %d %d", (new->name), &(new->n), &(new->e), &(new->s), &(new->w)) != 5 ){
       perror("sscanf error\n");
       return_value = 1;
     }
      /* INITIALIZE SEMAPHORE FOR THE NODE */
     sem_init( &new->node_lock, 0, 1); 

     new->prev = &head;  
     if(head.next == NULL){
       head.next = new;
       new->next = NULL;
     }
     else{
       (head.next)->prev = new;
       new->next = head.next;
       head.next = new;
     }
   }
   return_value=0;
 }
 else{
  printf("memory allocation error\n");
  return_value=1;
}
return return_value;
}

void
print_grid(void) {
  int i, j;
  
  for (j = 0; j < grid.numrows; j++){
    for(i=0; i < grid.numcols; i++){
      if ( strcmp( (char *)(grid.cells[i][j].name) , "") == 0){
       printf(". ");
     }
     else{ 
       printf("%s ", grid.cells[i][j].name);
     }
   }
   printf("\n");
 }
}

void
print_list(){
  node_t *runner = &head;

  printf("LIST:\n");
  if ( runner == NULL ) printf("List is Empty\n");
  while (runner != NULL){


    printf("%s\tsem-value:" , runner->name);
    int val, *p;
    p = &val;
    sem_getvalue( &(runner->node_lock), p);
    printf("%d\n",val);

    runner = runner->next;
  }
}


void
release_memory(){ 
  free( grid.cells[0] );
  free( grid.cells );
  grid.cells = NULL;
}
