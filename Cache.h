// Currently, the cache changes the location of the elements as the operation is performed, regardless of the read or write operation, rather than the cache read operation.

#ifndef CACHE_H
#define CACHE_H

#include "HashTable.h"

#include <string.h>
#include <stdlib.h>

typedef enum {
    MRU,
    LRU,
} CacheStrategy;

typedef struct CacheNode {
    char key[HASHTABLE_KEY_LENGTH];
    size_t read;
    size_t write;
    struct CacheNode* next;
    struct CacheNode* prev;
} CacheNode;

typedef struct {
    HashTable hashtable;
    CacheStrategy strategy;
    CacheNode* head;
    CacheNode* tail;
    size_t capacity;
    size_t count;
} Cache;

static inline CacheNode* cachenode_find(Cache* c, const char* key) {
    CacheNode* itr = c->head;
    while (itr != NULL) {
        if (strcmp(itr->key, key) == 0) {
            return itr;
        }
        itr = itr->next;
    }
    return NULL;
}

static inline void cache_remove_node(Cache* c, CacheNode* node) {
    if (node != NULL) {
        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else {
            c->head = node->next;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        } else {
            c->tail = node->prev;
        }
        free(node);
        c->count--;
    }
}

static inline CacheNode* cache_move_node_to_head(Cache* c, CacheNode* node) {
    if (node == NULL) {
        return NULL;
    }
    size_t r = node->read, w = node->write;
    char key[HASHTABLE_KEY_LENGTH];
    strcpy(key, node->key);

    // Remove node
    cache_remove_node(c, node);

    // Add node to head
    node = malloc(sizeof(CacheNode));
    memset(node, 0, sizeof(CacheNode));
    strcpy(node->key, key);
    node->read = r;
    node->write = w;
    node->next = c->head;
    if (c->head != NULL) {
        c->head->prev = node;
    }
    c->head = node;
    if (c->tail == NULL) {
        c->tail = node;
    }
    c->count++;

    return node;
}

static inline CacheNode* cache_add_node_to_head(Cache* c, const char* key) {
    CacheNode* node = malloc(sizeof(CacheNode));
    memset(node, 0, sizeof(CacheNode));
    strcpy(node->key, key);
    node->next = c->head;
    if (c->head != NULL) {
        c->head->prev = node;
    }
    c->head = node;
    if (c->tail == NULL) {
        c->tail = node;
    }
    c->count++;
    return node;
}

Cache cache_create(CacheStrategy strategy, size_t cap) {
    Cache c = {0};
    c.capacity = cap;
    c.strategy = strategy;
    c.hashtable = hashtable_create(cap);
    return c;
}

size_t cache_put(Cache* c, const char* key, hashtable_type data) {
    // Add data to hashtable
    CacheNode* node = cachenode_find(c, key);
    if(NULL==node){
        hashtable_add(&c->hashtable, key, data);
    } else{
        hashtable_set(&c->hashtable, key, data);
    }

    // Update usage list
    switch (c->strategy) {
        case MRU:
            // Not implemented
            break;
        case LRU:
        default:
            if (node == NULL) {
                // Remove least recent element if needed
                if (c->count == c->capacity) {
                    cache_remove_node(c, c->tail);
                }
                node = cache_add_node_to_head(c, key);
            } else {
                // Move node to head
                node = cache_move_node_to_head(c, node);
            }
            node->write++;
            break;
    }
    return c->count;
}

hashtable_type* cache_get(Cache* c, const char* key) {
    Pair* data = hashtable_get(&c->hashtable, key);
    if (data == NULL) {
        return NULL;
    }
    CacheNode* node = cachenode_find(c, key);
    if(NULL == node){
        return NULL;
    } else{
        node->read++;
        cache_move_node_to_head(c, node);
    }

    return &data->value;
}

size_t cache_remove(Cache* c, const char* key) {
    hashtable_delete(&c->hashtable, key);
    CacheNode* node = cachenode_find(c, key);

    if (node == NULL) {
        return 0;
    }

    cache_remove_node(c, node);
    return c->count;
}

#endif // CACHE_H
