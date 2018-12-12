#include <stdio.h>
#include <stddef.h> // offsetof macro
#include <stdlib.h>
// Register metadata about the pointer fields f1 .. fn of type type
#define GET_MACRO(_1,_2,_3, NAME, ...) NAME // OVERLOADING MACRO
#define register_type2(type, f1, f2)                                  \
  __register_type2(#type, sizeof(type), offsetof(type, f1), offsetof(type, f2))

#define register_type(...) GET_MACRO(__VA_ARGS__, register_type2)(__VA_ARGS__) //OVERLOADING MACRO

#define allocate_from_type(type) \
  __allocate_from_type(#type)


struct list{
  int* first;
  int* last;
  
};

typedef struct list list_t;

void __register_type2(char* type, int size_of_type,int offset_one, int offset_two){
  printf("type name: %s \n", type); 
  printf("type size: %d \n", size_of_type);
  printf("offset 1: %d \n", offset_one);
  printf("offset 2: %d \n", offset_two);

}

void __allocate_from_type(char *type){
  printf("type name: %s \n", type);
}

int main(int argc, char *argv[]){
  if (argc < 2)
    {
      fprintf(stdout, "Usage: %s fil1 ...\n", argv[0]);
    }
  else{
    int a = 5;
    int b = 10;
    
    list_t *list = calloc(1, sizeof(list_t));
    list->first = &a;
    list->last = &b;

    register_type(list_t, first, last);
  }
  
}
