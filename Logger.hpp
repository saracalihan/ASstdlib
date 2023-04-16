#pragma once
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

template <typename... Param>
void LOG(std::string message, Param const &...values) {
  // FIXME: std::format @ c++20
  cout << "message: " << message << endl;
  // //   (std::cout << ... << values) << "\n";
  //     auto f = [&, ...values](auto a){
  //         cout << "f:"<< a <<endl;
  //     };
  // tipi bul
  // formatlanacak stingi üret
  // formatla
  // yazdır
}

void DEBUG(string message) { cout << message << endl; }

#define ERROR(m) cout<< "[ERROR] "<<m<<"\n"<<__func__ <<":"<<__LINE__<< " at "<<__FILE__<<"\n"
