//
// Created by Дмитрий Надобко on 9/17/19.
//

#define DEFAULT_MEM_SIZE 1024 * 1024 // 1 MB

#include <stdio.h>

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

void memInit();

void *memAlloc(size_t size);

void *mem_realloc(void *addr, size_t size);

void *mem_free(void *addr);

