#include <iostream>
using namespace std;

struct memory_block_header{
    size_t size;
    size_t prev_size;
    bool full;
} ;

struct Memory_container{
    void *addr;
    bool full;
    size_t size;
} ;

struct Memory_container heap;

void memInit(){
    int size = DEFAULT_MEM_SIZE;
    heap.addr = malloc(size);
    heap.size = size;
}

void *memAlloc(size_t size){
    return heap.addr;
};

void *mem_realloc(void *addr, size_t size){
    return heap.addr;
};

void *mem_free(void *addr){
    return heap.addr;
};
