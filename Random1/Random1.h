#ifndef _RANDOM1_H_
#define _RANDOM1_H_

#include <ctime>
#include <cmath>

namespace my_rand
{

    class Random
    {
        unsigned m = 268435456, a = 134217733, c = 56727086, s0, s1;

    private:


    public:
        Random(): s0(time(nullptr) % m) {};
        Random(unsigned seed): s0(seed % m) {};

        double random();
        double randrange(double a, double b);
        int randrange_int(int a, int b);
    };
}


#endif
