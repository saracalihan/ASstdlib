/*
 * Copyright (c) 2023, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more
 * detail.
 */

#include "../StringView.hpp"
#include "../Test.hpp"
#include "../Logger.hpp"
#include <exception>

using namespace ASstdlib;

int main() {

  Tests({
    Describe(
        "ctor()",
        {Test("Client should get new object successfully without passing "
              "paramater",
              {
                StringView *s = new StringView();
                return s->to_string() == "";
              }) Test("Client should get new object successfully with char*",
                      {
                        char *c = "Hello world!";
                        StringView *s = new StringView(c);
                        return s->to_string() == "Hello world!";
                      })

             Test("Client should get new object successfully with string", {
               string c = "Hello world!";
               StringView *s = new StringView(c);
               return s->to_string() == "Hello world!";
             })});

    Describe("to_string()", {
      Test("client should get empty string when its empty", {
        StringView s = StringView();
        return s.to_string() == "";
      });
      Test("client should get correct string", {
        StringView s = StringView("hello world! ");
        return s.to_string() == "hello world! ";
      });
    });

    Describe("length()", {Test("Client should get 0 when string is empty", {
               StringView *s = new StringView();
               return s->length() == 0;
             }) Test("Client should get correct length", {
               StringView *s = new StringView("hello! ");
               return s->length() == 7;
             })});

    Describe("append()", {
      Test("", {
        StringView s = StringView("hello");
        StringView s2 = s.append('a');
        return s2.to_string() == "helloa";
      });
    });

    Describe("clear()", {
      Test("client should get empty string when its not empty", {
        StringView s = StringView("hello");
        StringView s2 = s.clear();
        return s2.to_string() == "";
      });
    });

    Describe("erases()", {
      Test("client should erase string successfuly with correct range", {
        StringView s = StringView("hello world! ");
        return s.erases(1, 4).to_string() == "h world! ";
      });
      Test("throw error when erase range is incorrect", {
        StringView s = StringView("hello world! ");
        bool isThrowed = false;
        try {
          s.erases(15, 4).to_string();
        } catch (exception e) {
          isThrowed = true;
        }

        return isThrowed;
      });
    });

    Describe("indexOf()", {
      Test("client should get index when string match", {
        StringView s = StringView("hello world! ");
        return s.indexOf('!') == 11;
      });
      Test("client should get index when string found", {
        StringView s = StringView("hello world! ");
        return s.indexOf(" wo") == 5;
      });
      Test("client should get index when StringView found", {
        StringView s = StringView("hello world! ");
        return s.indexOf(StringView("rld")) == 8;
      });
      Test("client should get -1 when character not found", {
        StringView s = StringView("hello world! ");
        return s.indexOf('X') == -1;
      });
      Test("client should get index when string match after start index", {
        StringView s = StringView("hello world! ");
        return s.indexOf('o', 5) == 7;
      });
      Test("client should get -1 when string dont match after start index", {
        StringView s = StringView("hello world! ");
        return s.indexOf('e', 5) == -1;
      });
    });

    Describe("Operators", {
      Test("* operator is concat string given times then return it",{
        StringView s = StringView("a ");
        return s * 3 == "a a a ";
      });
      Test("* operator should return '' when paramater is 0",{
        StringView s = StringView("a ");
        return s * 0 == "";
      });
      Test("*= operator is multiply string given times then assagin itself",{
        StringView s = StringView("a ");
        s *=3;
        return s== "a a a ";
      });
    });
  });
  return 0;
}