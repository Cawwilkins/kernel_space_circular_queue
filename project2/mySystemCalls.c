#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include "421queue.h"

kqueue_421_t* queue = NULL;


qnode_421_t* get_head_node(void) {
	if (queue->num_nodes < 1){
  		return NULL;
	} else {
		return queue->head;
	}
}

qnode_421_t* get_tail_node(void) {
	if (queue->num_nodes < 1){
		return NULL;
	} else {
		return queue->tail;
	}
}

qnode_421_t* dequeue(void) {
	qnode_421_t* temp = queue->head;
	if (queue->num_nodes == 1) {
		queue->head = NULL;
		queue->tail = NULL;
		queue->num_nodes--;
		return temp;
	} else {
		queue->head = queue->head->next;
			if (queue->num_nodes == 2){
				queue->tail = queue->head;
			}
		queue->num_nodes--;
		return temp;
	}
	return NULL;
}

void enqueue(qnode_421_t* node) {
	if (queue->num_nodes < 1) {
		queue->head = node;
		queue->tail = node;
		queue->num_nodes++;
		return;
	} else if (queue->num_nodes == 1) {
		queue->head->next = node;
		queue->tail = node;
		queue->num_nodes++;
		return;
	} else {
		queue->tail->next = node;
		queue->tail = node;
		queue->num_nodes++;
  		return;
	}
	return;
}

long queue_init(void) {
	if (queue != NULL) {
		if (queue->head || queue->tail || queue->num_nodes > 0){
			return 1;
		}
	} else {
		queue = kmalloc(sizeof(kqueue_421_t), GFP_KERNEL);
		queue->head = NULL;
		queue->tail = NULL;
		queue->num_nodes = 0;
		return 0;
	}
	return 1;
}

long queue_free(void) {
	if (queue == NULL){
		return 1;
	}
	while (queue->head != NULL){
		kfree(dequeue());
	}
	queue->head = NULL;
	queue->tail = NULL;
	queue->num_nodes = 0;
	kfree(queue);
	queue = NULL;
	return 0;
}

// kernel-space initializer.
SYSCALL_DEFINE0(kern_queue_init) {
	int result = queue_init();
	return result;
}

// kernel-space free-er.
SYSCALL_DEFINE0(kern_queue_free) {
	int result = queue_free();
	return result;
}

/**
 * kernel-space function to dequeue a Node.
 * HINT:  remember, your user-space program will need the value of the node.
 *        how can you get the data from kernel-space to user-space, i wonder?
 * RETURN VALUE: should be 0 on success, 1 otherwise.
 */
SYSCALL_DEFINE1(kern_dequeue, void __user*, dest) {
	if (queue == NULL){
		return -EPERM;
	} else if (queue->num_nodes < 1 || queue->head == NULL){
		return -ENOENT;
	}

	qnode_421_t* topOfQueue = queue->head;

	if (copy_to_user(dest, topOfQueue, sizeof(qnode_421_t))) {
		return -ENXIO;
	}
	dequeue();
	kfree(topOfQueue);
	return 0;
}

/**
 * kernel-space function to enqueue a node.
 * HINT:  you will have to get the data from user-space into kernel space.
 *        how can you do that?
 * RETURN VALUE: should be 0 on success, 1 otherwise.
 */
SYSCALL_DEFINE1(kern_enqueue, void __user*, node) {
	qnode_421_t* newNode = kmalloc(sizeof(qnode_421_t), GFP_KERNEL);
	if (!newNode){
		return -ENOMEM;
	}
	if (queue == NULL) {
		return 2;
	}
	if (copy_from_user(newNode, node, sizeof(qnode_421_t))) {
		kfree(newNode);
		return -EIO;
	}
	enqueue(newNode);
	return 0;
}
