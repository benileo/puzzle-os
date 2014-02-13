
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

  int n,s,e,w;
  char *name;
  struct _node_ *next, *prev;
  sem_t node_lock;

}node_t;

//puzzle piece data structure
typedef struct
{
  int n,s,e,w;
  char *name;
  sem_t cell_lock;

}cell_t;

//grid 
typedef struct
{
  cell_t **cells;
  int numcols;
  int numrows;

}grid_t;

//Globals
node_t head;
grid_t grid;

#endif
