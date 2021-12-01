#include <iostream>
#include <cstdio>
#include "Random1.h"
//#include "Random1.cpp"


using namespace std;

void test1()
{
    my_rand::Random rnd;

    cout << "random" << endl;
    for (int i=0; i<10; i++)
    {
        cout << rnd.random() << endl;
    }

    cout << "randrange(15.6, 91.3)" << endl;
    for (int i=0; i<5; i++)
    {
        cout << rnd.randrange(15.6, 91.3) << endl;
    }

    cout << "randrange(-65, 20)" << endl;
    for (int i=0; i<5; i++)
    {
        cout << rnd.randrange(-65, 20) << endl;
    }

    cout << "randrange_int(0,10000)" << endl;
    for (int i=0; i<5; i++)
    {
        cout << rnd.randrange_int(0,10000) << endl;
    }

    cout << "randrange_int(-20, -10)" << endl;
    for (int i=0; i<5; i++)
    {
        cout << rnd.randrange_int(-20, -10) << endl;
    }
}

void uniform_test()
{
    my_rand::Random rnd;
    unsigned N = 6, n = 1000000;
    double tmp;
    int counter[N];
    for(int i=0; i<N; i++) counter[i] = 0;
    for (int i=0; i<n; i++)
    {
        tmp = rnd.random();
        counter[static_cast<int>(floor(N*tmp))]++;
    }

    printf("\n1/%d = %lf\n", N, 1.0/N);
    for (int i=0; i<N; i++)
    {
        printf("Part of numbers in the interval [%d/%d, %d/%d]: %lf\n", i, N, i+1, N, (counter[i]+0.0)/n);
    }
}

int main()
{
    test1();
    uniform_test();
    return 0;
}
