#include "../HashTable.h"
#include "../Test.h"
#include<stdio.h>
int main(){
    Tests({
        Describe("Hashtable Creation", {
            Test("Create a hashtable with initial capacity 3", {
                HashTable table = hashtable_create(3);
                table.capacity == 3 && table.count == 0; // return value
            });
        });

        Describe("Hashtable Operations", {
            HashTable table = hashtable_create(3);

            Test("Add elements to the hashtable", {
                hashtable_add(&table, "key1", 100) == hashtable_hash("key1") % table.capacity &&
                hashtable_add(&table, "key2", 200) == hashtable_hash("key2") % table.capacity &&
                hashtable_add(&table, "key3", 300) == hashtable_hash("key3") % table.capacity; // return value
            });

            Test("Retrieve elements from the hashtable", {
                Pair *p1 = hashtable_get(&table, "key1");
                Pair *p2 = hashtable_get(&table, "key2");
                Pair *p3 = hashtable_get(&table, "key3");
                p1 != NULL && p1->value == 100 &&
                p2 != NULL && p2->value == 200 &&
                p3 != NULL && p3->value == 300; // return value
            });

            Test("Update an element in the hashtable", {
                hashtable_set(&table, "key2", 250);
                Pair *p = hashtable_get(&table, "key2");
                p != NULL && p->value == 250; // return value
            });

            Test("Delete an element from the hashtable", {
                hashtable_delete(&table, "key2");
                hashtable_get(&table, "key2") == NULL; // return value
            });

            Test("Handle collisions in the hashtable", {
                // Adding keys that would result in the same hash
                hashtable_add(&table, "key1", 100);
                hashtable_add(&table, "key2", 200);
                hashtable_add(&table, "key3", 300);
                hashtable_add(&table, "key4", 400); // Assume this collides with key1

                Pair *p1 = hashtable_get(&table, "key1");
                Pair *p4 = hashtable_get(&table, "key4");
                p1 != NULL && p1->value == 100 &&
                p4 != NULL && p4->value == 400; // return value
            });
              Test("Retrieve non-existent key", {
                Pair *p = hashtable_get(&table, "non_existent_key");
                p == NULL; // return value
            });

            Test("Delete non-existent key", {
                hashtable_delete(&table, "non_existent_key");
                // No crash or error expected
                true; // return value
            });

            Test("Update non-existent key", {
                hashtable_set(&table, "non_existent_key", 999);
                // This should not crash but also should not add the key
                Pair *p = hashtable_get(&table, "non_existent_key");
                p == NULL; // return value
            });

            Test("Add a large number of elements", {
                HashTable lt = hashtable_create(1000);
                for (int i = 0; i < 1000; ++i) {
                    char key[20];
                    snprintf(key, sizeof(key), "large_key_%d", i);
                    hashtable_add(&lt, key, i);
                }

                bool all_found = true;
                for (int i = 0; i < 1000; ++i) {
                    char key[20];
                    snprintf(key, sizeof(key), "large_key_%d", i);
                    Pair *p = hashtable_get(&lt, key);
                    if (p == NULL || p->value != i) {
                        all_found = false;
                        break;
                    }
                }
                bool ret = all_found && lt.element_count == 1000;
                hashtable_free(&lt);
                ret;
            });

            Test("Free hashtable", {
                hashtable_free(&table);
                table.items == NULL;
            });
        });
    });
return 0;
}