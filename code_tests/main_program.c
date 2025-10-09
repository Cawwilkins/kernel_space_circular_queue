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
	return syscall(__NR_dequeue);
}

long enqueue_syscall(qnode_421_t* node) {
	return syscall(__NR_enqueue, node);
}



int main(){
	// Initialize queue
	printf("Initializing queue\n");
	printf("queue init: %ld\n", init_syscall());

	// Create three nodes w ascending ids
	// Printing each id in order they are enqueued
	qnode_421_t* nodeOne = malloc(sizeof(qnode_421_t));
	nodeOne->id = 1;
	printf("Qnode id: %d\n", nodeOne->id);
	printf("Enqueued?: %ld\n", enqueue_syscall(nodeOne));

	qnode_421_t* nodeTwo = malloc(sizeof(qnode_421_t));
        nodeTwo->id = 2;
	printf("Qnode id: %d\n", nodeTwo->id);
        printf("Enqueued?: %ld\n", enqueue_syscall(nodeTwo));

	qnode_421_t* nodeThree = malloc(sizeof(qnode_421_t));
        nodeThree->id = 3;
	printf("Qnode id: %d\n", nodeThree->id);
        printf("Enqueued?: %ld\n", enqueue_syscall(nodeThree));

	// Print each id in order they are dequeued
	printf("Beginning dequeuing\n");
	qnode_421_t* tempOne = malloc(sizeof(qnode_421_t));
	printf("Dequeued?: %ld \n", dequeue_syscall(tempOne));
	printf("Id should be: 1, Id returned is: %d \n", tempOne->id);
	free(tempOne);

        qnode_421_t* tempTwo = malloc(sizeof(qnode_421_t));
        printf("Dequeued?: %ld \n", dequeue_syscall(tempTwo));
        printf("Id should be: 2, Id returned is: %d \n", tempTwo->id);
        free(tempTwo);

        qnode_421_t* tempThree = malloc(sizeof(qnode_421_t));
        printf("Dequeued?: %ld \n", dequeue_syscall(tempThree));
        printf("Id should be: 3, Id returned is: %d \n", tempThree->id);
        free(tempThree);

	// free
	printf("Now to free:");
	printf("Freed?: %ld \n", free_syscall());

	//tons of print statements to show exactly what is happening at each step
	return 0;
}
