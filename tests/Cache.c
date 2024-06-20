#include "../Cache.h"
#include "../Test.h"
int main(){

// Test fonksiyonları
Tests({
    Describe("Cache Creation", {
        Test("Create a cache with LRU strategy and capacity 3", {
            Cache c = cache_create(LRU, 3);
            c.strategy == LRU && c.capacity == 3 && c.count == 0; // return value
        });
    });

    Describe("Cache Operations", {
        Cache c = cache_create(LRU, 3);
        hashtable_type data1 = 100;
        hashtable_type data2 = 200;
        hashtable_type data3 = 300;
        hashtable_type data4 = 400;

        Test("Add data to cache", {
            cache_put(&c, "key1", data1) == 1 &&
            cache_put(&c, "key2", data2) == 2 &&
            cache_put(&c, "key3", data3) == 3; // return value
        });

        Test("Retrieve data from cache", {
            *cache_get(&c, "key1") == 100 &&
            *cache_get(&c, "key2") == 200 &&
            *cache_get(&c, "key3") == 300; // return value
        });

        Test("Add data to full cache", {
            cache_put(&c, "key4", data4) == 3 && // should remove least recently used (key1)
            cache_get(&c, "key1") == NULL &&
            *cache_get(&c, "key4") == 400; // return value
        });

        Test("Remove data from cache", {
            cache_remove(&c, "key2") == 2 && // should remove key2
            cache_get(&c, "key2") == NULL &&
            c.count == 2; // return value
        });
    });
});
return 0;
}