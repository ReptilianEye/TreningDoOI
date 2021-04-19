#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

class Wierzcholek
{
public:
    int X = 0;
    int Y = 0;
};

Wierzcholek *TablicaOdcinkow;

// int ZwracaWynikDzielenia(int dzielna, int dzielnik)
// {
//     if (dzielna * dzielnik > 0)
//         return dzielna / dzielnik;
//     else
//     {
//         int wynik = (dzielna + dzielnik - 2) / dzielnik;
//         return wynik;
//     }
// }
bool CzyOdcinkiSiePrzecinaja()
{
    int poziomaDluga;
    int poziomaKrotka;
    int pionowaDluga ;
    int pionowaKrotka = max(TablicaOdcinkow[2].Y,TablicaOdcinkow[1].Y) - min(TablicaOdcinkow[2].Y,TablicaOdcinkow[1].Y) ;

}

int main()
{

    TablicaOdcinkow = new Wierzcholek[4];
    Wierzcholek nowy1;
    cout << sizeof(long double) << endl;
    for (int i = 0; i < 4; i++)
    {
        Wierzcholek nowy;
        int x, y;
        cin >> x >> y;
        nowy.X = x;
        nowy.Y = y;
        TablicaOdcinkow[i] = nowy;
    }

    for (int i = -10; i < 10; i++)
    {
        for (int j = 1; j < 5; j++)
        {
         //   cout << i << " / " << j << " " << ZwracaWynikDzielenia(i, j) << endl;
        }
    }
    return 0;
}
