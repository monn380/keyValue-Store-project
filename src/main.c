#include <stdio.h>
#include <kv.h>
#include <assert.h>

int main() {

  kv_t *table = kv_init(1024);
  printf("%p\n", table);
  assert(table->capacity == 1024);
  assert(table->count==0);
  assert(table != NULL);

  kv_put(table,"hehe","haha");
  printf("capacity %ld\n",table->capacity);
   for (int i = 0;i < table->capacity; i++) {
    if (table->entries[i].key){
      printf("[%d] %s : %s\n", i,
              table->entries[i].key,
              table->entries[i].value);
    }
   }
}

