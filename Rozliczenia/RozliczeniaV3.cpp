#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

using namespace std;

class TablicaCykliczna
{
private:
    int wielkosc;
    int *Tablica;
    long long ileDodalismy = 0;
    int PrawdziwyIndex(int index)
    {
        int wolnyIndex = ileDodalismy % wielkosc;
        int nowyIndex = wolnyIndex - index % wielkosc;
        if (nowyIndex < 0)
            nowyIndex = wielkosc + nowyIndex;
        return nowyIndex;
    }

public:
    TablicaCykliczna(){

    };
    TablicaCykliczna(int rozmiar)
    {
        wielkosc = rozmiar;
        Tablica = new int[wielkosc]{0};
    };

    void Dodaj(int wartosc)
    {
        Tablica[PrawdziwyIndex(0)] = wartosc;
        ileDodalismy++;
    };
    int &operator[](int index)
    {
        //if (index > ileDodalismy)
        //    throw out_of_range("nie dodalismy tyle faktur. Podany index to: " + index);
        return Tablica[PrawdziwyIndex(index)];
    }
};

TablicaCykliczna Faktury;
long long *SumyRosnace;
int m;
int dlugoscSum;
int wolnyIndex = 0;

void inicjuj(int rozmiar)
{
    m = rozmiar;
    Faktury = TablicaCykliczna(m);
    dlugoscSum = sqrt(m);
    SumyRosnace = new long long[dlugoscSum + 1]{0};
}
void dodaj(int nowaFaktura)
{

    for (int i = 0; i < dlugoscSum + 1; i++)
    {
        int pozycjaPrzesuwana = (i + 1) * dlugoscSum;
        SumyRosnace[i] = SumyRosnace[i] - Faktury[pozycjaPrzesuwana];
    }
    Faktury.Dodaj(nowaFaktura);

    for (int i = 0; i < dlugoscSum + 1; i++)
    {
        SumyRosnace[i] = SumyRosnace[i] + nowaFaktura;
    }
}
void koryguj(int pozycja, int nowaWartosc)
{
    Faktury[pozycja] = Faktury[pozycja] + nowaWartosc;
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
        Suma = Suma + Faktury[i];
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
            cout << Faktury[j] << " ";
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