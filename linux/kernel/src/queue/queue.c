#include "queue.h"

Queue *queue_init(Queue *queue, unsigned char *buf, int size) {
    // 记住不能使用内部定义的数组, 因为是临时的
    // unsigned char cc[size + 1];
    queue->node_arr = buf; //malloc(sizeof(unsigned char) * (size + 1));
    queue->capacity = size;
    queue->size = 0;
    queue->start = 0;
    queue->end = 0;
    return queue;
}
// #define queue_real_end (queue->end + queue->capacity + 1) % (queue->capacity + 1)
#define queue_real_index(x) (((x) + queue->capacity) % (queue->capacity))

int queue_size(Queue *queue) {
    // return queue_real_end - queue->start;
    return queue->size;
}

int queue_empty(Queue *queue) {
    // return queue->end == queue->start;
    return queue->size == 0;
}

int queue_full(Queue *queue) {
    // return queue_real_end + 1 == queue->start;
    return queue->size == queue->capacity;
}

int queue_push(Queue *queue, unsigned char c) {
    if (!queue_full(queue)) {
        queue->node_arr[queue->end] = c;
        // queue->end++;
        // queue->end = queue_real_end;
        queue->end = queue_real_index(queue->end + 1);// + queue->capacity) % (queue->capacity);
        queue->size++;
        return 1;
    }
    return 0;
}

unsigned char queue_pop(Queue *queue) {
    if (!queue_empty(queue)) {
        // printf("%d\n",queue->node_arr[queue->start]);
        unsigned char c = queue->node_arr[queue->start];
        // printf("%d\n",queue->node_arr[queue->start]);
        // printf("%d %c\n",c,c);
        // queue->start = (queue->start + 1 + queue->capacity + 1) % (queue->capacity + 1);
        queue->start = queue_real_index(queue->start + 1);// (queue->start + 1 + queue->capacity) % (queue->capacity);
        queue->size--;
        return c;
    }
    return 0;
}
