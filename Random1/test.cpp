#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>
#include "Random1.h"
#include "test.h"
#include "Distributions.h"

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

    cout << "#################################################################################" << endl;
}

void uniform_test(unsigned N, unsigned n)
{
    my_rand::Random rnd;
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
    cout << "#################################################################################" << endl << endl;
}

void exponent_test(double lambda, unsigned N, unsigned n)
{
    distr::Exponential expo(lambda);

    unsigned counter[N];
    for (unsigned i=0; i<N; i++) counter[i] = 0;

    const char filename[32] = "Exponential.txt";
    ofstream fout;
    fout.open(filename);

    double tmp;
    double x = 10.0 / lambda;
    for (unsigned i=0; i<n; i++)
    {
        try {
            tmp = expo.get();
            fout << tmp << endl;
            if (tmp < 0 || tmp > x)
            {
                n--;
                continue;
            }
            counter[static_cast<int>(floor(N*tmp/x))]++;
        }
        catch(std::bad_cast)
        {
            n--; continue;
        }
    }

    fout.close();

    cout << "Sequence saved in file " << filename << endl;
    cout << "Parts of numbers in the intervals compared with theoretical probability of entering the interval" << endl << endl;
    cout << "x = " << x << endl;

    const int bigwidth = 120, smallwidth = 10, precision = 6;
    cout.fill('=');
    cout.width(bigwidth);
    cout << endl << "" << endl;

    char buf[smallwidth];
    for (int k=0; k<N; k++)
    {
        sprintf(buf, "%dx/%d", k, N);
        cout.fill(' ');
        cout.width(smallwidth);
        cout.setf(ios::left);
        cout << buf;
    }
    cout.fill('-');
    cout.width(bigwidth);
    cout << endl << "" << endl;

    for (int k=0; k<N; k++)
    {
        cout.fill(' ');
        cout.width(smallwidth);
        cout.precision(precision);
        cout.setf(std::ios::fixed);
        cout.setf(ios::left);
        cout << (counter[k]+0.0)/n;
    }
    cout.fill('-');
    cout.width(bigwidth);
    cout << endl << "" << endl;

    double s=0, prob, delta;
    for (int k=0; k<N; k++)
    {
        prob = expo.distr_func((k+1)*x/N) - expo.distr_func(k*x/N);
        delta = abs(prob - (counter[k]+0.0)/n);
        s += delta*delta;
        cout.fill(' ');
        cout.width(smallwidth);
        cout.precision(precision);
        cout.setf(std::ios::fixed);
        cout.setf(ios::left);
        cout << prob;
    }
    cout.fill('=');
    cout.width(bigwidth);
    cout << endl << "" << endl;

    cout.precision(10);
    cout.setf(std::ios::fixed);
    cout << "Square differences sum: " << s << endl;
    cout << "#################################################################################" << endl << endl;

}

void puasson_test(double lambda, unsigned n)
{
    distr::Puasson p(lambda);
    unsigned N = static_cast<unsigned>(floor(5*lambda));
    if (N > 20) N = 20;
    unsigned counter[N];
    for (unsigned i=0; i<N; i++) counter[i] = 0;
    const char filename[32] = "Puasson.txt";
    ofstream fout;
    fout.open(filename);

    unsigned tmp;
    for (unsigned i=0; i<n; i++)
    {
        try {
            tmp = p.get();
            fout << tmp << endl;
            counter[tmp]++;
        }
        catch(std::bad_cast e)
        {
            n--;
            continue;
        }
    }

    fout.close();

    cout << "Sequence saved in file " << filename << endl;
    cout << "Frequency of numbers appearing in the sequence compared with theoretical probability" << endl << endl;

    const int width = 10, precision = 6, num = 10;
    cout.fill('=');
    cout.width(width*num);
    cout << endl << "" << endl;

    int j,k;
    double s = 0;
    for (int i=0; i<N; i+=j)
    {

        for (j=0, k=i; k<N && j<num; k++, j++)
        {
            cout.fill(' ');
            cout.width(width);
            cout.setf(ios::left);
            cout << k;
        }
        cout.fill('-');
        cout.width(width*num);
        cout << endl << "" << endl;

        for (j=0, k=i; k<N && j<num; k++, j++)
        {
            cout.fill(' ');
            cout.width(width);
            cout.precision(precision);
            cout.setf(std::ios::fixed);
            cout.setf(ios::left);
            cout << (counter[k]+0.0)/n;
        }
        cout.fill('-');
        cout.width(width*num);
        cout << endl << "" << endl;

        double prob, delta;
        for (j=0, k=i; k<N && j<num; k++, j++)
        {
            prob = p.distr_func(k);
            delta = abs(prob - (counter[k]+0.0)/n);
            s += delta*delta;
            cout.fill(' ');
            cout.width(width);
            cout.precision(precision);
            cout.setf(std::ios::fixed);
            cout.setf(ios::left);
            cout << prob;
        }
        cout.fill('=');
        cout.width(width*num);
        cout << endl << "" << endl;
    }

    cout.precision(10);
    cout.setf(std::ios::fixed);
    cout << "Square differences sum: " << s << endl;
    cout << "#################################################################################" << endl << endl;

}

