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
    long long n = 2000;
    cout << n << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int liczba = rand();
            if (liczba % 2 == 0)
                cout << 1 << " ";
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
    return 0;
}