#include<stdio.h>
#include<stdint.h>
#include<math.h>
#include<sys/mman.h>

void init_list();
void walk();
void coalesce(void *ptr);
void free(void *pt);
void * palloc(int size);