void gauss_test(double mu, double sigma, unsigned N, unsigned n)
{
    distr::Gauss gauss(mu, sigma);

    unsigned counter[N];
    for (unsigned i=0; i<N; i++) counter[i] = 0;

    const char filename[32] = "Gauss.txt";
    ofstream fout;
    fout.open(filename);

    double tmp;
    double a = mu - 3*sigma;
    double b = mu + 3*sigma;
    int m;
    printf("Considering interval [%lf, %lf]\n", a, b);
    for (unsigned i=0; i<n; i++)
    {
        try {
            tmp = gauss.get();
            fout << tmp << endl;
            if (tmp < a || tmp > b)
            {
                n--;
                continue;
            }
            m = static_cast<int>(floor(N * (tmp-a) / (b-a)));
            counter[m]++;
        }
        catch(std::bad_cast e)
        {
            n--;
            continue;
        }
    }

    fout.close();

    cout << "Sequence saved in file " << filename << endl;
    cout << "Parts of numbers in the intervals compared with theoretical probability of entering the interval" << endl << endl;

    const int width = 10, precision = 6, num = 10;
    cout.fill('=');
    cout.width(width*num);
    cout << endl << "" << endl;

    int j,k;
    double s = 0;
    for (int i=0; i<N; i+=j)
    {

        for (j=0, k=i; k<N && j<num; k++, j++)
        {
            cout.fill(' ');
            cout.width(width);
            cout.setf(ios::left);
            cout << k;
        }
        cout.fill('-');
        cout.width(width*num);
        cout << endl << "" << endl;

        for (j=0, k=i; k<N && j<num; k++, j++)
        {
            cout.fill(' ');
            cout.width(width);
            cout.precision(precision);
            cout.setf(std::ios::fixed);
            cout.setf(ios::left);
            cout << (counter[k]+0.0)/n;
        }
        cout.fill('-');
        cout.width(width*num);
        cout << endl << "" << endl;

        double prob, delta, x2, x1;
        for (j=0, k=i; k<N && j<num; k++, j++)
        {
            x1 = a + k*(b-a+0.0)/N;
            x2 = x1 + (b-a+0.0)/N;
            prob = gauss.distr_func(x2) - gauss.distr_func(x1);
            delta = abs(prob - (counter[k]+0.0)/n);
            s += delta*delta;
            cout.fill(' ');
            cout.width(width);
            cout.precision(precision);
            cout.setf(std::ios::fixed);
            cout.setf(ios::left);
            cout << prob;
        }
        cout.fill('=');
        cout.width(width*num);
        cout << endl << "" << endl;
    }

    cout.precision(10);
    cout.setf(std::ios::fixed);
    cout << "Square differences sum: " << s << endl;
    cout << "#################################################################################" << endl << endl;

}

void cauchy_test(unsigned N, unsigned n)
{
    distr::Cauchy cauchy;

    unsigned counter[N];
    for (unsigned i=0; i<N; i++) counter[i] = 0;

    const char filename[32] = "Cauchy.txt";
    ofstream fout;
    fout.open(filename);

    double tmp;
    double a = -40.0;
    double b = 40.0;
    int m;
    printf("Considering interval [%lf, %lf]\n", a, b);
    for (unsigned i=0; i<n; i++)
    {
        try {
            tmp = cauchy.get();
            fout << tmp << endl;
            if (tmp < a || tmp > b)
            {
                n--;
                continue;
            }
            m = static_cast<int>(floor(N * (tmp-a) / (b-a)));
            counter[m]++;
        }
        catch(std::bad_cast e)
        {
            n--;
            continue;
        }
    }

    fout.close();

    cout << "Sequence saved in file " << filename << endl;
    cout << "Parts of numbers in the intervals compared with theoretical probability of entering the interval" << endl << endl;

    const int width = 10, precision = 6, num = 10;
    cout.fill('=');
    cout.width(width*num);
    cout << endl << "" << endl;

    int j,k;
    double s = 0;
    for (int i=0; i<N; i+=j)
    {

        for (j=0, k=i; k<N && j<num; k++, j++)
        {
            cout.fill(' ');
            cout.width(width);
            cout.setf(ios::left);
            cout << k;
        }
        cout.fill('-');
        cout.width(width*num);
        cout << endl << "" << endl;

        for (j=0, k=i; k<N && j<num; k++, j++)
        {
            cout.fill(' ');
            cout.width(width);
            cout.precision(precision);
            cout.setf(std::ios::fixed);
            cout.setf(ios::left);
            cout << (counter[k]+0.0)/n;
        }
        cout.fill('-');
        cout.width(width*num);
        cout << endl << "" << endl;

        double prob, delta, x2, x1;
        for (j=0, k=i; k<N && j<num; k++, j++)
        {
            x1 = a + k*(b-a+0.0)/N;
            x2 = x1 + (b-a+0.0)/N;
            prob = cauchy.distr_func(x2) - cauchy.distr_func(x1);
            delta = abs(prob - (counter[k]+0.0)/n);
            s += delta*delta;
            cout.fill(' ');
            cout.width(width);
            cout.precision(precision);
            cout.setf(std::ios::fixed);
            cout.setf(ios::left);
            cout << prob;
        }
        cout.fill('=');
        cout.width(width*num);
        cout << endl << "" << endl;
    }

    cout.precision(10);
    cout.setf(std::ios::fixed);
    cout << "Square differences sum: " << s << endl;
    cout << "#################################################################################" << endl << endl;
}
