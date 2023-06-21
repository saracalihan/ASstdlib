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

#define ERROR(m) cerr<< "[ ERROR ]: "<<m<<"\n"<<__func__ <<":"<<__LINE__<< " at "<<__FILE__<<"\n";

#ifdef ASSTD_TODO
    #define TODO(message) cout<< "[ TODO ]: "<< message << " at "  __FILE__<<"/"<< __func__ << "():" << __LINE__ << "\n";
#else
    #define TODO(message)
#endif

#ifdef ASSTD_FIXME
    #define FIXME(message) cout<< "[ FIXME ]: "<< message << " at "  __FILE__<<"/"<< __func__ << "():" << __LINE__ << "\n";
#else
    #define FIXME(message)
#endif
