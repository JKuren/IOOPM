#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

typedef struct test test_t;

struct test {
  char * chr_ptr;
  char * chr_ptr2;
  char * chr_ptr3;
  char * chr_ptr4;
};

int cmp_void(elem_t a, elem_t b) {
  if(a.p == b.p) {
    
    return 0;
  }
  return 1;
}

void scan(void *obj, ioopm_list_t* collection) {  
  unsigned long size = sizeof(obj);
  // unsigned long end_addr = (unsigned long)&obj + 1;
  printf("%lu\n", size);
  printf("%p\n", obj );
  printf("%p\n", &obj + 1);
  for(unsigned long i = 0; i < size; i++){

    void *possible_pointer = obj + i*8;
    void** p_ptr = (void **) possible_pointer;

    elem_t poss_pointer = (elem_t)*p_ptr;
    printf("CHECK PTR: %p\n", &p_ptr);
    
    printf("ADDR: %p \n", obj + i*8);

    if(ioopm_linked_list_contains(collection, poss_pointer)) {
      printf("removed an oject \n");
      printf("%p free \n", *p_ptr);

      free(*p_ptr);
      
      // release(*p_ptr);
      // releasing should deal wth
      // deallocating all objects in struct
      // from our collection so we should
      // have no memory leaks
    }
    
  }

}


int main(int argc, char *argv[]){

  ioopm_list_t* collection = ioopm_linked_list_create(cmp_void);
  test_t *obj = calloc(1, sizeof(test_t));
  char *str = calloc(1, sizeof(str));
  obj->chr_ptr  =  calloc(1, 8);
  obj->chr_ptr2  =  str;
  obj->chr_ptr3  =  calloc(1, 8);
  obj->chr_ptr4  =  calloc(1, 8);

  
  ioopm_linked_list_append(collection, (elem_t)(void*)(obj->chr_ptr));
  ioopm_linked_list_append(collection, (elem_t)(void*)(obj->chr_ptr2));
  ioopm_linked_list_append(collection, (elem_t)(void*)(obj->chr_ptr3));
  ioopm_linked_list_append(collection, (elem_t)(void*)(obj->chr_ptr4)); 
 
  scan(obj, collection);

  printf("%lu", sizeof(obj));
  free(obj);
  ioopm_linked_list_clear(collection);
  ioopm_linked_list_destroy(collection);
  
}
