#include <stdio.h>
#include <kv.h>
#include <assert.h>

int main() {

  kv_t *table = kv_init(3);
  printf("%p\n", table);

  kv_put(table,"hehe","haha");
   for (int i = 0;i<2; i++) {
     printf("prova prima di if\n");
    if (table->entries[i].key){
      printf("prova\n");
     /* printf("%s: %s\n",
      *        table->entries[i].key,
      *        table->entries[i].value);*/
    }
   }
}

