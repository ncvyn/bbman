#include "eoutln.h"

#include <iostream>

int eoutln(std::string_view msg) {
    std::cerr << "error! " << msg << std::endl;
    return 1;
}
