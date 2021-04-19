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

    for (int i = 0; i < 3; i++)
    {
        vector<Liczba> listaLiczb;
        for (int j = 0; j < n; j++)
        {
            int wartosc;
            cin >> wartosc;
            Liczba nowa;
            nowa.wartosc = wartosc;
            listaLiczb.push_back(nowa);
        }
        sort(listaLiczb.begin(), listaLiczb.end(), PorownujeLiczby);
        listaListLiczb.push_back(listaLiczb);
    }
    ZliczaWartosciKtoreWystapily();
    TablicaWskaznikow = new int[3]{0};
    for (int i = 0; i < n; i++)
    {
        TablicaWskaznikow[0] = i;
        PodliczaLiczbeMniejszychOd(0, listaListLiczb[0][i].wartosc);
    }
    cout << licznikTrojek << endl;
}
