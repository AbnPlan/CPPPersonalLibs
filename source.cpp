#include "string.h"

int main(){
    string test1("abcdef");
    string test2("ABCDEF");
    string test3(test2);

    std::cout << test1.toUpper() + test2.toLower();
}