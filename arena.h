#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *start;      // Start of the arena (from mmap)
    uint8_t *current;    // Current bump pointer position
    size_t capacity;     // Total size of the arena
    size_t used;         // Bytes currently allocated (for stats)
} Arena;

// Create a new arena with the given capacity
Arena arena_init(size_t capacity);

// Allocate memory from the arena (8-byte aligned)
void* arena_alloc(Arena *a, size_t bytes);

// Reset the arena (reuse memory without freeing to OS)
void arena_reset(Arena *a);

// Destroy the arena and return all memory to OS
void arena_destroy(Arena *a);

#endif
