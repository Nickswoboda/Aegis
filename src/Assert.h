#include <iostream>
#define AE_ASSERT(x, msg) {if (!(x)) { std::cout << msg << "\n"; __debugbreak();}} 