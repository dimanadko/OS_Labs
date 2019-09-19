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
//    cout << "=======" << curr_pointer->size << " - " << size << endl;
//    cout << (curr_pointer->size < size) << endl;
    cout << "new while" << endl;

    while((!curr_pointer->free) && (curr_pointer->size <= size)){
        cout << "free: " << curr_pointer->free << ':' << curr_pointer->size << ':' << *(int*)(curr_pointer+HEADER_SIZE) << endl;
//        cout << curr_pointer->size << " " << size << endl;

//        *curr_pointer = currentHeader;
        curr_pointer = (memory_block_header *)((char *)curr_pointer + curr_pointer->size + HEADER_SIZE);
        cout << "free after: " << curr_pointer->free << endl;
    };

    struct memory_block_header nextHeader;
    nextHeader.size = curr_pointer->size-currentHeader.size;
    nextHeader.free = true;
    nextHeader.prev_size = size;

    memory_block_header * next_pointer = (memory_block_header *)((char *)curr_pointer + HEADER_SIZE + size);
    *next_pointer = nextHeader;

    *curr_pointer = currentHeader;

    void * result_pointer = (memory_block_header *)((char *)curr_pointer + HEADER_SIZE);
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

void mem_free(void *addr){
    memory_block_header * curr_header = (memory_block_header *)((char*)addr-HEADER_SIZE);
    cout<< (char*)(curr_header) + HEADER_SIZE << ":" << ((char*)(addr)-HEADER_SIZE)+HEADER_SIZE << " \n equal: " <<((char*)curr_header + HEADER_SIZE == ((char*)addr-HEADER_SIZE)+HEADER_SIZE )<< endl;
    cout<< "delete:" << *(int*)(curr_header+HEADER_SIZE) << *(int*)addr <<endl;
    curr_header->free = true;
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
    mem_free(b);
    memory_block_header* prev_b_header = (memory_block_header*)((char*)b-HEADER_SIZE);
    cout << "prev_b_header: " << prev_b_header->free << endl;
    int* d = (int *)mem_alloc(sizeof(int));
    *d = 4;
    cout << "Hello, World!\n"<<endl;
    cout << *a << *b << *c << *d <<endl;
    return 0;
}
