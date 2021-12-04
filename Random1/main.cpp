#include <iostream>
#include <cstdio>
#include "Random1.h"
#include "test.h"
#include "Random1.cpp"
#include "test.cpp"


int main()
{
    test1();
    uniform_test(6, 1000000);
    return 0;
}
