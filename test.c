#include "arena.h"
#include <stdio.h>


void test_size(size_t size)
{
    
    Arena b = arena_init(100);

    uint8_t* ptr4;

    uint16_t cnt = 0;
    
    size_t prevUsg; 
    while(1)
    { 
    prevUsg = b.used;
    ptr4 = arena_alloc(&b, size);
    if(ptr4 == NULL) break; 
    cnt++;
    size_t max_alloc = cnt * size; 
    size_t padding = (b.used - prevUsg)- size;
//    printf("allocation size %zu bytes, max allocations is %zu, padding is %zu \n", size, max_alloc, padding);
    }
    size_t total_data = cnt * size;
    size_t total_padding = (b.used - total_data);
    size_t waste_pct = (total_padding * 100) / b.used;
    printf("total data consumed is %zu, total padding is %zu, total waste is %zu \n", total_data, total_padding, waste_pct);
}

int main()
{
  Arena a = arena_init(1024);
  if(a.start == NULL) 
  {
    printf("Failed to initialize arena\n");
  }
  printf("start address is %p, current address is %p, capacity is %zu, used upto %zu bytes \n", a.start, a.current, a.capacity, a.used);

  uint8_t* ptr1;

  ptr1 = arena_alloc(&a, 10);
 
 printf("after allocation of 10 bytes start address is %p, current address is %p, capacity is %zu, used upto %zu bytes \n", a.start, a.current, a.capacity, a.used);

  uint8_t* ptr2;
  ptr2 = arena_alloc(&a, 20);
  
  printf("after allocation of 10 bytes start address is %p, current address is %p, capacity is %zu, used upto %zu bytes \n", a.start, a.current, a.capacity, a.used);

  uint8_t* ptr3; 
  ptr3 = arena_alloc(&a, 30);
  
  printf("after allocation of 10 bytes start address is %p, current address is %p, capacity is %zu, used upto %zu bytes \n", a.start, a.current, a.capacity, a.used);



  printf("ptr1: %p (offset: %lu)\n", ptr1, (uintptr_t)ptr1 & 7);
  printf("ptr2: %p (offset: %lu)\n", ptr2, (uintptr_t)ptr2 & 7);
  printf("ptr3: %p (offset: %lu)\n", ptr3, (uintptr_t)ptr3 & 7);

    test_size(1);
    test_size(4);
    test_size(8);
    test_size(15);
    test_size(16);


  return 0;
}
