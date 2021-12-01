#include "Random1.h"

double my_rand::Random::random()
{
    s0 = (a * s0 + c) % m;
    return (s0 + 1.0) / (m + 1.0);
}

double my_rand::Random::randrange(double a, double b)
{
    return a + (b-a) * random();
};

int my_rand::Random::randrange_int(int a, int b)
{
    return static_cast<int>(floor(a + (b+1-a) * random()));
}
