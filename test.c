#include "arena.h"
#include <stdio.h>


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

  Arena b = arena_init(100);
   
  uint8_t* ptr4;

  uint16_t cnt = 0;


  while(1)
  {
    ptr4 = arena_alloc(&b, 10);
    if(ptr4 == NULL)
    {
      printf("allocated %d times and used upto %zu \n", cnt, b.used);
      break; 
    }
    cnt++;
  }  
  return 0;
}
