#ifndef KERNEL_QUEUE_UMBC_H
#define KERNEL_QUEUE_UMBC_H

typedef struct qnode_421 {
  struct qnode_421* next;
  int id;
} qnode_421_t;

typedef struct kqueue_421 {
  qnode_421_t* head;
  qnode_421_t* tail;
  int num_nodes;
} kqueue_421_t;

/**
 * You have been given the following function prototypes:
 *  1. get_head_node: gets the head of the queue.
 *  2. get_tail_node: gets the tail of the queue.
 *  3. dequeue: removes the head Node from the queue.
 *  4. enqueue: adds a Node to the end of the queue.
 *  5. queue_init: initializes the queue if not already.
 *  6. queue_free: cleans up any memory associated with the queue.
 */

qnode_421_t*  get_head_node(void);
qnode_421_t*  get_tail_node(void);
qnode_421_t*  dequeue(void);
void          enqueue(qnode_421_t* node);
long          queue_init(void);
long          queue_free(void);

#endif
