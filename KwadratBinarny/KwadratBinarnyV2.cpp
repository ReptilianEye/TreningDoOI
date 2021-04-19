#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

typedef unsigned long ll;

using namespace std;

int n;
int **Tablica;
int pozycjaOdPrawej;
int pozycjaOdLewej;
vector<vector<ll>> listaSkroconych;

// string GenerujeBinarna()
// {
//     string binarna = "";
//     int dlugosc = (rand() + 2) % 32;
//     for (int i = 0; i <= dlugosc; i++)
//     {
//         if (rand() % 2 == 1)
//         {
//             binarna += '1';
//         }
//         else
//         {
//             binarna += '0';
//         }
//     }
//     return binarna;
// }
bool CzyJedynkaMaOdpowiednika(int numerWiersza,int ktoraKolumna, int pozycja)
{
    //int ktoraKolumna = n - 1 - pozycja / 32;
    ll liczba = listaSkroconych[numerWiersza][ktoraKolumna];
    ll potega = pow(2, pozycja % 31);
    ll porownanie = potega & liczba;
    if (porownanie > 0)
        return true;
    else
        return false;
}
int ZwracaPozycjeSkrajnejJedynkiPrawa(ll liczba, int ktoraOdPrawej, int numerWiersza)
{
    for (int i = 0; i < 32; i++)
    {
        ll potega = pow(2, i);
        ll wynikAnd = liczba & potega;
        if (wynikAnd > 0)
        {
            int pozycjaJedynki = i + (32 * ktoraOdPrawej);
            for (int i = n - 1; i > numerWiersza; i++)
            {
                if (CzyJedynkaMaOdpowiednika(i,ktoraOdPrawej, pozycjaJedynki))
                {
                    cout << "Ma" << endl;
            }
        }
    }

    return -1;
}

void WypisujeListe(vector<vector<ll>> tablica)
{
    for (int i = 0; i < tablica.size(); i++)
    {
        for (int j = 0; j < tablica[i].size(); j++)
        {
            cout << tablica[i][j] << " ";
        }
        cout << endl;
    }
}

ll ZamieniaBinarnaNaDziesietna(string binarna)
{
    ll dziesietna;
    int licznikPotegi = 0;
    for (int i = binarna.size() - 1; i >= 0; i--)
    {
        if (binarna[i] == '1')
            dziesietna += pow(2, licznikPotegi);
        licznikPotegi++;
    }
    return dziesietna;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        listaSkroconych.push_back(vector<ll>());
        string binarna;
        ll dziesietna;
        for (int j = 0; j < n; j++)
        {
            char wartosc;
            cin >> wartosc;
            binarna += wartosc;
            if (binarna.size() == 32)
            {
                dziesietna = ZamieniaBinarnaNaDziesietna(binarna);
                binarna = "";
                listaSkroconych[i].push_back(dziesietna);
            }
        }
        if (binarna != "")
        {
            dziesietna = ZamieniaBinarnaNaDziesietna(binarna);
            listaSkroconych[i].push_back(dziesietna);
        }
    }
    for (int i = 0; i < listaSkroconych.size(); i++)
    {
        int ktoraOdPrawej = 0;
        for (int j = listaSkroconych[i].size(); j >= 0; j--)
        {
            ll liczba = listaSkroconych[i][j];
            pozycjaOdPrawej = ZwracaPozycjeSkrajnejJedynkiPrawa(liczba, ktoraOdPrawej, i);
            ktoraOdPrawej++;
        }
    }
    return 0;
}
