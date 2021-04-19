#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

class Ciag
{
public:
    string tresc;
    int ilosc;
};
const int MaxDlugosc = 1000;
int ObecnaDlugosc;
int *Ilosci = new int[MaxDlugosc];

vector<Ciag> listaKombinacji;

void WypiszOdpowiedz()
{
    for (int i = 1; i < MaxDlugosc; i++)
    {
        if (Ilosci[i] < pow(2, i))
        {
            cout << i << endl;
            break;
        }
    }
}
void ZmieniaElement(string element, int zmiana)
{
    for (int i = 0; i < listaKombinacji.size(); i++)
    {
        if (listaKombinacji[i].tresc == element)
        {
            listaKombinacji[i].ilosc = listaKombinacji[i].ilosc + zmiana;
            if (listaKombinacji[i].ilosc == 0)
            {
                Ilosci[element.size()]--;
            }
            return;
        }
    }
    Ciag elem;
    elem.ilosc = zmiana;
    elem.tresc = element;
    listaKombinacji.push_back(elem);
    Ilosci[element.size()]++;
}

void WyszkujeStringODLugosci(string Liczba, int dlugosc)
{

    for (int i = 0; i <= Liczba.length() - dlugosc; i++)
    {
        string wyszukanyString = Liczba.substr(i, dlugosc);
        ZmieniaElement(wyszukanyString, 1);
    }
}
void ZmienCyfre(string liczba, int index)
{
    for (int i = 1; i <= ObecnaDlugosc; i++)
    {
        for (int j = 0; j < i; j++)
        {
            string poprzedniCiag = liczba.substr(index - j, i);
            ZmieniaElement(poprzedniCiag, -1);
        }
    }
    if (liczba[index] == '1')
    {
        liczba[index] == '0';
    }
    else
    {
        liczba[index] = '1';
    }
    for (int i = 1; i <= ObecnaDlugosc; i++)
    {
        for (int j = 0; j < i; j++)
        {
            string nowyCiag = liczba.substr(index - j, i);
            ZmieniaElement(nowyCiag, 1);
        }
    }
}

int main()
{
    //********** wczytywanie wejscia
    int n, m;
    cin >> n >> m;
    vector<string> elementy;

    string liczba;
    cin >> liczba;
    for (int i = 0; i < MaxDlugosc; i++)
    {
        Ilosci[i] = 0;
    }

    for (int i = 1; i < MaxDlugosc; i++)
    {
        WyszkujeStringODLugosci(liczba, i);
        ObecnaDlugosc = i;
        if (Ilosci[i] < pow(2, i))
        {
            break;
        }
    }
    WypiszOdpowiedz();
    for (int i = 0; i < m; i++)
    {
        int indexNowej;
        cin >> indexNowej;
        ZmienCyfre(liczba, indexNowej);
        WypiszOdpowiedz();
        if(Ilosci[ObecnaDlugosc] == pow(2,ObecnaDlugosc))
        {
            WyszkujeStringODLugosci(liczba,ObecnaDlugosc+1);
            ObecnaDlugosc++;
        }
    }

    return 0;
}