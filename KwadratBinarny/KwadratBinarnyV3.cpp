#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

typedef unsigned long ll;

using namespace std;

int poleNajwiekszego;
int n;
int **Tablica;
vector<vector<ll>> listaSkroconych;
int reszta;

void WypisujeListe()
{
    for (int i = 0; i < listaSkroconych.size(); i++)
    {
        for (int j = 0; j < listaSkroconych[i].size(); j++)
        {
            cout << listaSkroconych[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}
void WypisujeTablice()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << Tablica[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

void WczytujeTablice()
{
    Tablica = new int *[n];
    for (int i = 0; i < n; i++)
    {
        Tablica[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int wartosc;
            cin >> wartosc;
            Tablica[i][j] = wartosc;
        }
    }
}
void ZamieniaTabliceBinarnaNaDziesietna()
{
    for (int i = 0; i < n; i++)
    {
        vector<ll> lista;
        listaSkroconych.push_back(lista);
        string binarna;
        for (int j = 0; j < n; j++)
        {
            binarna += to_string(Tablica[i][j]);
            if (binarna.size() == 32)
            {
                ll dziesietna = bitset<32>(binarna).to_ulong();
                listaSkroconych[i].push_back(dziesietna);
                binarna = "";
            }
        }
        ll dziesietna = bitset<32>(binarna).to_ulong();
        listaSkroconych[i].push_back(dziesietna);
    }
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

int ZnajdujeSkajnaPareJedynek(ll liczba1, ll liczba2, bool czyOdLewej, bool CzyOstatnia)
{
    string liczbaBinarna1 = bitset<32>(liczba1).to_string();
    string liczbaBinarna2 = bitset<32>(liczba2).to_string();
    if (czyOdLewej)
    {
        int i = 0;
        if (CzyOstatnia)
            i += reszta;
        for (i; i < 32; i++)
        {

            if (liczbaBinarna1[i] == '1' && liczbaBinarna2[i] == '1')
                return i - reszta;
        }
    }
    else
    {
        for (int i = liczbaBinarna1.size()-1; i >= 0; i--)
        {
            if (liczbaBinarna1[i] == '1' && liczbaBinarna2[i] == '1')
                return i-reszta;
        }
    }
    return -1;
}
int main()
{
    cin >> n;
    reszta = 32 - (n % 32);
    WczytujeTablice();
   // WypisujeTablice();
    ZamieniaTabliceBinarnaNaDziesietna();
    //WypisujeListe();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int kolumnaOdLewej = 0;
            int kolumnaOdPrawej = 0;
            bool CzyOstania = false;
            for (int k = 0; k < listaSkroconych[i].size(); k++)
            {
                if (k == listaSkroconych[i].size() - 1)
                    CzyOstania = true;
                ll porowanie = listaSkroconych[i][k] & listaSkroconych[j][k];
                if (porowanie != 0)
                {
                    int pozycjaOdLewej = ZnajdujeSkajnaPareJedynek(listaSkroconych[i][k], listaSkroconych[j][k], true, CzyOstania);
                    kolumnaOdLewej = pozycjaOdLewej + k * 32;
                    break;
                }
            }
            for (int k = listaSkroconych[i].size() - 1; k >= 0; k--)
            {
                ll porowanie = listaSkroconych[i][k] & listaSkroconych[j][k];
                if (porowanie != 0)
                {
                    int pozycjaOdPrawej = ZnajdujeSkajnaPareJedynek(listaSkroconych[i][k], listaSkroconych[j][k], false, true);
                    kolumnaOdPrawej = pozycjaOdPrawej + k * 32;
                    break;
                }
            }
            if (kolumnaOdLewej != kolumnaOdPrawej)
            {
                int poleProstokata = (abs(kolumnaOdLewej - kolumnaOdPrawej) + 1) * (abs(i - j) + 1);
                if (poleNajwiekszego < poleProstokata)
                {
                    poleNajwiekszego = poleProstokata;
                }
            }
        }
    }
    cout << poleNajwiekszego << endl;
    return 0;
}
