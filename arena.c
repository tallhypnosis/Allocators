#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include"arena.h"


Arena arena_init(size_t capacity)
{
    
  Arena stats;
  stats.start = NULL;
  stats.current = NULL;
  stats.capacity = 0;
  stats.used = 0;

  void *ptr = mmap(NULL, capacity, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  if(ptr == MAP_FAILED)
  {
    return stats;
  }


  stats.start = ptr;
  stats.current = ptr;
  stats.capacity = capacity;
  stats.used = 0;

  return stats;
}


void* arena_alloc(Arena *a, size_t bytes)
{
  uintptr_t addr = (uintptr_t)a->current;
  size_t padding = ((8 - (addr & 7)) & 7);

  if(a->capacity - a->used < (bytes + padding) )
  {
  
    //perror("Cannot allocated not enough memory");
    return NULL;
  }
 
  void* aligned_ptr = (void*)(addr + padding);
  a->current = (uint8_t*)aligned_ptr + bytes;
  a->used = a->used+(bytes + padding);
  return aligned_ptr;

}

void arena_reset(Arena *a)
{
  if(a)   
  {
    a->current = a->start;
    a->used = 0;
  }
}

void arena_destroy(Arena *a)
{
  if(a && a->start)
  {
    munmap(a->start, a->capacity);
    a->start = NULL;
    a->current = NULL;
    a->capacity = 0;
    a->used = 0;
  }
}

  
