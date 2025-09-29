#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include "421queue.h"

kqueue_421_t* queue = NULL;


qnode_421_t* get_head_node(void) {
	if (num_nodes < 1){
  		return NULL;
	} else {
		return head;
	}
}

qnode_421_t* get_tail_node(void) {
	if (num_nodes < 1){
		return NULL;
	} else {
		return tail;
	}
}

qnode_421_t* dequeue(void) {
	if (num_nodes < 1){
		return NULL;
	} else if (num_nodes == 1){
		qnode_421_t* temp = head;
		head = NULL;
		tail = NULL;
		num_nodes--;
		return temp;
	} else {
		head = head->next;
			if (num_nodes == 2){
				tail = head;
			}
		num_nodes--;
		return temp;
	}
	return NULL;
}

void enqueue(qnode_421_t* node) {
  return;
}

long queue_init(void) {
  return -1;
}

long queue_free(void) {
  return -1;
}

// kernel-space initializer.
SYSCALL_DEFINE0(kern_queue_init) {
  return -1;
}

// kernel-space free-er.
SYSCALL_DEFINE0(kern_queue_free) {
  return -1;
}

/**
 * kernel-space function to dequeue a Node.
 * HINT:  remember, your user-space program will need the value of the node.
 *        how can you get the data from kernel-space to user-space, i wonder?
 * RETURN VALUE: should be 0 on success, 1 otherwise.
 */
SYSCALL_DEFINE1(kern_dequeue, void __user*, dest) {
  return -1;
}

/**
 * kernel-space function to enqueue a node.
 * HINT:  you will have to get the data from user-space into kernel space.
 *        how can you do that?
 * RETURN VALUE: should be 0 on success, 1 otherwise.
 */
SYSCALL_DEFINE1(kern_enqueue, void __user*, node) {
  return -1;
}
