#include <cmath>
#include <ctime>
#include "Distributions.h"

unsigned long long distr::factorial(unsigned n)
{
    unsigned long long res = 1;
    for(unsigned i=1; i<=n; i++) res *= i;
    return res;
}

distr::Exponential::Exponential(double a)
{
    if (a < 0) throw BadParameterException("Exponential distribution: parameter lambda must be > 0");
    gen = my_rand::Random();
    lambda = a;
}

distr::Exponential::Exponential(int seed, double a)
{
    if (a < 0) throw BadParameterException("Exponential distribution: parameter lambda must be > 0");
    gen = my_rand::Random(seed);
    lambda = a;
}

double distr::Exponential::get()
{
    return -log(gen.random())/lambda;
}

double distr::Exponential::distr_func(double x)
{
    return 1.0 - exp(-lambda*x);
}

distr::Puasson::Puasson(double a)
{
    if (a < 0) throw BadParameterException("Puasson distribution: parameter lambda must be > 0");
    gen = my_rand::Random();
    lambda = a;
}

distr::Puasson::Puasson(int seed, double a)
{
    if (a < 0) throw BadParameterException("Puasson distribution: parameter lambda must be > 0");
    gen = my_rand::Random(seed);
    lambda = a;
}

unsigned distr::Puasson::get()
{
    unsigned k = 0;

    for (double prod = gen.random(), expRateInv = exp(-lambda); prod > expRateInv; prod *= gen.random(), k++) {}

    return k;
}

double distr::Puasson::distr_func(unsigned k)
{
    return std::pow(lambda, k)*std::exp(-lambda) / factorial(k);
}

distr::Gauss::Gauss(double a, double b)
{
    if (b < 0) throw BadParameterException("Gauss distribution: parameter sigma must be > 0");
    int t = time(nullptr);
    gen1 = my_rand::Random(t);
    gen2 = my_rand::Random(7*t);
    mu = a;
    sigma = b;
}

distr::Gauss::Gauss(int seed, double a, double b)
{
    if (b < 0) throw BadParameterException("Gauss distribution: parameter sigma must be > 0");
    gen1 = my_rand::Random(seed);
    gen2 = my_rand::Random(7*seed);
    mu = a;
    sigma = b;
}

double distr::Gauss::get()
{
    double x, y, s;
    do {
        x = gen1.randrange(-1,1);
        y = gen2.randrange(-1,1);
        s = x*x + y*y;
    } while(s > 1 or s < 0.0000001);
    double z = x * std::sqrt(-2*std::log(s)/s);
    return mu + sigma*z;
}

void distr::Gauss::gettwo(double& a, double& b)
{
    double x, y, s;
    do {
        x = gen1.randrange(-1,1);
        y = gen2.randrange(-1,1);
        s = x*x + y*y;
    } while(s > 1 or s < 0.0000001);
    double z1 = x * std::sqrt(-2*std::log(s)/s);
    double z2 = y * std::sqrt(-2*std::log(s)/s);
    a = mu + sigma*z1;
    b = mu + sigma*z2;
}

double distr::Gauss::distr_func(double x)
{
    double res = (1.0 + std::erf( (x-mu) / (sigma*std::sqrt(2.0))) ) / 2.0;
    return res;
}

double distr::Cauchy::get()
{
    double a,b;
    gen.gettwo(a,b);
    return a/b;
}

double distr::Cauchy::distr_func(double x)
{
    return std::atan(x) / M_PI + 0.5;
}
