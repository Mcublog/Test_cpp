// TestFunc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

#define MAX(x, y, r) do{\
                        int X = x;\
                        int Y = y;\
                        X > Y? r=X:r=Y;\
                     }while(0)

int power(int x, unsigned p) {
    int answer = x;
    /* считаем answer */
    if (p != 0)
    {
        if (p & 1 == 0)
        {
            for (int i = 0; i < (p - 1); i++) answer = answer << 1;
        }
        else
        {
            for (int i = 0; i < (p - 1); i++) answer = answer * x;
        }
    }
    else return 1;
    return answer;
}

int foo(int n) {
    static int i = 0;
    cout << i<<endl;
    i++;
    if (n <= 0)
        return 1;
    return foo((n * 2) / 3) + foo(n - 2);
}

unsigned GCD(unsigned a, unsigned b) {

    if (a != 0 && b != 0)
    {
        if (a > b) a = a % b;
        else b = b % a;
        GCD(a, b);
    }
    else return a + b;
}

int main() {

    foo(3);
    cout << GCD(100, 24) << endl;

    system("pause");
    return 0;
}

void test (void)
{
    cout << "power " << power(2, 5) << endl;

    vector<int> srcVec;
    for (int val = 0; val < 10; val++)
    {
        srcVec.push_back(val);
    }

    for_each(srcVec.begin(), srcVec.end(), [](int _n)
    {
        _n++;
        cout << _n << " ";
    });
    cout << endl << endl;

    int a = 10;
    int b = 20;
    int c = 0;

    MAX(--a, b, c);

    cout << "c = " << c << endl;

    system("pause");
}

