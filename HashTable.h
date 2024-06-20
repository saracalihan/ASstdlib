#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "da.h"

#define HASHTABLE_KEY_LENGTH 265
typedef int hashtable_type;

/*
  Basicly hashtable structure

  HashTable
    count
    capacity
    items
      {
        pair
          {key, value}
        nexts
          {{key, value}, {key, value}, ...}
      }
*/

typedef struct{
    char key[HASHTABLE_KEY_LENGTH];
    hashtable_type value;
} Pair;

// We use dynamic array, not linked list for support full CPU cache
typedef struct {
    Pair* items;
    size_t count;
    size_t capacity;
}HashTableNextList;

typedef struct{
    Pair pair;
    HashTableNextList nexts;
} HashTableNode;

typedef struct{
    HashTableNode *items;
    size_t count;
    size_t capacity;
    size_t element_count;
} HashTable;

void hashtable_free(HashTable* table){
    for(size_t i=0; i< table->count;i++){
        HashTableNode *node = table->items;

        while(node->nexts.count>0){
            free(node->nexts.items);
        }
    }
    free(table->items);
    table->items=NULL;
}

HashTable hashtable_create(size_t size){
    HashTable table = {0};
    DA_INIT(table, size);
    memset(table.items, 0, sizeof(HashTableNode)*size);
    return table;
}

size_t hashtable_hash(const char* key){
    size_t hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

size_t hashtable_add(HashTable *table, const char* key, hashtable_type value){
    if(table->capacity < table->count +1 ){
        // realloc table then rehash all elements
        HashTable temp = hashtable_create(table->capacity *2);

        while(table->count>0){
            HashTableNode itr=DA_POP(*table);

            if(itr.pair.key[0]!='\0'){ // reassign value
                hashtable_add(&temp, itr.pair.key, itr.pair.value);

                for(size_t j=0; j<itr.nexts.count; j++){ // reassign nexts
                    hashtable_add(&temp, itr.nexts.items[j].key, itr.nexts.items[j].value);
                }
            }
        }
        hashtable_free(table);
        memcpy(table, &temp, sizeof(HashTable));
    }

    size_t hash = hashtable_hash(key) % table->capacity;
    Pair var = (Pair){
                .key = {0},
                .value = value
    };
    strcpy(var.key, key);

    if(table->items[hash].pair.key[0]=='\0'){ // if node is avaible
        table->items[hash] = (HashTableNode){
            .pair = var,
            .nexts = {0}
        };
        table->count++;
    } else{
        DA_PUSH(table->items[hash].nexts, var);
    }
    table->element_count++;
    return hash;
}

Pair* hashtable_get(const HashTable *table, const char* key){
    size_t hash = hashtable_hash(key) % table->capacity;
    HashTableNode *root_node = &table->items[hash];
    if(strcmp(root_node->pair.key, key) == 0){
        return &root_node->pair;
    }

    size_t index =0;
    while(index < root_node->nexts.count){
        Pair* var = &DA_GET(root_node->nexts, index);
        if (strcmp(var->key, key) == 0) {
            return var;
        }
        index++;
    }
    return NULL;
}

void hashtable_delete(HashTable *table, const char* key){
    Pair *var = hashtable_get(table, key);
    if(NULL == var){
        return;
    }
    memset(var, 0, sizeof(Pair));
    table->element_count--;
}

void hashtable_set(HashTable *table, const char* key, const hashtable_type value){
    Pair* var = hashtable_get(table, key);
    if(NULL == var){
        return;
    }
    memcpy(&var->value, &value, sizeof(value));
}

#endif // HASHTABLE_H
