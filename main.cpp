#include <iostream>
#include "string.h"

int main() {
    String str("Hi");
    str.append(" everyone");
    str.push_back(')');
    std::cout << str.print() << std::endl;
}