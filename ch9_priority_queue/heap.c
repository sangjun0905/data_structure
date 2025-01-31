#include <stdio.h>
#define MAX_ELEMENT 20

typedef struct{
    int key;
}element;

typedef struct{
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;