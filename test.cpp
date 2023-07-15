#include <iostream>

#include "Logger.hpp"
#include "StringView.hpp"
#include "Assertions.hpp"
#include "VArg.h"
#include "Variant.h"

// void f(int ignore, ...){ 
//   va_list args;

//   FOR_EACH_VARG(args, "char", {
//     std::cout << std::arg << std::endl;
//   })
// }

int main() {
  // StringView s = StringView("   alihan    ");
  // StringView s2 = StringView("   alihan , asdas,1615616    ,dsfsdf3,    0,,0.2    ");

  // VariantData v;
  // v.type = DOUBLE_TYPE;
  // v.value.float_v = -17.73;

  // printf("(%d, %s)%f", v.type, variant_type_to_string(v.type),  v.value);

 // TODO("todo deneme mesajı")
  //FIXME("fixme deneme mesajı")

  // s.append('X');
  // s += "z   ";
  // cout<<s<<"|"<<s.trim()<<"|"<<s.trim().insert(3, 'X')<<"|"<<endl<<s2<<endl;
  // for( auto a : s2.parse(',')){
  //   cout << a <<"|";
  // }
  return 0;
}
