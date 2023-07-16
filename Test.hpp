/*
 * Copyright (c) 2023, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more detail.
 */

#pragma once
#include <iostream>
#define TAB_CHAR "  "
#ifndef ASSTDLIB_EXIT_WHEN_TEST_FAIL
#define ASSTDLIB_EXIT_WHEN_TEST_FAIL 0
#endif

inline bool status = false;
inline int groupCount = 0, testCount = 0, passedTest = 0, failedTest = 0;

#define Tests(body)                                                            \
  {                                                                            \
    groupCount = 0, testCount = 0, passedTest = 0, failedTest = 0;             \
    [] body();                                                                 \
    printf("\nTests: \x1B[32m%d passed\033[0m, \x1B[31m%d failed\033[0m, %d total\nGroups: %d\n%s\n\n",      \
           passedTest, failedTest, testCount, groupCount, __FILE__);           \
    if (ASSTDLIB_EXIT_WHEN_TEST_FAIL && failedTest != 0)                       \
      exit(1);                                                                 \
  };

#define Describe(label, body)                                                  \
  groupCount++;                                                                \
  std::cout << std::endl << "\x1B[1m" << label << "\033[0m:" << std::endl;     \
  [] body()

#define Test(label, body)                                                      \
  testCount++;                                                                 \
  std::cout << TAB_CHAR << "\033[3;43;30m RUNNING \033[0m \033[3m" << label    \
            << "\033[0m" << std::endl;                                         \
  status = []() -> bool body();                                                \
  std::cout << TAB_CHAR                                                        \
            << (status ? "   \033[1;42;37m PASS \033[0m"                          \
                       : "   \033[1;41;37m FAIL \033[0m")                         \
            << std::endl;                                                      \
  status ? passedTest++ : failedTest++;
