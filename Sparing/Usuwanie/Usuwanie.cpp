#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
class Liczba
{
public:
    long long wartosc;
    int ilosc = 1;
};

int licznikTrojek = 0;
//vector<vector<Liczba>> listaListLiczb;
vector<vector<int>> listaListLiczb;

int n;
int *TablicaWskaznikow;

// void ZliczaWartosciKtoreWystapily()
// {

//     for (int i = 0; i < listaListLiczb.size(); i++)
//     {
//         int wskaznik = 0;
//         for (int j = 1; j < listaListLiczb[i].size(); j++)
//         {
//             if (listaListLiczb[i][wskaznik].wartosc == listaListLiczb[i][j].wartosc)
//             {
//                 listaListLiczb[i][wskaznik].ilosc++;
//                 listaListLiczb[i].erase(listaListLiczb[i].begin() + j);
//                 j--;
//             }
//             else
//                 wskaznik++;
//         }
//     }
// }
// bool PorownujeLiczby(const Liczba &l, const Liczba &r)
// {
//     if (l.wartosc < r.wartosc)
//         return true;
//     return false;
// }
bool PodliczaLiczbeMniejszychOd(int wskaznikNaListe, long long wartoscMniejsza)
{
    //long long wartoscMniejsza = listaListLiczb[wskaznikNaListe][TablicaWskaznikow[wskaznikNaListe]];
    int i = TablicaWskaznikow[wskaznikNaListe + 1];
    for (i; i < n; i++)
    {
        if (wartoscMniejsza < listaListLiczb[wskaznikNaListe + 1][i])
        {
            if (wskaznikNaListe < 1)
            {
                TablicaWskaznikow[wskaznikNaListe + 1] = i;
                PodliczaLiczbeMniejszychOd(wskaznikNaListe + 1, listaListLiczb[wskaznikNaListe + 1][i]);
                //TablicaWskaznikow[wskaznikNaListe + 1] = i;
            }
            else
            {
                TablicaWskaznikow[wskaznikNaListe + 1] = i;
                licznikTrojek += (n - i);
                return true;
            }
        }
    }
    return false;
}

int main()
{
    cin >> n;
    vector<long long> listaLiczb;
    long long wartoscNajmniejszej = INT64_MAX;
    bool CzyPoLewej = true;
    for (int i = 0; i < n * 3; i++)
    {
        long long wartosc;
        cin >> wartosc;
        if (wartoscNajmniejszej > wartosc)
        {
            wartoscNajmniejszej = wartosc;
            if (i > (n * 3 / 2))
                CzyPoLewej = false;
        }
        listaLiczb.push_back(wartosc);
    }
    sort(listaLiczb.begin(), listaLiczb.end());

    long long sumaMniejszych = 0;
    long long sumaWiekszych = 0;
    long long i = 0;
    auto odGOry = 3 * n - 1;
    long long odDolu = 0;
    while (i < n)
    {
        sumaMniejszych += listaLiczb[odDolu];
        sumaWiekszych += listaLiczb[odGOry];
        odGOry--;
        odDolu++;
        i++;
    }
    long long roznica;
    if (CzyPoLewej)
    {
        roznica = sumaWiekszych - sumaMniejszych;
    }
    else
    {
        roznica = sumaMniejszych - sumaWiekszych;
    }
    cout << roznica << endl;
}
