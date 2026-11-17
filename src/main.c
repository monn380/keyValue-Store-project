#include <stdio.h>
#include <kv.h>
#include <assert.h>

int main() {

  kv_t *table = kv_init(1024);
  printf("%p\n", table);
  assert(table->capacity == 1024);
  assert(table->count==0);
  assert(table != NULL);

  int status = 0;
  kv_put(table,"lele","haha");
  kv_put(table,"lolo","hfhf");
  status = kv_put(table,"hehe","hphp");
  printf("status kv_put: %d\n", status);
  status = kv_put(table,"hoho","hihi");
  printf("status kv_put: %d\n", status);
  
  printf("capacity %ld\n",table->capacity);
   for (int i = 0;i < table->capacity; i++) {
    if (table->entries[i].key){
      printf("[%d] %s : %s\n", i,
              table->entries[i].key,
              table->entries[i].value);
    }
   }
}

