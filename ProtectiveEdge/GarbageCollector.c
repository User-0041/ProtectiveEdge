#include <stdlib.h>

#include "GarbageCollector.h"

// Global garbage collector variable
struct GarbageCollector* Garbage;

// Function to initialize the garbage collector
struct GarbageCollector* gc_startup(int initial_size) {
    Garbage = (struct GarbageCollector*)malloc(sizeof(struct GarbageCollector));
    if (Garbage == NULL) {
        return NULL; // Allocation failed
    }

    Garbage->pointers = (void**)malloc(initial_size * sizeof(void*));
    if (Garbage->pointers == NULL) {
        free(Garbage);
        return NULL; // Allocation failed
    }

    Garbage->size = 0; // Initialize size to 0
    return Garbage;
}

// Function to add a pointer to the garbage collector
void gc_add(void* pointer) {
    if (Garbage == NULL) {
        return; // Invalid garbage collector
    }

    // Resize the array if needed
    if (Garbage->size % 10 == 0) {
        Garbage->pointers = (void**)realloc(Garbage->pointers, (Garbage->size + 10) * sizeof(void*));
        if (Garbage->pointers == NULL) {
            return; // Reallocation failed
        }
    }

    Garbage->pointers[Garbage->size++] = pointer;
}

// Function to clean up resources in the garbage collector
void gc_cleanup() {
    if (Garbage == NULL) {
        return; // Invalid garbage collector
    }

    // Free individual pointers
    for (int i = 0; i < Garbage->size; ++i) {
        free(Garbage->pointers[i]);
    }

    // Free the array itself
    free(Garbage->pointers);

    // Free the garbage collector struct
    free(Garbage);
}
/*
// Example usage
int main() {
    // Initialize the garbage collector with an initial size of 10
    gc_startup(10);

    // Add some pointers to the garbage collector
    int* ptr1 = (int*)malloc(sizeof(int));
    int* ptr2 = (int*)malloc(sizeof(int));

    gc_add(ptr1);
    gc_add(ptr2);

    // Cleanup resources when done
    gc_cleanup();

    return 0;
}
*/