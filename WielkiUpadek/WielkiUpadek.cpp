#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int MAX = 2147483647;

class Domino
{
public:
    int pozycja = -1;
    int wysokosc = 0;
    int dziura = MAX;
};

class Dostawka
{
public:
    int ilosc = 0;
    int wartosc = -1;
};

int najdluzszyCiag = 0;

bool WypelniaDziure(int n, int poczatek, int koniec, Domino *TablicaDomino, Dostawka *Wziete)
{
    int *DoWypelnienia = new int[n];
    int i = poczatek;
    int IleWiekszych = Wziete[0].ilosc;
    int IleMniejszych = Wziete[1].ilosc;
    while (i <= koniec)
    {
        DoWypelnienia[i] = TablicaDomino[i].dziura;
        if (DoWypelnienia[i] >= Wziete[0].wartosc && IleWiekszych > 0)
        {
            int ileRazy = DoWypelnienia[i] / Wziete[0].wartosc;
            if (ileRazy >= IleWiekszych)
            {
                DoWypelnienia[i] = DoWypelnienia[i] - (IleWiekszych * Wziete[0].wartosc);
                IleWiekszych = 0;
                break;
            }
            else
            {
                DoWypelnienia[i] = DoWypelnienia[i] - (ileRazy * Wziete[0].wartosc);
                IleWiekszych = IleWiekszych - ileRazy;
            }
        }
        i++;
    }
    if (IleWiekszych > 0)
    {
        for (int i = 0; i < IleWiekszych; i++)
        {
            int pozycjaNajmniejszejStraty = -1;
            int najwiekszaLuka = 0;
            for (int j = 0; j <= koniec; j++)
            {
                if (DoWypelnienia[j] > najwiekszaLuka)
                {
                    najwiekszaLuka = DoWypelnienia[j];
                    pozycjaNajmniejszejStraty = j;
                }
            }
            if (pozycjaNajmniejszejStraty == -1)
                return true;
            DoWypelnienia[pozycjaNajmniejszejStraty] = DoWypelnienia[pozycjaNajmniejszejStraty] - Wziete[0].wartosc;
        }
    }
    i = poczatek;
    while (i <= koniec)
    {
        while (DoWypelnienia[i] > 0)
        {
            if (IleMniejszych <= 0)
            {
                return false;
            }
            int ileRazy = DoWypelnienia[i] / Wziete[1].wartosc;
            if (DoWypelnienia[i] % Wziete[1].wartosc != 0)
                ileRazy++;
            if (ileRazy > IleMniejszych)
            {
                return false;
            }
            DoWypelnienia[i] = DoWypelnienia[i] - (Wziete[1].wartosc * ileRazy);
            IleMniejszych = IleMniejszych - ileRazy;
        }
        i++;
    }
    return true;
}
void ZwracaNajwiekszaIloscDominoWCiagu(int n, Domino *TablicaDomino, Dostawka *Wziete)
{
    int poczatek;
    int koniec = 0;
    int ciag;
    int sumaDostawek = Wziete[0].ilosc + Wziete[1].ilosc;
    for (int i = 0; i < n; i++)
    {
        if (n - i + sumaDostawek < najdluzszyCiag)
            return;
        poczatek = i;
        while (WypelniaDziure(n, poczatek, koniec, TablicaDomino, Wziete))
        {

            if (koniec == n)
                break;
            koniec++;
        }
        ciag = koniec - poczatek + 1 + sumaDostawek;
        if (najdluzszyCiag < ciag)
            najdluzszyCiag = ciag;
    }
}
int WyliczaJednaDziure(int pozycja1, int pozycja2, int wysokosc)
{
    int dziura = pozycja1 - pozycja2 - wysokosc;
    if (dziura < 0)
        dziura = 0;
    return dziura;
}
void WyliczaDziury(int n, Domino *TablicaDomino, char kierunek)
{
    int dziura;
    for (int i = 0; i < n - 1; i++)
    {
        if (kierunek == 'P')
            dziura = WyliczaJednaDziure(TablicaDomino[i + 1].pozycja, TablicaDomino[i].pozycja, TablicaDomino[i].wysokosc);
        if (kierunek == 'L')
            dziura = (WyliczaJednaDziure(TablicaDomino[i].pozycja, TablicaDomino[i + 1].pozycja, TablicaDomino[i].wysokosc));
        TablicaDomino[i].dziura = dziura;
    }
}
void ObrocenieDanych(int n, Domino *TablicaDomino)
{
    int j = n - 1;
    Domino *tymczasowa = new Domino[n];
    Domino el;
    for (int i = 0; i < n; i++)
    {
        tymczasowa[j] = TablicaDomino[i];
        j--;
    }
    for (int i = 0; i < n; i++)
    {
        TablicaDomino[i] = tymczasowa[i];
    }
}
int main()
{
    int n;

    cin >> n; // Czytamy liczbę wierzchołków i krawędzi

    Domino *TablicaDomino = new Domino[n];
    int poz, wys;
    for (int i = 0; i < n; i++)
    {
        cin >> poz >> wys;
        TablicaDomino[i].pozycja = poz;
        TablicaDomino[i].wysokosc = wys;
    }
    WyliczaDziury(n, TablicaDomino, 'P');

    Dostawka *Wziete = new Dostawka[2];
    cin >> Wziete[0].ilosc >> Wziete[0].wartosc >> Wziete[1].ilosc >> Wziete[1].wartosc;

    ZwracaNajwiekszaIloscDominoWCiagu(n, TablicaDomino, Wziete);
    cout << najdluzszyCiag << endl;

    ObrocenieDanych(n, TablicaDomino);
    WyliczaDziury(n, TablicaDomino, 'L');
    najdluzszyCiag = 0;
    ZwracaNajwiekszaIloscDominoWCiagu(n, TablicaDomino, Wziete);
    cout << najdluzszyCiag << endl;
    return 0;
}
