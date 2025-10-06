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
	if (kqueue_421_t == NULL){
		return -EPERM;
	} else if (num_nodes < 1 || head == NULL){
		return -ENOENT;
	} else if (num_nodes == 1){
		qnode_421_t* temp = head;
		head = NULL;
		tail = NULL;
		num_nodes--;
		kfree(temp);
		return temp;
	} else {
		head = head->next;
			if (num_nodes == 2){
				tail = head;
			}
		num_nodes--;
		kfree(temp);
		return temp;
	}
	return NULL;
}

void enqueue(qnode_421_t* node) {
	if (num_nodes < 1) {
		head = node;
		tail = node;
		num_nodes++;
		return;
	} else if (num_nodes == 1) {
		head->next = node;
		tail = node;
		num_nodes++;
		return;
	} else {
		tail->next = node;
		tail = node;
		num_nodes++;
  		return;
	return;
}

long queue_init(void) {
	if (head || tail || num_nodes > 0){
		return -1;
	}
	else {
		head = NULL;
		tail = NULL;
		num_nodes = 0;
		return 0;
	}
}

long queue_free(void) {
	if (kqueue_421_t == NULL){
		return 1;
	}
	while (head != NULL){
		kfree(dequeue());
	}
	head = NULL;
	tail = NULL;
	num_nodes = 0;
	return 0;
}

// kernel-space initializer.
SYSCALL_DEFINE0(kern_queue_init) {
	return kern_queue_init;
}

// kernel-space free-er.
SYSCALL_DEFINE0(kern_queue_free) {
	return kern_queue_free;
}

/**
 * kernel-space function to dequeue a Node.
 * HINT:  remember, your user-space program will need the value of the node.
 *        how can you get the data from kernel-space to user-space, i wonder?
 * RETURN VALUE: should be 0 on success, 1 otherwise.
 */
SYSCALL_DEFINE1(kern_dequeue, void __user*, dest) {
	if (kqueue_421_t == NULL){
		return -EPERM;
	} else if (kqueue_421_t->num_nodes < 1 || kqueue_421_t->head == NULL){
		return -ENOENT;
	}
	// EDIT TO MATCH SPEC AB CHECKING BEFORE REMOVING
	qnode_421_t* topOfQueue = dequeue();
	if (copy_to_user(dest, topOfQueue, sizeof(qnode_421_t))) {
		return -ENXIO;
	} else {
		kfree(temp);
		return 0;
	}
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
	if (kqueue_421_t == NULL || kqueue_421_t->head == NULL || kqueue_421_t->num_nodes <) {
		return 2;
	}
	if (copy_from_user(newNode, node, sizeof(qnode_421_t))) {
		kfree(temp);
		return -EIO;
	}
	enqueue(newNode);
	return 0;
}
