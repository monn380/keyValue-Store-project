#include <kv.h>
#include <string.h>
#include <stdlib.h>

size_t hash(char* val, int capacity){
  size_t hash = 0x13371337deadbeef;
  while(*val) {
    hash ^= *val;
    hash = hash << 8;
    hash += *val;
    
    val++;
  }
  return hash % capacity;
}



kv_t *kv_init(size_t capacity) {
  if (capacity == 0) return NULL;

  kv_t *table = malloc(sizeof(kv_t));
  if (table == NULL) return NULL;

  table->capacity = capacity;
  table->count = 0;
  table->entries = calloc(sizeof(kv_entry_t), capacity);
  if (table->entries == NULL) return NULL;
  return table;
}

int kv_put(kv_t *table, char *key, char *val){
  size_t idx = hash(key,table->capacity);
  size_t real_idx = (idx) % table->capacity;
  kv_entry_t *entry = &table ->entries[real_idx];
        entry->value = val;
        entry->key = key;
        table->count++;
        return real_idx;

}

/*fn kv_put
 * returns the index of the key, otherwise
 * on error returns -1, on not found returns -2*/
/*int kv_put(kv_t *table, char *key, char *val){
  if (!table || !key || !val) return -1;
  
  size_t idx = hash(key,table->capacity);
  for (int i = 0; i < table->capacity-1; i++) {
    size_t real_idx = (idx+i) % table->capacity;
    
    kv_entry_t *entry = &table->entries[real_idx];

    //the key is already set, updating
if (entry->key && entry->key != (void*)TOMBSTONE &&
        !strcmp(entry->key, key)) {
        char *newval = strdup(val);
        if (!newval) return -1;
        entry->value = newval;
        return real_idx;
        }

    //lands in an empty slot either null or tombstone
   if (!entry->key || entry->key == (void*)TOMBSTONE){
        char *newval = strdup(val);
        char *newkey = strdup(key);
        if (!newval || !newkey) {
          free(newval);
          free(newkey);
          return -1;
        }
        entry->value = newval;
        entry->key = newkey;
        table->count++;
        return real_idx;
    } 
    // the database is occupied
    return -2;
  }
  return -1;
}*/
