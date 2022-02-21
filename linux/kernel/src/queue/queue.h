#ifndef QUEUE_H
#define QUEUE_H


struct Queue {
    unsigned char *node_arr;
    int start, end, capacity, size;
};
#define Queue struct Queue

Queue *queue_init(Queue *queue, unsigned char *buf, int size);

int queue_size(Queue *queue);

int queue_empty(Queue *queue);

int queue_full(Queue *queue);

int queue_push(Queue *queue, unsigned char c);

unsigned char queue_pop(Queue *queue);

#endif //QUEUE_H
