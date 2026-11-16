#include <stdio.h>
#include <kv.h>
#include <assert.h>

int main() {

  kv_t *table = kv_init(3);
  printf("%p\n", table);
  assert(table->capacity == 3);
  assert(table->count==0);
  assert(table != NULL);

  kv_put(table,"hehe","haha");
  printf("%ld:count\n",table->count);
  printf("key %s\n", table->entries[0].key);
  printf("value %s\n", table->entries[0].value);

   for (int i = 0;i<2; i++) {
     printf("prova prima di if\n");
    if (table->entries[i].key){
      printf("prova\n");
      printf("%s : %s\n",
              table->entries[i].key,
              table->entries[i].value);
    }
   }
}

