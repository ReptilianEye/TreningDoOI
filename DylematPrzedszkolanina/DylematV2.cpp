#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

void ZwracaLiczbyPierwszeZPrzedzialuSitemEratostenesaV2(long granicaPrzedzialu)
{
    long *PrzedzialLiczb = new long[granicaPrzedzialu + 1]{0}; //funkcja dziala podobnie jak ta wyzej tylko ze uzywa bool zamiast int
    // for (int i = 0; i <= granicaPrzedzialu; i++)
    // {
    //     PrzedzialLiczb[i] = 0;
    // }

    int i, j;
    for (i = 2; i <= granicaPrzedzialu; i++)
        for (j = 1; j <= granicaPrzedzialu / i; j++)
            PrzedzialLiczb[i * j]++;
    int max = -1, liczba1;
    for (i = 1; i <= granicaPrzedzialu; i++)
        if (PrzedzialLiczb[i] >= max)
        {
            max = PrzedzialLiczb[i];
            liczba1 = i;
        }

    for (int i = 2; i <= liczba1; i++)
    {
        if (liczba1 % i == 0)
        { //funkcja wypisuje daną liczbę jeśli dzieli argument bez reszty
            {
                for (int wielokrotnosc = i; wielokrotnosc <= granicaPrzedzialu; wielokrotnosc = wielokrotnosc + i)
                {
                    PrzedzialLiczb[wielokrotnosc]--;
                }
            }
        }
    }
    int max2 = -1, pos2;
    for (i = 1; i <= granicaPrzedzialu; i++)
        if (PrzedzialLiczb[i] >= max2)
        {
            max2 = PrzedzialLiczb[i];
            pos2 = i;
        }
    cout << max + max2+1 << endl;
    cout << pos2 << " " << liczba1 << endl;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
    long n;

    cin >> n; // Czytamy liczbę wierzchołków i krawędzi

    ZwracaLiczbyPierwszeZPrzedzialuSitemEratostenesaV2(n);
    return 0;
}
