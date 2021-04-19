#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

using namespace std;

int *Faktury;
long long *SumyRosnace;
int m;
int dlugoscSum;
long long ileDodalismy = 0;
int wolnyIndex = 0;

int ZwracaOdwroconyIndex(int index)
{
    wolnyIndex = ileDodalismy % m;
    int nowyIndex = wolnyIndex - index % m;
    if (nowyIndex < 0)
        nowyIndex = m + nowyIndex;
    return nowyIndex;
}

void inicjuj(int rozmiar)
{
    m = rozmiar;
    Faktury = new int[m]{0};
    dlugoscSum = sqrt(m);
    SumyRosnace = new long long[dlugoscSum + 1]{0};
}
void dodaj(int nowaFaktura)
{
    for (int i = 0; i < dlugoscSum + 1; i++)
    {
        int pozycjaPrzesuwana = (i + 1) * dlugoscSum;
        SumyRosnace[i] = SumyRosnace[i] - Faktury[ZwracaOdwroconyIndex(pozycjaPrzesuwana)];
    }
    Faktury[ZwracaOdwroconyIndex(0)] = nowaFaktura;
    ileDodalismy++;

    for (int i = 0; i < dlugoscSum + 1; i++)
    {
        SumyRosnace[i] = SumyRosnace[i] + nowaFaktura;
    }
}
void koryguj(int pozycja, int nowaWartosc)
{
    Faktury[ZwracaOdwroconyIndex(pozycja)] = Faktury[ZwracaOdwroconyIndex(pozycja)] + nowaWartosc;
    int pozycjaWSumach = (pozycja - 1) / dlugoscSum;
    for (int i = pozycjaWSumach; i < dlugoscSum + 1; i++)
        SumyRosnace[i] = SumyRosnace[i] + nowaWartosc;
}
long long suma(int pozycja)
{
    long long Suma = 0;
    int pozycjaWSumach = (pozycja - 1) / dlugoscSum - 1;
    if (pozycjaWSumach > -1)
        Suma = SumyRosnace[pozycjaWSumach];
    int pozycjaStartowaWFakturach = dlugoscSum * (pozycjaWSumach + 1) + 1;
    for (int i = pozycjaStartowaWFakturach; i <= pozycja; i++)
    {
        Suma = Suma + Faktury[ZwracaOdwroconyIndex(i)];
    }
    return Suma;
}

int main()
{
    //********** wczytywanie wejscia
    int roz = 17;
    //cin >> roz;
    inicjuj(roz);
    int iloscOperacji;
    cin >> iloscOperacji;
    for (int i = 1; i <= m; i++)
    {
        dodaj(i);
    }
    for (int i = m + 1; i <= 100; i++)
    {
        dodaj(i);
        for (int j = 1; j <= m; j++)
        {
            koryguj(j, -1);
        }
        for (int j = 1; j <= m; j++)
        {
            cout << Faktury[(ZwracaOdwroconyIndex(j))] << " ";
        }
        cout << endl;
        for (int j = 1; j <= m; j++)
        {
            cout << suma(j) << " ";
        }
        cout << endl;
        cout << endl;
        cout << endl;
    }
    // for (int i = 0; i < iloscOperacji; i++)
    // {
    //     string operacja;
    //     cin >> operacja;
    //     if (operacja == "dodaj")
    //     {
    //         int wartosc;
    //         cin >> wartosc;
    //         dodaj(wartosc);
    //     }
    //     if (operacja == "koryguj")
    //     {
    //         int wartosc, pozycja;
    //         cin >> pozycja >> wartosc;
    //         koryguj(pozycja, wartosc);
    //     }
    //     if (operacja == "suma")
    //     {
    //         int pozycja;
    //         cin >> pozycja;
    //         long long sumaFaktur = suma(pozycja);
    //         cout << sumaFaktur << endl;
    //     }
    // }

    return 0;
}