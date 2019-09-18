#include <iostream>
using namespace std;

#define DEFAULT_MEM_SIZE 1024 * 1024 // 1 MB
#define HEADER_SIZE sizeof(memory_block_header)

struct memory_block_header{
    size_t size;
    size_t prev_size;
    bool free;
} ;

struct Memory_container{
    void *addr;
    bool free;
    size_t size;
} ;

struct Memory_container heap;

//void *write_header_block(memory_block_header *current_header){
//
//}
//
//void *find_next(memory_block_header* current_header){
//
//}

void mem_init(){
    int size = DEFAULT_MEM_SIZE;
    heap.addr = malloc(size);
    heap.size = size;
    struct memory_block_header currentHeader;
    currentHeader.size = DEFAULT_MEM_SIZE-HEADER_SIZE;
    currentHeader.free = true;
    currentHeader.prev_size = 0;
    memory_block_header * start_pointer = (memory_block_header *)heap.addr;
    *start_pointer = currentHeader;
}

void *mem_alloc(size_t size){
    struct memory_block_header currentHeader;
    currentHeader.size = size;
    currentHeader.free = false;
    currentHeader.prev_size = 0;

    memory_block_header * curr_pointer = (memory_block_header *)(heap.addr);

//    cout << "------" << endl << curr_pointer->free << endl;
//    cout << curr_pointer->size << endl;
//    cout << curr_pointer->prev_size << endl;

    while(!curr_pointer->free){
//        cout << curr_pointer->free << endl;
//

//        *curr_pointer = currentHeader;
        curr_pointer = curr_pointer + curr_pointer->size + HEADER_SIZE;
    };

    struct memory_block_header nextHeader;
    nextHeader.size = curr_pointer->size-currentHeader.size;
    nextHeader.free = true;
    nextHeader.prev_size = size;

    memory_block_header * next_pointer = curr_pointer + HEADER_SIZE + size;
    *next_pointer = nextHeader;

    *curr_pointer = currentHeader;

    void * result_pointer = curr_pointer + HEADER_SIZE;
    return result_pointer;

//    memory_block_header * header_poiner = (memory_block_header *)(heap.addr);
//    *header_poiner = currentHeader;
//    void * result_pointer = header_poiner + HEADER_SIZE;
//    return result_pointer;
//    memory_block_header * start_header = (memory_block_header *)heap.addr;
//    cout << start_header->free << endl << start_header->size << endl;

    return (void *)((int*)heap.addr + HEADER_SIZE);
};

void *mem_realloc(void *addr, size_t size){
    return heap.addr;
};

void *mem_free(void *addr){
    return heap.addr;
};


int main(int argc, const char * argv[]) {
    // insert code here...
    mem_init();
    int* a = (int *)mem_alloc(sizeof(int));
    int* b = (int *)mem_alloc(sizeof(int));
    int* c = (int *)mem_alloc(sizeof(int));
    *a = 1;
    *b = 2;
    *c = 3;
    cout << "Hello, World!\n"<<endl;
    cout << *a << *b << *c <<endl;
    return 0;
}
