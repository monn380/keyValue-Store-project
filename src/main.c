#include <stdio.h>
#include <kv.h>
#include <assert.h>

int main() {

  kv_t *table = kv_init(1024);
  printf("%p\n", table);
  assert(table->capacity == 1024);
  assert(table->count==0);
  assert(table != NULL);
  kv_put(table,"lele","haha");
  kv_put(table,"lolo","hfhf");
  kv_put(table,"hehe","hphp");
  kv_put(table,"hoho","hihi");
  
  char *val1 = kv_get(table,"lele");
  char *val2 = kv_get(table,"lolo");
  char *val3 = kv_get(table,"not_exists");
  printf("%s %s %s\n",val1 ,val2, val3);
  printf("now we test kv_delete\n");
  int result = kv_delete(table, "hoho");
}

