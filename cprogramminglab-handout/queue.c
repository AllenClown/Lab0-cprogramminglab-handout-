/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q != NULL){
      q->head = q->tail = NULL;
      q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q != NULL)
    {
      list_ele_t *i = q->head;
      while(i)
      {
        list_ele_t *tmp = i;
        i = i->next;
        free(tmp->value);
        free(tmp);
      }
      free(q);
    }

}
/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{

    list_ele_t *newh;
    if(q == NULL) return false;
    /* What should you do if the q is NULL? */
    newh = (list_ele_t *)malloc(sizeof(list_ele_t));
    if(newh == NULL) return false;
    /* Don't forget to allocate space for the string and copy it */
    newh->value = (char *)malloc((strlen(s) + 1) * sizeof(char));
    if(newh->value == NULL) return false;
    strcpy(newh->value, s);  
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if(q->tail == NULL) q->tail = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
  list_ele_t *nt;
  if(q==NULL) return false;
  nt = malloc(sizeof(list_ele_t));
  if(nt == NULL) return false;
  nt->value = malloc((strlen(s) + 1) * sizeof(char));
  if(nt->value == NULL) return false;
  strcpy(nt->value, s);
  nt->next = NULL;
  if(q->tail != NULL)
    q->tail->next = nt;
  q->tail = nt;
  if(q->head == NULL) q->head = nt;
  q->size++;
  
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if(q == NULL || q->size == 0) 
      return false;
    list_ele_t *e = q->head;
    q->head = q->head->next;
    if(--q->size == 0) q->tail = NULL;
    char *p = e->value;
    int i;
    for( i = 0; i < bufsize-1 && p[i] != '\0'; i++)
      sp[i] = p[i];
    sp[i] = '\0'; 
    free(e->value);
    free(e);  
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
  if(q==NULL || q->size == 0) return;
  list_ele_t *p = q->tail;
  list_ele_t *cur;
  while(q->head != p){
    cur = q->head;
    q->head = q->head->next;
    q->tail->next = cur;
    cur->next = NULL;
    q->tail = cur;
  } 
}
