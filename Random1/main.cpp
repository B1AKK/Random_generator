#include <iostream>
#include <cstdio>
#include "Random1.h"
#include "test.h"


int main()
{
    test1();
    uniform_test(6, 1000000);
    exponent_test(1.2, 11, 10000);
    puasson_test(10, 10000);
    gauss_test(5, 1.2, 17, 10000);
    cauchy_test(20, 10000);
    return 0;
}
