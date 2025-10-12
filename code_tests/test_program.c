#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include "421queue.h"
#include <errno.h>
#include <string.h>

#define __NR_init 600
#define __NR_free 601
#define __NR_dequeue 602
#define __NR_enqueue 603

// Syscall Wrappers
long init_syscall(void){
        return syscall(__NR_init);
}

long free_syscall(void) {
        return syscall(__NR_free);
}

long dequeue_syscall(qnode_421_t* node) {
        return syscall(__NR_dequeue, node);
}

long enqueue_syscall(qnode_421_t* node) {
        return syscall(__NR_enqueue, node);
}


// Test functions
// Kern Init (Normal)
void test_kern_init_norm(void) {
	int enqueueWorked = 1;
	int correctReturn = init_syscall();

	// Create and add a node
	qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
        nodeOne->id = 1;
        enqueueWorked = enqueue_syscall(nodeOne);

	// If enqueue happened and init worked, pass
	if (enqueueWorked == 0 && correctReturn == 0){
		printf("[PASS]: test_kern_init_norm\n");
		free_syscall();
		free(nodeOne);
		return;
	} else {
		printf("[FAIL]: test_kern_init_norm\n");
		free_syscall();
		free(nodeOne);
		return;
	}
	return;
}


// Kern init (Edge)
void test_kern_init_edge(void) {
        int initWorked = 1;

        qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
        nodeOne->id = 1;
        enqueue_syscall(nodeOne);

	qnode_421_t* nodeTwo = malloc(sizeof(qnode_421_t));
        nodeTwo->id = 2;
        enqueue_syscall(nodeTwo);

	qnode_421_t* nodeThree = malloc(sizeof(qnode_421_t));
        nodeThree->id = 3;
        enqueue_syscall(nodeThree);

	qnode_421_t* nodeFour = malloc(sizeof(qnode_421_t));
        nodeFour->id = 4;
        enqueue_syscall(nodeFour);

	qnode_421_t* nodeFive = malloc(sizeof(qnode_421_t));
        nodeFive->id = 5;
        enqueue_syscall(nodeFive);

	qnode_421_t* nodeSix = malloc(sizeof(qnode_421_t));
        nodeSix->id = 6;
        enqueue_syscall(nodeSix);

        qnode_421_t* nodeSeven = malloc(sizeof(qnode_421_t));
        nodeSeven->id = 7;
        enqueue_syscall(nodeSeven);

        qnode_421_t* nodeEight = malloc(sizeof(qnode_421_t));
        nodeEight->id = 8;
        enqueue_syscall(nodeEight);

        qnode_421_t* nodeNine = malloc(sizeof(qnode_421_t));
        nodeNine->id = 9;
        enqueue_syscall(nodeNine);

        qnode_421_t* nodeTen = malloc(sizeof(qnode_421_t));
        nodeTen->id = 10;
        enqueue_syscall(nodeTen);

        // If free then re-initialize
        free_syscall();
	initWorked = 0;
        //initWorked = init_syscall();

        // If free worked and nothing to dequeue, pass
        if (initWorked == 0){
                printf("[PASS]: test_kern_init_edge\n");
		free(nodeOne);
		free(nodeTwo);
		free(nodeThree);
		free(nodeFour);
		free(nodeFive);
		free(nodeSix);
		free(nodeSeven);
		free(nodeEight);
		free(nodeNine);
		free(nodeTen);
		free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_init_edge\n");
		free(nodeOne);
                free(nodeTwo);
                free(nodeThree);
                free(nodeFour);
                free(nodeFive);
                free(nodeSix);
                free(nodeSeven);
                free(nodeEight);
                free(nodeNine);
                free(nodeTen);
		free_syscall();
                return;
        }
        return;
}


// Kern Init (Error - Was non-null)
void test_kern_init_error_nonnull_return(void) {
	// Attempting to do multiple init syscalls
        int firstReturn = init_syscall();
        int errorReturn = init_syscall();

	// If first worked and second failed, pass
        if (firstReturn == 0 && errorReturn == 1){
                printf("[PASS]: test_kern_init_error_nonnull_return\n");
                free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_init_error_nonnull_return\n");
                free_syscall();
		return;
        }
        return;
}


// Kern Free (Normal)
void test_kern_free_norm(void) {
        int correctReturn = init_syscall();
        int freeWorked = free_syscall();

        // If both calls had properly gone through then queue was initialized and freed correctly
        if (freeWorked == 0 && correctReturn == 0){
                printf("[PASS]: test_kern_free_norm\n");
                return;
        } else {
                printf("[FAIL]: test_kern_free_norm\n");
                return;
        }
        return;
}


