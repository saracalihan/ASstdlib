#pragma once
#include "Assertions.hpp"
#include "Logger.hpp"
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <vector>

#define ASSTDLIB_DEFAULT_VECTOR_SIZE 100
#define SIZE_T int

/*
    This macros uses for basic implemantation with std::vector.
    On own implemantation, they will delete
*/
#define ITARATOR_T void
#define VECTOR_IMPL_TYPE(T) std::vector<T>

FIXME("vector_size default should be changeable")
template <typename T, unsigned int vector_size = ASSTDLIB_DEFAULT_VECTOR_SIZE>
class Vector {
private:
  VECTOR_IMPL_TYPE(T) m_data = {};

public:
  VECTOR_IMPL_TYPE(T) getContainer() { return m_data; }
  T at(SIZE_T index) { return m_data.at(index); }
  // T friend [int index]{}
  T first() {
    if (0 == size()) {
      throw std::runtime_error("Vector is empty!");
    }
    return m_data.front();
  }
  T last() {
    if (0 == size()) {
      throw std::runtime_error("Vector is empty!");
    }
    return m_data.back();
  }
  bool is_empty() { return size() == 0; }
  SIZE_T size() { return m_data.size(); }
  SIZE_T capacity() { return m_data.capacity(); }
  SIZE_T clear() {
    SIZE_T s = size();
    m_data.clear();
    if (m_data.size() != 0) {
      return -1;
    }
    return s;
  }
  ITARATOR_T emplace(SIZE_T to, T data) { return m_data.emplace(to, data); }
  ITARATOR_T emplace_back(SIZE_T to, T data) {
    return m_data.emplace_back(to, data);
  }
  ITARATOR_T push(T data) { return m_data.push_back(data); }
  ITARATOR_T remove(SIZE_T index) { m_data.erase(m_data.begin() + index); }
  ITARATOR_T remove(SIZE_T first, SIZE_T step) {
    auto begin = m_data.begin();
    m_data.erase(begin + first, begin + first + step);
  }
  T pop() {
    T data = last();
    m_data.pop_back();
    return data;
  }
  void resize(SIZE_T size) { return m_data.resize(size); }
  void swap(Vector<T, vector_size> other) { return m_data.swap(other); }
  bool operator==(Vector<T, vector_size> &other) {
    try {
      for (SIZE_T i = 0; i < other.size(); i++) {
        if (at(i) != other.at(i)) {
          return false;
        }
      }
    } catch (exception) {
      return false;
    }

    return true;
  }
  bool operator!=(Vector<T, vector_size> &other) { return !(*this == other);}
  bool operator=(const Vector<T, vector_size> &other) { NOT_IMPLEMENTED; }
  T operator[](SIZE_T index) { return at(index); }
};