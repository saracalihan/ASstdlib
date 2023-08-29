#include "Logger.hpp"
#include <cstdlib>
int main(){
    string a = "asdd";
    LOG("Bu deneme log: {}, {}, {}", 15, "asd", '!', false);
    LOG("Bu deneme log: {}, {}, {}");
    LOG("Bu deneme log",875,'c');
    LOG("Bu deneme log");

    //DEBUG("deneme", 16);
    // LOG(12);
    return EXIT_SUCCESS;
}