#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct{
    int key;
}element;

typedef struct{
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create(){
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h){
    h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item){
    int i = 0;
    i = ++(h->heap_size);

    while((i != 1) && (item.key > h->heap[i/2].key)){
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_max_heap(HeapType* h){
    int parent, child;
    element item, temp;
    item = h->heap[1];
    temp = h->heap[((h->heap_size)--)];

    parent = 1;
    child = 2;
    while(child <= h->heap_size){
        //현재 노드의 자식 중 큰 자식을 찾고 인덱스를 child에 저장장
        if((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) child++;
        if(temp.key >= h->heap[child].key) break;
        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

int main(){
    element e1 = {10}, e2 = {5}, e3 = {30};
    element e4, e5, e6;
    HeapType* heap;
    HeapType* heap = create();
    init(heap);

    insert_max_heap(heap, e1);
    insert_max_heap(heap, e2);
    insert_max_heap(heap, e3);
        
}