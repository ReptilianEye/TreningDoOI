#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
int liczbaRuchow = 0;

void ZwracaRoznice(int wieksza, int &mniejsza)
{
    int roznicaNajwiekszej = wieksza - mniejsza;
    if (roznicaNajwiekszej % 2 == 0)
    {
        liczbaRuchow += roznicaNajwiekszej / 2;
        mniejsza = wieksza;
    }
    else
    {
        liczbaRuchow += roznicaNajwiekszej / 2;
        mniejsza += roznicaNajwiekszej - 1;
    }
}
void WyrownujeLiczby(vector<int> &listaLiczb)
{
    if (listaLiczb[0] == listaLiczb[1] && listaLiczb[1] == listaLiczb[2])
        return;
    liczbaRuchow++;
    sort(listaLiczb.begin(), listaLiczb.end());
    listaLiczb[0]++;
    listaLiczb[1]++;
    return WyrownujeLiczby(listaLiczb);
}
int main()
{
    bool *TablicaWzietych = new bool[51];
    vector<int> listaLiczb;
    int A, B, C;
    cin >> A >> B >> C;
    listaLiczb.push_back(A);
    listaLiczb.push_back(B);
    listaLiczb.push_back(C);

    int najwieksza = -1;
    int pozycjaNajwiekszej;
    for (int i = 0; i < listaLiczb.size(); i++)
    {
        if (najwieksza < listaLiczb[i])
        {
            najwieksza = listaLiczb[i];
            pozycjaNajwiekszej = i;
        }
    }
    listaLiczb.erase(listaLiczb.begin() + pozycjaNajwiekszej);

    int najmniejsza = INT32_MAX;
    int pozycjaNajmniejszej;
    for (int i = 0; i < listaLiczb.size(); i++)
    {
        if (najmniejsza > listaLiczb[i])
        {
            najmniejsza = listaLiczb[i];
            pozycjaNajmniejszej = i;
        }
    }
    listaLiczb.erase(listaLiczb.begin() + pozycjaNajmniejszej);

    int srednia = listaLiczb.back();
    listaLiczb.pop_back();

    ZwracaRoznice(najwieksza, najmniejsza);
    ZwracaRoznice(najwieksza, srednia);
    listaLiczb.push_back(najmniejsza);
    listaLiczb.push_back(najwieksza);
    listaLiczb.push_back(srednia);
    WyrownujeLiczby(listaLiczb);
    cout << liczbaRuchow << endl;
    return 0;
}