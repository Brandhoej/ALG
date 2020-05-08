#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int tail, head;
    unsigned int length;
    int *array;
} Queue;

/* Constructs a new queue with the desired length */
Queue *newQueue(unsigned int length);
/* Frees the queue and its inner array */
void freeQueue(Queue *queue);
/* Enqueues an item to the queue. Overwrites instead of overflow */
void enqueue(Queue *queue, int item);
/* Dequeues and item from the queue */
int dequeue(Queue *queue);

int main() {
    Queue *queue = newQueue(10);

    /* Tests */
    printf("Head (%2i) -> tail (%2i)\n", queue->head, queue->tail);
    enqueue(queue, 0);
    printf("Head (%2i) -> tail (%2i)\n", queue->head, queue->tail);
    printf("Dequeued value was %2i\n", dequeue(queue));

    return 0;
}

Queue *newQueue(unsigned int length){
    Queue *queue = malloc(sizeof(Queue));
    queue->head = 0;
    /* The tail will point to the next location with out and item */
    queue->tail = 1;
    queue->array = calloc(length, sizeof(int));
    queue->length = length;
    return queue;
}

void freeQueue(Queue *queue) {
    free(queue->array);
    queue->array = NULL;
    free(queue);
    queue = NULL;
}

void enqueue(Queue *queue, int item) {
    queue->array[queue->tail] = item;
    /* Wrap the tail around */
    if(queue->tail == queue->length - 1) {
        queue->tail = 0;
    } else {
        queue->tail = queue->tail + 1;
    }
}

int dequeue(Queue *queue) {
    int item = queue->array[queue->head];
    /* Wrap the head around (Yikes) */
    if(queue->head == queue->length - 1) {
        queue->head = 0;
    } else {
        queue->head++;
    }
    return item;
}