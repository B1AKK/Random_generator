#ifndef _DISTRIBUTIONS_H_
#define _DISTRIBUTIONS_H_

#include <exception>
#include <stdexcept>
#include "Random1.h"

namespace distr
{

    unsigned long long factorial(unsigned n);

    class BadParameterException: public std::domain_error
    {
    public:
        BadParameterException(const char* message): std::domain_error(message) {};
    };

    class Exponential
    {
        my_rand::Random gen;
        double lambda;
    public:
        Exponential(double a=1.0);
        Exponential(int seed, double a=1.0);
        double get();
        double distr_func(double x);
    };

    class Puasson
    {
        my_rand::Random gen;
        double lambda;
    public:
        Puasson(double a=1.0);
        Puasson(int seed, double a=1.0);
        unsigned get();
        double distr_func(unsigned k);
    };

    class Gauss
    {
        my_rand::Random gen1, gen2;
        double mu, sigma;
    public:
        Gauss(double a=0.0, double b=1.0);
        Gauss(int seed, double a=0.0, double b=1.0);
        double get();
        void gettwo(double& a, double& b);
        double distr_func(double x);
    };

    class Cauchy
    {
        Gauss gen;
    public:
        Cauchy(): gen(Gauss()) {};
        Cauchy(int seed): gen(Gauss(seed)) {};
        double get();
        double distr_func(double x);
    };

}


#endif
