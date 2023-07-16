/*
 * Copyright (c) 2023, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more
 * detail.
 */

#include "Logger.hpp"
#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
namespace ASstdlib {
template <typename T> class LinkedListNode {
private:
  T m_value;
  LinkedListNode<T> *m_next;

public:
  LinkedListNode<T>(T v) : m_value(v), m_next(nullptr){};
  T value() { return m_value; }
  void value(T data) { m_value = data; }
  LinkedListNode<T> &next_node() { return *m_next; }
  LinkedListNode<T> &next_node(LinkedListNode<T> &n) {
    m_next = &n;
    return n;
  }
  LinkedListNode<T> &next_node(T n) {
    m_next = new LinkedListNode<T>(n);
    return *m_next;
  }
  void remove_next_node() { m_next = nullptr; }
};

template <typename T> class LinkedListIterator {
private:
  LinkedListNode<T> *m_node;

public:
  LinkedListIterator<T>() : m_node(nullptr){};
  LinkedListIterator<T>(T value) { m_node = new LinkedListNode<T>(value); };
  LinkedListIterator<T>(LinkedListNode<T> &node) : m_node(&node){};
  LinkedListIterator<T> &operator++() {
    m_node = m_node->next_node();
    return *this;
  }
  LinkedListNode<T> &next_node() { return m_node->next_node(); }
  void next() {
    if (nullptr == &(next_node())) {
      return;
    }
    m_node = &next_node();
    return;
  }
  LinkedListNode<T> &node() { return *m_node; }
  T value() { return m_node->value(); }
  void value(T v) { m_node->value(v); }
  bool is_last() { return nullptr == &(m_node->next_node()); }
};

template <typename T> class LinkedList {
private:
  LinkedListNode<T> *m_head = nullptr;
  LinkedListNode<T> *m_tail = nullptr;
  unsigned int m_size = 0;

public:
  LinkedList<T>(){};
  LinkedList<T>(T value) { m_head = new LinkedListNode<T>(value); }
  LinkedList<T>(LinkedListNode<T> h) : m_head(&h) {}
  unsigned int size() { return m_size; }
  void append(T v) {
    LinkedListNode<T> *node = new LinkedListNode<T>(v);
    m_tail = node;
    m_size++;
    if (!m_head) {
      m_head = node;
      return;
    }
    LinkedListIterator<T> itr = LinkedListIterator<T>(*m_head);
    while (!itr.is_last()) {
      itr.next();
    }
    itr.node().next_node(*node);
  }
  LinkedListIterator<T> begin() { return *m_head; }
  LinkedListIterator<T> end() { return *m_tail; }
  T &first() { return m_head->value(); }

  T &last() { return m_tail->value(); }

  void remove(int index) {
    if (index > m_size || index < 0) {
      throw std::range_error(
          "Index can not greater then list size or less then zero!");
    }
    m_size--;
    if (0 == index) {
      LinkedListNode<T> *tmp = m_head;
      m_head = &(m_head->next_node());
      delete tmp;
      return;
    }
    LinkedListIterator<T> itr = LinkedListIterator<T>(*m_head);
    LinkedListNode<T> *prev = m_head;
    while (--index > -1) {
      prev = &(itr.node());
      itr.next();
    }
    prev->next_node(itr.next_node());
    delete &(itr.node());
  }

  T at(int index) {
    if (index >= m_size) {
      throw std::range_error("Index can not greater then list size!");
    }
    LinkedListIterator<T> itr = LinkedListIterator<T>(*m_head);
    if (0 == index) {
      return m_head->value();
    }
    while (--index >= 0) {
      itr.next();
    }
    return itr.value();
  }

  LinkedListIterator<T> find(T value) {
    LinkedListIterator<T> *itr = new LinkedListIterator<T>(*m_head);
    while (!itr->is_last() && value != itr->value()) {
      itr->next();
    }

    if (value == itr->value()) {
      return *itr;
    }
    throw std::runtime_error("List doesnt include this item");
  }
};
} // namespace ASstdlib
