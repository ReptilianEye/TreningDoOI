#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

typedef unsigned long ll;

using namespace std;

class Wierzcholek
{
public:
    int numer;
    int numerWStroneLidera;
    int iloscPodlaczonych;
};

int n;
Wierzcholek *Tablica;

void WypisujeTablice()
{
    for (int i = 0; i < n; i++)
    {
        cout << Tablica[i].numer << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << Tablica[i].numerWStroneLidera << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << Tablica[i].iloscPodlaczonych << " ";
    }
    cout << endl;
    cout << endl;
    cout << endl;
}

Wierzcholek Find(Wierzcholek szukany)
{
    vector<Wierzcholek> Stos;
    Wierzcholek aktualny = szukany;
    while (aktualny.numer != aktualny.numerWStroneLidera)
    {
        Stos.push_back(aktualny);
        aktualny = Tablica[aktualny.numerWStroneLidera];
    }
    Wierzcholek lider = aktualny;
    while (!Stos.empty())
    {
        Wierzcholek przerabiany = Stos.back();
        Stos.pop_back();
        Tablica[przerabiany.numer].numerWStroneLidera = lider.numer;
    }
    return aktualny;
}

void Union(int liczba1, int liczba2)
{
    Wierzcholek lider1 = Find(Tablica[liczba1]);
    Wierzcholek lider2 = Find(Tablica[liczba2]);
    if (lider1.iloscPodlaczonych >= lider2.iloscPodlaczonych)
    {
        lider2.numerWStroneLidera = lider1.numer;
        lider1.iloscPodlaczonych += lider2.iloscPodlaczonych;
        lider2.iloscPodlaczonych = 1;
    }

    else
    {
        lider1.numerWStroneLidera = lider1.numer;

        lider2.iloscPodlaczonych += lider1.iloscPodlaczonych;
        lider1.iloscPodlaczonych = 1;
    }
    Tablica[lider1.numer] = lider1;
    Tablica[lider2.numer] = lider2;
}
int main()
{

    int iloscZapytan;
    cin >> n >> iloscZapytan;
    Tablica = new Wierzcholek[n];
    for (int i = 0; i < n; i++)
    {
        Wierzcholek nowy;
        nowy.iloscPodlaczonych = 1;
        nowy.numer = i;
        nowy.numerWStroneLidera = i;
        Tablica[i] = nowy;
    }
    for (int i = 0; i < iloscZapytan; i++)
    {
        int liczba1, liczba2;
        cin >> liczba1 >> liczba2;
        cout << liczba1 << " " << liczba2 << endl;
        Union(liczba1, liczba2);
        WypisujeTablice();
    }

    return 0;
}

