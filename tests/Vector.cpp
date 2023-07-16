#include "../Vector.hpp"
#include "../Test.hpp"
#include <exception>

#define Vector1 Vector<int, 300>

int main() {
  Tests({
    Describe("push()", {
      Test("client should push successfuly when type is correct", {
        Vector<int> v;
        v.push(15);
        v.push(20);
        auto container = v.getContainer();
        return container.at(0) == 15 && container.at(1) == 20;
      });
    });
    Describe("size()", {
      Test("client should get size of vector when vector is not empty", {
        Vector<int> v;
        v.push(15);
        v.push(15);
        v.push(20);
        return v.size() == 3;
      });
      Test("client should get 0 when vector is empty", {
        Vector<int> v;
        return v.size() == 0;
      });
    });
    // FIXME: pass vector size to container.
    // Describe("capacity()", {
    //   Test("client should get default vector capacity when capacity doesnt
    //   pass to the ctor", {
    //     Vector<int> v;
    //     return v.capacity() == ASSTDLIB_DEFAULT_VECTOR_SIZE;
    //   });
    //   Test("Client should choose vector capacity", {
    //     Vector1 v;
    //     return v.size() == 0;
    //   });
    // });
    Describe("at()", {
      Test("client should get data if vechor has data that index ", {
        Vector<int> v;
        v.push(15);
        v.push(20);
        v.push(30);
        return v.at(0) == 15 && v.at(1) == 20 && v.at(2) == 30;
      });
      Test("client should get exception when index is out of range", {
        Vector<int> v;
        v.push(15);
        v.push(20);
        v.push(30);
        bool underRange = false;
        bool overRange = false;
        try {
          std::cout << v.at(5);
        } catch (std::exception e) {
          overRange = true;
        }
        try {
          std::cout << v.at(-10);
        } catch (std::exception e) {
          underRange = true;
        }
        return underRange && overRange;
      });
    });
    Describe("pop()", {
      Test("client get data when vector is not empty", {
        Vector<int> v;
        v.push(10);
        v.push(20);
        return v.pop() == 20 && v.size() == 1;
      });
    });
    Describe("first()", {
      Test("client should get first data if vector is not empty", {
        Vector<int> v;
        v.push(15);
        v.push(20);
        v.push(30);
        return v.first() == 15;
      });
      Test("client should get exception when vector is empty", {
        Vector<int> v;
        try {
          v.first();
        } catch (std::exception) {
          return true;
        }
        return false;
      });
    });
    Describe("last()", {
      Test("client should get last data if vector is not empty", {
        Vector<int> v;
        v.push(15);
        v.push(20);
        v.push(30);
        return v.last() == 30;
      });
      Test("client should get exception when vector is empty", {
        Vector<int> v;
        try {
          v.last();
        } catch (std::exception) {
          return true;
        }
        return false;
      });
    });
    Describe("is_empty()", {
      Test("client should get false when vector is not empty", {
        Vector<int> v;
        v.push(15);
        v.push(20);
        v.push(30);
        return !v.is_empty();
      });
      Test("client should get true when vector is empty", {
        Vector<int> v;
        return v.is_empty();
      });
    });
    Describe("clear()", {
      Test("client should get deleted item count", {
        Vector<int> v;
        Vector<int> v2;
        v.push(15);
        v.push(20);
        v.push(30);
        return v.clear() == 3 && v2.clear() == 0;
      });
    });
    Describe("remove()", {
      Test("client should erase with correct index", {
        Vector<int> v;
        v.push(10);
        v.push(20);
        v.push(30);
        v.push(40);
        v.remove(2);
        return v.size() == 3 && v.at(1) == 20 && v.at(2) == 40;
      });
      Test("client should erase with range", {
        Vector<int> v;
        v.push(10);
        v.push(20);
        v.push(30);
        v.push(40);
        v.remove(1, 2);
        return v.size() == 2 && v.at(0) == 10 && v.at(1) == 40;
      });
    });
    Describe("OPERATORS", {
      Test("== operator return true when vectors have same data and order", {
        Vector<int> v1;
        Vector<int> v2;

        v1.push(1);
        v1.push(2);
        v1.push(3);
        v1.push(4);

        v2.push(1);
        v2.push(2);
        v2.push(3);
        v2.push(4);

        return v1 == v2;
      });
      Test("== operator return false when vectors have not same data or order",
           {
             Vector<int> v1;
             Vector<int> v2;

             v1.push(1);
             v1.push(2);
             v1.push(4);

             v2.push(1);
             v2.push(2);
             v2.push(3);
             v2.push(4);

             return !(v1 == v2);
           });
      Test("!= operator return false when vectors have same data and order", {
        Vector<int> v1;
        Vector<int> v2;

        v1.push(1);
        v1.push(2);
        v1.push(3);
        v1.push(4);

        v2.push(1);
        v2.push(2);
        v2.push(3);
        v2.push(4);

        return !(v1 != v2);
      });
      Test("!= operator return true when vectors have not same data and order",
           {
             Vector<int> v1;
             Vector<int> v2;

             v1.push(1);
             v1.push(4);

             v2.push(1);
             v2.push(2);
             v2.push(3);
             v2.push(4);

             return v1 != v2;
           });
    });
    Test("[] operator return value when index is not empty", {
      Vector<int> v1;

      v1.push(1);
      v1.push(4);
      v1.push(3);
      return v1[1] == 4;
    });

    Test("[] operator throw exception when index is incorrect", {
      Vector<int> v1;

      v1.push(1);
      v1.push(4);
      v1.push(3);

      bool isCatched = false;
      try {
        v1[25];
      } catch (exception) {
        isCatched = true;
      }
      return isCatched;
    });
  });
  return 0;
}
