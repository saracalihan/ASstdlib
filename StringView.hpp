/*
 * Copyright (c) 2023, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more detail.
 */

#pragma once
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <list>
#include <string>

using namespace std;
namespace ASstdlib {

class StringView {
private:
  string m_data;

public:
  StringView() { m_data = ""; }
  StringView(string value) : m_data(value) {}
  StringView(char *value) : m_data(value) {}
  StringView &append(char c) {
    m_data = m_data.append(1, c);
    return *(this);
  }

  string to_string() const { return m_data; }
  int length() { return m_data.length(); }
  StringView &clear() {
    m_data = "";
    return *this;
  }
  StringView erases(int start, int step) {
    return StringView(m_data.erase(start, step));
  }
  template <typename T> int indexOf(T c, int start) {
    return m_data.find(c, start);
  }

  int indexOf(StringView c, int start) {
    return m_data.find(c.to_string(), start);
  }

  template <typename T> int indexOf(T c) { return indexOf(c, 0); }

  StringView substr(int start, int step) {
    return StringView(m_data.substr(start, step));
  }

  bool is_empty() { return m_data == ""; }

  StringView pad_end(int size = 1) {
    char *spaces = (char *)malloc(sizeof(char) * size);
    memset(spaces, (int)' ', sizeof(char) * size);
    return StringView(m_data + spaces);
  }
  StringView pad_start(int size = 1) {
    char *spaces = (char *)malloc(sizeof(char) * size);
    memset(spaces, (int)' ', sizeof(char) * size);
    return StringView(spaces + m_data);
  }

  StringView to_upper() {
    StringView s = StringView();
    for (int x = 0; x < length(); x++)
      s.m_data += toupper((int)m_data[x]);
    return s;
  }

  StringView to_lower() {
    StringView s = StringView();
    for (int x = 0; x < length(); x++)
      s.m_data += tolower((int)m_data[x]);
    return s;
  }

  char at(int index) { return m_data[index]; }

  char start_with() { return m_data[0]; }

  char end_with() { return m_data[length() - 1]; }

  bool is_start_with(char c) { return m_data[0] == c; }

  bool is_end_with(char c) { return m_data[length() - 1] == c; }

  StringView trim_start() { return trim_start(length()); }
  StringView trim_start(int size) {
    int i = 0, len = length();
    while (i < size && i < len && at(i) == ' ') {
      i += 1;
    }
    return erases(0, i);
  }

  StringView trim_end() { return trim_end(length()); }
  StringView trim_end(int size) {
    int i = 0, len = length();
    while (i < size && i < len && at(len - i - 1) == ' ') {
      i += 1;
    }
    return erases(len - i, i);
  }

  StringView trim() { return trim_start().trim_end(); }
  StringView trim(int size) { return trim_start(size).trim_end(size); }

  StringView insert(int index, char c) {
    return StringView(substr(0, index).append(c) +
                      substr(index, length() - index));
  }

  // StringView insert(int index, StringView str) {
  //   return StringView(substr(0, index) + str +
  //                     substr(index + 1, length() - index - 1));
  // }

  // StringView insert(int index, char *str) {
  //   return insert(index, StringView(str));
  // }

  list<StringView> parse(char c) {
    list<StringView> list = {};
    int start = 0, index = 0;
    while (indexOf(c, start) != -1) {
      index = indexOf(c, start);
      StringView s = substr(start, index - start);
      list.push_back(s);
      start = index + 1;
    }
    // if chatacter doesnt found add all text else add last part of string.
    list.push_back(substr(start, length() - start));
    return list;
  }

  char operator[](size_t index) { return m_data[index]; }

  friend ostream &operator<<(ostream &Str, StringView const &v) {
    Str << v.m_data;
    return Str;
  }

  friend string operator+(StringView &s, string const &s2) {
    return s.m_data + s2;
  }
  friend string operator+(StringView &s, char const &s2) {
    return s.m_data + s2;
  }
  StringView operator+(StringView const &s) {
    return StringView(m_data + s.m_data);
  }

  StringView &operator=(char *const &v) {
    m_data = v;
    return *this;
  }

  StringView &operator=(StringView &v) {
    m_data = v.m_data;
    return *this;
  }

  StringView &operator+=(char *const &v) {
    m_data += v;
    return *this;
  }
  StringView &operator+=(string const &v) {
    m_data += v;
    return *this;
  }
  StringView &operator+=(StringView const &v) {
    m_data += v.m_data;
    return *this;
  }

  friend bool operator==(StringView const &s, StringView const &t) {
    return s.m_data == t.m_data;
  }
  friend bool operator==(StringView const &s, char *const t) {
    return s.m_data == t;
  }
  friend bool operator==(StringView const &s, string const &t) {
    return s.m_data == t;
  }

  friend bool operator!=(StringView const &s, StringView const &t) {
    return !(s == t);
  }
  friend bool operator!=(StringView const &s, char *const t) {
    return !(s == t);
  }
  friend bool operator!=(StringView const &s, string const &t) {
    return !(s == t);
  }
};
} // namespace ASstdlib
