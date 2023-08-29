/*
 * Copyright (c) 2023, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more
 * detail.
 */

#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <cstdio>

using namespace std;


const char *to_string(const char *&c) { return (c); }

const char *to_string(char c) {
  char *cp = (char *)malloc(sizeof(char));
  *cp = c;
  return cp;
}

string str;

int getIndexOfBrickets(string format) {
  if (format.find('{') + 1 != format.find('}')) {
    return -1;
  }
  return format.find('{');
}

template <class T> void formatVariadicString(T a) {
  int indexOfBrickets = getIndexOfBrickets(str);
  if (indexOfBrickets == -1) {
    return;
  }
  str = str.replace(indexOfBrickets, 2, to_string(a));
}

template <class T, class... Args> void formatVariadicString(T a, Args... args) {
  int indexOfBrickets = getIndexOfBrickets(str);
  if (indexOfBrickets == -1) {
    return;
  }
  str = str.replace(indexOfBrickets, 2, to_string(a));
  formatVariadicString(args...);
}

template <class T, class... Args> void println(T format, Args... args) {
  if (getIndexOfBrickets(format) == -1) { // if {} not exist
    cout << format << endl;
    return;
  }
  str += format;
  formatVariadicString(args...);

  std::cout << str << std::endl;
  str = "";
}

template <class T, class... Args> void LOG(T format, Args... args) {
  string tag = "[INFO]: ";
  println(tag + (char *)format, args...);
}
template <class T> void LOG(T format) {
  string tag = "[INFO]: ";
  println(tag + (char *)format, "{}");
}
/*
#define LOG(args...) println(args);
#define DEBUG(...) println(string("[DEBUG]: ")+ __VA_ARGS__)
#define ERROR(...) println((string("[DEBUG]: ") __func__ + ":" +__LINE__ + " at " + __FILE__) + __VA_ARGS__)
*/
#ifdef ASSTD_TODO
#define TODO(message)                                                          \
  cout << "[ TODO ]: " << message << " at " __FILE__ << "/" << __func__        \
       << "():" << __LINE__ << "\n";
#else
#define TODO(message)
#endif

#ifdef ASSTD_FIXME
#define FIXME(message)                                                         \
  cout << "[ FIXME ]: " << message << " at " __FILE__ << "/" << __func__       \
       << "():" << __LINE__ << "\n";
#else
#define FIXME(message)
#endif
