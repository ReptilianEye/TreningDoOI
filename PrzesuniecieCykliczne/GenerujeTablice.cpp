#include <iostream>
#include <time.h>
#include <bitset>
#include <math.h>
#include <fcntl.h>

using namespace std;

int main()
{
    _setmode(_fileno(stdout), _O_TEXT);
    srand((unsigned)time(NULL));
    //long long n = (rand()* rand()  % 500000);
    long long n = 500000;
    cout << n << endl;

    long long zakres = (long long)pow(10, 9);

    long long liczba = 0;
    for (int i = 1; i <= n; i++)
    {
        liczba += ((rand() * rand()) % zakres);
        cout << liczba << " ";
        //cout << i << " ";
    }

    cout << endl;
    cout << rand() % n;
    return 0;
}