
#ifndef PUZZLER
#define PUZZLER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define LABEL_LEN (12)
#define MAXLINELEN (8095)
#define NO_PIECE_INDEX (-1)


// Linked list node Data Structure
typedef struct _node_
{
  int north;
  int south;
  int east;
  int west;
  char name[LABEL_LEN + 1];
  struct _node_ *next, *prev;
  sem_t node_lock;
}node_t;

//puzzle piece data structure
typedef struct
{
  int north;
  int west;
  int east;
  int south;
  char name[LABEL_LEN + 1];
  sem_t cell_lock;
}cell_t;

//grid 
typedef struct
{
  cell_t **cells;
  int numcols;
  int numrows;
}grid_t;


// linked list head
node_t head;

// the grid
grid_t grid;	

#endif
