/**
 * Prompts user to enter a set of random integers. When 'Q' is entered,
 * display the integers in ascending order.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct node {
  int value;
  struct node *next;
} node_t;

/**
 * Initializes when head is NULL and assigns initial value
 *
 */
void init(node_t **headp, int value) {
  node_t *newp;
  newp = malloc(sizeof(node_t));
  newp->value = value;
  newp->next = NULL;

  if (*headp == NULL) {
    *headp = newp; 
  }
}

/**
 * Inserts a node into a sorted list
 */

void insert(node_t **headp, int value) {

  node_t *currp;
  node_t *prevp = NULL;

  // Handle empty list by initializing it

  if (*headp == NULL) {
    init(headp, value);
    return;
  }

  node_t *newp;
  newp = malloc(sizeof(node_t));
  newp->value = value;
  newp->next = NULL;

  // Find where it goes

  for (currp = *headp; currp; currp = currp->next) {
    if (currp->value >= value) {
      if (prevp == NULL) { // insert at beginning of list
        *headp = newp;
        newp->next = currp;
        break;
      } else { // insert between two existing nodes
        prevp->next = newp;
        newp->next = currp;
        break;
      }
    } else if (currp->next == NULL) { // append to end of list
      currp->next = newp;
      break;
    }
    prevp = currp;
  }
}

int main(int argc, char **argv) {

  node_t *headp = NULL;
  node_t *currp;

  char inbuf[80];
  memset(inbuf, '\0', sizeof(inbuf));
  int value = 0;

  // Prompt for list of unsorted integers

  while (*inbuf != 'Q') {
    printf("Enter a number or 'Q' to quit: ");
    // Get input from console
    fgets(inbuf, sizeof(inbuf),stdin);

    char *p = strchr(inbuf, '\n');
    *p = '\0'; // Clear out the trailing newline
    if (*inbuf == 'Q') 
      break;

    if (sscanf(inbuf, "%d", &value) > 0)
      // Process valid integer
      insert(&headp, value);
    else
      // Ignore any input not an integer
      printf("** ignored input\n");
  }

  // Done with input, now display the sorted list

  for (currp = headp; currp; currp = currp->next) {
    printf("%d\n", currp->value);
  }
}
