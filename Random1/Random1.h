#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <ctime>

namespace my_rand
{

    class Random
    {
        static const unsigned m = 268435456;
        static const unsigned a = 134217733;
        static const unsigned c = 56727087;
        unsigned s0;

    public:
        Random(): s0(time(nullptr) % m) {};
        Random(int seed): s0(seed % m) {};

        double random();
        double randrange(double a, double b);
        int randrange_int(int a, int b);
    };
}


#endif
