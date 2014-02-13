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
  int ROWS, COLUMNS;

  fgets(buffer, MAXLINELEN - 1, stdin);
  buffer[MAXLINELEN] = '\0';
  sscanf(buffer, "%d %d", &COLUMNS, &ROWS);
  
  grid.numcols = COLUMNS;
  grid.numrows = ROWS;

  space = (cell_t *) malloc( (ROWS)*(COLUMNS) * sizeof( cell_t ) ) ;
  grid.cells = (cell_t **)malloc( (COLUMNS) * sizeof( cell_t *) );
  
  if( (space != NULL) && (grid.cells != NULL) ){
    
    for(i = 0; i < (COLUMNS) ; i++ ){
      grid.cells[i] = space + i*(ROWS);
    }
    
    for(i = 0; i < ((COLUMNS)  * (ROWS)) ; i++){
      space[i].north = NO_PIECE_INDEX;
      space[i].west = NO_PIECE_INDEX;
      space[i].south= NO_PIECE_INDEX;
      space[i].east = NO_PIECE_INDEX;
      strcpy( space[i].name , "" ); 
      sem_init( &space[i].cell_lock , 0 , 1 );
    }

    
    fgets(buffer, MAXLINELEN, stdin);
    ssp = NULL;
    token = strtok_r(buffer, " \n", &ssp);
    for(i = 0; i < COLUMNS; i++){
      grid.cells[i][0].north = atoi(strtok_r( NULL, " \n", &ssp));
    }
    
    fgets(buffer, MAXLINELEN, stdin );
    ssp = NULL;
    token = strtok_r(buffer, " \n", &ssp);
    for (i = 0; i < COLUMNS; i++ ){
      grid.cells[i][ROWS-1].south = atoi( strtok_r(NULL, " \n", &ssp ) );
    }
    
   
    fgets(buffer, MAXLINELEN, stdin );
    ssp = NULL;
    token = strtok_r(buffer, " \n", &ssp);
    for (i = 0; i < ROWS; i++ ){
      grid.cells[0][i].west = atoi( strtok_r(NULL, " \n", &ssp ) );
    }
    
    fgets(buffer, MAXLINELEN, stdin );
    buffer[MAXLINELEN] = '\0';
    ssp = NULL;
    token = strtok_r(buffer, " \n", &ssp);
    for (i = 0; i< ROWS; i++){
      grid.cells[COLUMNS - 1][i].east = atoi( strtok_r(NULL, " \n", &ssp ) );
    }
    
    /* Create Doubly Linked List to hold the pieces */

    for(i = 0; i < (COLUMNS * ROWS); i++){
      fgets(buffer, MAXLINELEN - 1, stdin);
      buffer[MAXLINELEN] = '\0';
      
      node_t *new = (node_t *)malloc(sizeof(node_t));
      
      if ( sscanf(buffer, "%s %d %d %d %d", &(new->name), &(new->north), &(new->east), &(new->south), &(new->west)) != 5 ){
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
  }
  else{
    printf("memory allocation error\n");
  }
  return_value = 0;

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
  node_t *runner = head.next;
  printf("LIST:\n");
  while (runner != NULL){
    printf("%s\n" , runner->name);
    runner = runner->next;
  }
}


void
release_memory(){ 
  free( grid.cells[0] );
  free( grid.cells );
  grid.cells = NULL;
}
