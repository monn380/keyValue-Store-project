#include <kv.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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


/*fn kv_put
 * returns the index of the key, otherwise
 * on error returns -1, on not found returns -2*/
int kv_put(kv_t *table, char *key, char *val){
  if (!table || !key || !val) return -1;
  
  size_t idx = hash(key,table->capacity);
  for (int i = 0;i < table->capacity; i++) {
    size_t real_idx = (idx+i) % table->capacity;
    kv_entry_t *entry = &table->entries[real_idx];

    //the key is already set, updating
    if (entry->key && 
      entry->key != (void*)TOMBSTONE &&
      !strcmp(entry->key, key)) {
        char *newval = strdup(val);
        if (!newval) return -1;
        entry->value = newval;
        return 0;
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
        return 0;
   } 
  }
  return -2;
}

char *kv_get(kv_t *table, char *key){
  if (!table || !key) return NULL;
  
  size_t idx = hash(key,table->capacity);
  for (int i = 0;i < table->capacity; i++) {
    size_t real_idx = (idx+i) % table->capacity;
    kv_entry_t *entry = &table->entries[real_idx];
    
    if (entry->key == NULL) return NULL;
    
    if (entry->key && entry->key != TOMBSTONE && !strcmp(entry->key, key)) {
      return entry->value;
    }
  }
  return NULL;
}

int kv_delete(kv_t *table, char *key){
  if (!table || !key) return -1;
  
  size_t idx = hash(key,table->capacity);

  for (int i = 0;i < table->capacity; i++) {
    size_t real_idx = (idx+i) % table->capacity;
    
    kv_entry_t *entry = &table->entries[real_idx];
    
    if (entry->key == NULL || key) return 0;
    
    if (entry->key && entry->key != TOMBSTONE && !strcmp(entry->key, key)) {
      free(entry->value);
      free(entry->key);
      table->count = 1;
      printf("%ld\n",table->count);
      entry->key = TOMBSTONE;
      entry->value = NULL;
      return 0;
    }
  }
  return -1;
}