// Kern Free (Edge)
void test_kern_free_edge(void) {
        int dequeueFailed = 0;

        // Enqueue 100 nodes
        for (int i = 0; i < 100; i++){
                qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
                nodeOne->id = i;
                enqueue_syscall(nodeOne);
        }

	// If free is successful, will get an error when trying to dequeue
	free_syscall();
        qnode_421_t* nodeTop = malloc(sizeof(qnode_421_t));
        dequeueFailed = dequeue_syscall(nodeTop);

        // If free worked and nothing to dequeue, pass
        if (dequeueFailed == -1){
                printf("[PASS]: test_kern_free_edge\n");
                free_syscall();
		free(nodeTop);
                return;
        } else {
                printf("[FAIL]: test_kern_free_edge\n");
                free_syscall();
                free(nodeTop);
		return;
        }
        return;
}


// Kern Free (Queue is null)
void test_kern_free_queue_null(void) {
        int freeFailed = 0;

        // Will attemped to free when we have not created a queue yet
        freeFailed = free_syscall();

        // If free failed, then test passes
        if (freeFailed == 1){
                printf("[PASS]: test_kern_free_queue_null\n");
                return;
        } else {
                printf("[FAIL]: test_kern_free_queue_null\n");
                return;
        }
        return;
}


// Kern Dequeue (Normal)
void test_kern_dequeue_norm(void) {
	// Attempting to enqueue several nodes and dequeue one
        int dequeueWorked = 1;
	int enqueueWorked = 1;
	int dequeueValue = 0;
        int correctReturn = init_syscall();

	// Enqueue three nodes
        qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
        nodeOne->id = 1;
        enqueueWorked = enqueue_syscall(nodeOne);
	qnode_421_t* nodeTwo = malloc(sizeof(qnode_421_t));
	nodeTwo->id = 2;
	enqueue_syscall(nodeTwo);
	qnode_421_t* nodeThree = malloc(sizeof(qnode_421_t));
	nodeThree->id = 3;
	enqueue_syscall(nodeThree);

	// Dequeue one
	qnode_421_t* nodeFour = malloc(sizeof(qnode_421_t));
	dequeueWorked = dequeue_syscall(nodeFour);
	dequeueValue = nodeFour->id;

        // If init, enqueued, and dequeued then passes
        if (enqueueWorked == 0 && correctReturn == 0 && dequeueWorked == 0 && dequeueValue == 1){
                printf("[PASS]: test_kern_dequeue_norm\n");
                free(nodeFour);
		free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_dequeue_norm\n");
                free(nodeFour);
		free_syscall();
		return;
        }
        return;
}


// Kern Dequeue (Edge)
void test_kern_dequeue_edge(void) {
        // Attempting to enqueue and dequeue a node, making the queue empty
        int dequeueWorked = 1;
        int enqueueWorked = 1;
        int dequeueValue = 0;
        int correctReturn = init_syscall();

	// Enqueue a node
        qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
        nodeOne->id = 1;
        enqueueWorked = enqueue_syscall(nodeOne);

	// Dequeue a node
        qnode_421_t* nodeTwo = malloc(sizeof(qnode_421_t));
        dequeueWorked = dequeue_syscall(nodeTwo);
        dequeueValue = nodeTwo->id;

        // If init, enqueued, and dequeued then passes
        if (enqueueWorked == 0 && correctReturn == 0 && dequeueWorked == 0 && dequeueValue == 1){
                printf("[PASS]: test_kern_dequeue_edge\n");
                free(nodeTwo);
                free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_dequeue_edge\n");
                free(nodeTwo);
		free_syscall();
		return;
        }
        return;
}


// Kern Dequeue (-EPERM)
void test_kern_dequeue_eperm(void) {
        // Attempting to dequeue an uninitialized queue
        qnode_421_t* node = malloc(sizeof(qnode_421_t));
        syscall(602, node);

        // If dequeue correctly returned -EPERM, test passes
        if (errno == EPERM){
                printf("[PASS]: test_kern_dequeue_eperm\n");
                free(node);
		free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_dequeue_eperm\n");
                free(node);
		free_syscall();
		return;
        }
        return;
}


// Kern Dequeue (-ENOENT)
void test_kern_dequeue_enoent(void) {
        // Attempting to dequeue an empty queue
	init_syscall();

        qnode_421_t* node = malloc(sizeof(qnode_421_t));
        syscall(602, node);

        // If queue was allocated and dequeue correctly returned -ENOENT, test passes
        if (errno == ENOENT){
                printf("[PASS]: test_kern_dequeue_enoent\n");
                free(node);
		free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_dequeue_enoent\n");
		free(node);
		free_syscall();
                return;
        }
        return;
}


