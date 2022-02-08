#include <stdio.h>
#include "../kernel/queue.c"

int main() {

    Queue queue;
    unsigned char data[43];
    Queue* q = &queue;

    queue_init(q, data, 5);
    printf("queueEmpty: %d\n", queue_empty(q));
    printf("queuePush: %d\n", queue_push(q, 'c'));
    printf("queuePush: %d\n", queue_push(q, 'a'));
    printf("queueSize: %d\n", queue_size(q));
    printf("queueSize: %d\n", queue_size(q));
    printf("queueSize: %d\n", queue_size(q));
    printf("queueSize: %d\n", queue_size(q));
    printf("queueSize: %d\n", queue_size(q));
    printf("queuePop: %d\n", queue_pop(q));
    printf("queuePop: %d\n", queue_pop(q));
    printf("queueSize: %d\n", queue_size(q));
    printf("queueSize: %d\n", queue_size(q));
    printf("queueSize: %d\n", queue_size(q));
    printf("queueSize: %d\n", queue_size(q));
}
