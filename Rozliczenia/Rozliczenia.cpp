#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

using namespace std;

int *Faktury;
long long *SumyRosnace;
int m;
int dlugoscSum;
long long wolnyIndex = 0;

void inicjuj(int rozmiar)
{

    m = rozmiar;
    Faktury = new int[m]{0};
    dlugoscSum = sqrt(m);
    SumyRosnace = new long long[dlugoscSum + 1]{0};
}
void dodaj(int nowaFaktura)
{
    SumyRosnace[dlugoscSum] = SumyRosnace[dlugoscSum] - Faktury[wolnyIndex % m];
    Faktury[wolnyIndex % m] = nowaFaktura;

    for (int i = 0; i < dlugoscSum + 1; i++)
    {
        SumyRosnace[i] = SumyRosnace[i] + nowaFaktura;
        int poz = (wolnyIndex - dlugoscSum * (i + 1));
        if (poz >= 0 && poz % m >= 0 && i < dlugoscSum)
            SumyRosnace[i] = SumyRosnace[i] - Faktury[poz % m];
    }
    wolnyIndex++;
}
void koryguj(int pozycja, int nowaWartosc)
{

    pozycja--;
    int pozycjaWSumach = pozycja / dlugoscSum;

    pozycja = (wolnyIndex - 1 - pozycja);
    Faktury[pozycja] = Faktury[pozycja] + nowaWartosc;

    for (int i = pozycjaWSumach; i < dlugoscSum + 1; i++)
        SumyRosnace[i] = SumyRosnace[i] + nowaWartosc;
}
long long suma(int pozycja)
{
    //pozycja--;

    long long Suma = 0;
    int pozycjaWSumach = (pozycja) / dlugoscSum - 1;
    if (pozycjaWSumach > -1)
        Suma = SumyRosnace[pozycjaWSumach];
    int pozycjaWFakturach = ((wolnyIndex - 1) % m) - (dlugoscSum * (pozycjaWSumach + 1));
    for (int i = 0; i < pozycja % dlugoscSum; i++)
    {
        if (pozycjaWFakturach < 0)
            pozycjaWFakturach = m - 1;
        Suma = Suma + Faktury[pozycjaWFakturach];
        pozycjaWFakturach--;
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
        //for (int j = 1; j <= m; j++)
        //{
        //    cout << Faktury[(ZwracaOdwroconyIndex(j))] << " ";
        //}
        cout << endl;
        for (int j = 1; j <= m; j++)
        {
            cout << suma(j) << " ";
        }
        cout << endl;
        cout << endl;
        cout << endl;
    }
    return 0;
}