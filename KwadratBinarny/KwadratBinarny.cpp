#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

typedef unsigned long ll;

using namespace std;

int n;
int **Tablica;

int poleNajwiekszego;

void ZwracaNumerKolumnyParyJedynek(int &kolumna, int wierszPierwszej, int wierszDrugiej)
{
    if (kolumna == 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (Tablica[wierszPierwszej][i] == 1 && Tablica[wierszDrugiej][i] == 1)
            {
                kolumna = i;
                return;
            }
        }
    }
    else
    {
        for (int i = kolumna; i >= 0; i--)
        {
            if (Tablica[wierszPierwszej][i] == 1 && Tablica[wierszDrugiej][i] == 1)
            {
                kolumna = i;
                return;
            }
        }
    }
    kolumna = -1;
}

int main()
{
    cin >> n;
    Tablica = new int*[n];
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

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int kolumnaPierwszejPary = 0;
            ZwracaNumerKolumnyParyJedynek(kolumnaPierwszejPary, i, j);
            int KolumnaDrugiejPary = n - 1;
            ZwracaNumerKolumnyParyJedynek(KolumnaDrugiejPary, i, j);
            if (kolumnaPierwszejPary != KolumnaDrugiejPary)
            {
                int poleProstokatu = (abs(kolumnaPierwszejPary - KolumnaDrugiejPary)+1) * (abs(i - j)+1);
                if (poleNajwiekszego < poleProstokatu)
                {
                    poleNajwiekszego = poleProstokatu;
                }
            }
        }
    }
    cout << poleNajwiekszego << endl;
    return 0;
}
