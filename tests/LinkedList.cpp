/*
 * Copyright (c) 2023, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more
 * detail.
 */

#include "../LinkedList.hpp"
#include "../Test.hpp"

using namespace ASstdlib;

int main() {
  Tests({
    Describe("LinkedListNode", {
      Test("value()", {
        LinkedListNode<int> l = LinkedListNode<int>(15);
        return l.value() == 15;
      });
      Test("next_node() get null when node doesnt have a next node", {
        LinkedListNode<int> l = LinkedListNode<int>(15);
        return &(l.next_node()) == nullptr;
      });
      Test("next_node(T) return node when have a next", {
        LinkedListNode<int> l = LinkedListNode<int>(15);
        return l.next_node(20).value() == 20;
      });
      Test("next_node(LinkedListNode<T>) return node when have a next", {
        LinkedListNode<int> l = LinkedListNode<int>(15);
        LinkedListNode<int> l2 = LinkedListNode<int>(20);
        return l.next_node(l2).value() == 20;
      });
      Test("remove_next_node() set null to m_next when next node is not null", {
        LinkedListNode<int> l = LinkedListNode<int>(15);
        LinkedListNode<int> *l2 = &l.next_node(20);
        bool isSameAddress = &(l.next_node()) == l2;
        l.remove_next_node();
        return isSameAddress && &(l.next_node()) == nullptr;
      });
    });
    Describe("LinkedListItarator", {
      Test("value()", {
        LinkedListIterator<int> l = LinkedListIterator<int>(15);
        return l.value() == 15;
      });
      Test("node()", {
        LinkedListIterator<int> l = LinkedListIterator<int>(15);
        return l.node().value() == 15;
      });
      Test("next_node()", {
        LinkedListNode<int> n = LinkedListNode<int>(15);
        n.next_node(20).next_node(30);
        LinkedListIterator<int> l = LinkedListIterator<int>(n);
        return l.value() == 15 && l.next_node().value() == 20 &&
               l.next_node().next_node().value() == 30;
      });
      Test("next() should return nullptr when node doesnt have a next", {
        LinkedListIterator<int> l = LinkedListIterator<int>(12);
        return l.is_last();
      });
      Test("next()", {
        LinkedListNode<int> n = LinkedListNode<int>(15);
        n.next_node(20).next_node(30);
        LinkedListIterator<int> l = LinkedListIterator<int>(n);
        int v1 = l.value();
        l.next();
        int v2 = l.value();
        l.next();
        int v3 = l.value();
        return 15 == v1 && 20 == v2 && 30 == v3;
      });
      Test("next() do nothing when node doesnt have a next", {
        LinkedListIterator<int> l = LinkedListIterator<int>(12);
        l.next();
        return l.value() == 12 && l.is_last();
      });
      Test("is_last()", {
        LinkedListNode<int> n = LinkedListNode<int>(15);
        n.next_node(20);
        LinkedListIterator<int> l = LinkedListIterator<int>(n);
        bool c1 = l.is_last() == false;
        l.next();
        bool c2 = l.is_last() == true;
        return c1 && c2;
      });
    });
    Describe("LinkedList", {
      Test("append()", {
        LinkedList<int> l;
        l.append(10);
        l.append(20);
        l.append(30);
        return l.size() == 3 && 10 == l.begin().value() &&
               20 == l.begin().next_node().value() &&
               30 == l.begin().next_node().next_node().value();
      });
      Test("at()", {
        LinkedList<int> l;
        l.append(10);
        l.append(20);
        l.append(30);
        return 10 == l.at(0) && 20 == l.at(1) && 30 == l.at(2);
      });
      Test("remove()", {
        LinkedList<int> l;
        l.append(10);
        l.append(20);
        l.append(30);
        l.append(40);
        l.remove(2);
        return 3 == l.size() && 10 == l.at(0) && 20 == l.at(1) && 40 == l.at(2);
      });

      Test("find()", {
        LinkedList<int> l;
        l.append(10);
        l.append(20);
        l.append(30);
        l.append(40);
        return &(l.find(30).node()) == &(l.begin().next_node().next_node());
      });
    });
  });
}
