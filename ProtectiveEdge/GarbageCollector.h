#pragma once


#include <stdlib.h>

struct GarbageCollector {
    void** pointers;
    size_t size;
};

 struct GarbageCollector* Garbage;

struct GarbageCollector* gc_startup(int initial_size);

void gc_add(void* pointer);

void gc_cleanup();