#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include "421queue.h"

#define __NR_init 600
#define __NR_free 601
#define __NR_dequeue 602
#define __NR_enqueue 603

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

	qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
        nodeOne->id = 1;
        enqueueWorked = enqueue_syscall(nodeOne);
	// if both have successful calls then the queue had been properly allocated
	if (enqueueWorked == 0 && correctReturn == 0){
		printf("[PASS]: test_kern_init_norm\n");
		free_syscall();
		return;
	} else {
		printf("[FAIL]: test_kern_init_norm\n");
		return;
	}
	return;
}

// Kern Init (Error - Was non-null)
void test_kern_init_error_nonnull_return(void) {
	// Attempting to do multiple init syscalls
        int firstReturn = init_syscall();
        int errorReturn = init_syscall();

        if (firstReturn == 0 && errorReturn == 1){
                printf("[PASS]: test_kern_init_error_nonnull_return\n");
                free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_init_error_nonnull_return\n");
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
// Kern Dequeue (Edge)
// Kern Dequeue (Error)
// Kern Dequeue (-EPERM)
// Kern Dequeue (-ENOENT)
// Kern Dequeue (-ENXIO) + head still there


// Kern Enqueue (Normal)
void test_kern_enqueue_norm(void) {
        int enqueueWorked = 1;
        int correctReturn = init_syscall();

        qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
        nodeOne->id = 1;
        enqueueWorked = enqueue_syscall(nodeOne);

        // If both have successful calls then the enqueue had worked
        if (enqueueWorked == 0 && correctReturn == 0){
                printf("[PASS]: test_kern_enqueue_norm\n");
                free_syscall();
                return;
        } else {
                printf("[FAIL]: test_kern_enqueue_norm\n");
                return;
        }
        return;
}

// Kern Enqueue (Edge)
// Kern Enqueue (-ENOMEM)
// Kern Enqueue (-EIO)
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
                return;
        } else {
                printf("[FAIL]: test_kern_enqueue_return_nonzero\n");
                return;
        }
        return;
}



int main(){
        test_kern_init_norm();
	test_kern_init_error_nonnull_return();
	test_kern_free_norm();
	test_kern_free_queue_null();
	test_kern_enqueue_norm();
	test_kern_enqueue_return_nonzero();
	return 0;
}