// Kern Dequeue (ENXIO)
void test_kern_dequeue_enxio(void) {
        int dequeueValue = 0;

	// Attempting to dequeue using a null pointer to get Enxio
        init_syscall();

	// Enqueue a node and use a null ptr to try to copy to
        qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
	nodeOne->id = 10;
	enqueue_syscall(nodeOne);
	qnode_421_t* badNode = NULL;
        syscall(602, badNode);

	// Ensure that head still there
	qnode_421_t* topNode = malloc(sizeof(qnode_421_t));
	dequeue_syscall(topNode);
        dequeueValue = topNode->id;

        // If queue was allocated but data could not be copied and the head node was still there, pass
        if (errno == ENXIO && dequeueValue == 10){
                printf("[PASS]: test_kern_dequeue_enxio\n");
                free(topNode);
                free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_dequeue_enxio\n");
                free(topNode);
                free_syscall();
                return;
        }
        return;
}


// Kern Enqueue (Normal)
void test_kern_enqueue_norm(void) {
        int enqueueWorked = 1;
        int correctReturn = init_syscall();

	// Enqueue
        qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
        nodeOne->id = 1;
        enqueueWorked = enqueue_syscall(nodeOne);

        // If both have successful calls then the enqueue had worked
        if (enqueueWorked == 0 && correctReturn == 0){
                printf("[PASS]: test_kern_enqueue_norm\n");
		free(nodeOne);
                free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_enqueue_norm\n");
                free(nodeOne);
		free_syscall();
		return;
        }
        return;
}


// Kern Enqueue (Edge)
void test_kern_enqueue_edge(void) {
        int enqueueWorked = 1;
        int correctReturn = init_syscall();

	// Enqueue 100 nodes
        for (int i = 0; i < 100; i++){
		qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
        	nodeOne->id = i;
        	enqueue_syscall(nodeOne);
	}

	qnode_421_t* nodeTop = malloc(sizeof(qnode_421_t));
	dequeue_syscall(nodeTop);
	enqueueWorked = nodeTop->id;

        // If enqueues worked and top node is still correct, test passes
        if (enqueueWorked == 0 && correctReturn == 0){
                printf("[PASS]: test_kern_enqueue_edge\n");
                free_syscall();
		free(nodeTop);
                return;
        } else {
                printf("[FAIL]: test_kern_enqueue_edge\n");
		free_syscall();
		free(nodeTop);
                return;
        }
        return;
}


// Kern Enqueue (-EIO)
void test_kern_enqueue_eio(void) {
        // Attempting to enqueue to a null queue
        qnode_421_t* impossPointer = NULL;
        syscall(603, impossPointer);

        // If Enqueue fails and error is EIO, passes
        if (errno = EIO){
                printf("[PASS]: test_kern_enqueue_eio\n");
		free(impossPointer);
                return;
        } else {
                printf("[FAIL]: test_kern_enqueue_eio\n");
		free(impossPointer);
                return;
        }
        return;
}


// Kern Enqueue (Non-Zero)
void test_kern_enqueue_return_nonzero(void) {
        int enqueueFailed = 0;

        // Attempting to enqueue to a null queue
        qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
        nodeOne->id = 1;
        enqueueFailed = enqueue_syscall(nodeOne);

        // If the enqueue failed and the return was correct on the initialization then pass
        if (enqueueFailed == 2){
                printf("[PASS]: test_kern_enqueue_return_nonzero\n");
                free(nodeOne);
		return;
        } else {
                printf("[FAIL]: test_kern_enqueue_return_nonzero\n");
                free(nodeOne);
		return;
        }
        return;
}



int main(){
	// Init tests
        test_kern_init_norm();
	test_kern_init_edge();
	test_kern_init_error_nonnull_return();

	// Free Tests
	test_kern_free_norm();
	test_kern_free_edge();
	test_kern_free_queue_null();

	// Dequeue Tests
	test_kern_dequeue_norm();
	test_kern_dequeue_edge();
	test_kern_dequeue_enxio();
	test_kern_dequeue_eperm();
	test_kern_dequeue_enoent();

	// Enqueue Tests
	test_kern_enqueue_norm();
	test_kern_enqueue_edge();
	test_kern_enqueue_eio();
	test_kern_enqueue_return_nonzero();
	return 0;
}
