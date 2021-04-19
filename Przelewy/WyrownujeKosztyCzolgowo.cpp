#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> Graf;
int *TablicaDocelowych;
int iloscOperacji = 0;
int n;

class Wierzcholek
{
public:
    int numer;
    int wartosc;
    int ileMusiOddac = 0;
};
vector<Wierzcholek> listaWierzcholkow;

void DrukujeWartosciWierzcholkow()
{
    for (int i = 1; i <= n; i++)
    {
        cout << TablicaDocelowych[i] << " ";
    }
    cout << endl;
}
bool PorownujePrzedzialy(const Wierzcholek &l, const Wierzcholek &r)
{
    if (l.wartosc >= r.wartosc)
        return true;
    return false;
}
int ZwracaNajwiekszaWartoscJakaMozeOddac(int wartosc, int iloscSasiadow)
{
    int oddawanaWartosc = 1;
    while (true)
    {
        if ((wartosc - iloscSasiadow * oddawanaWartosc) <= 0)
            return oddawanaWartosc;
        oddawanaWartosc++;
    }
    return oddawanaWartosc;
}
int ZnajdujePozycjeWierzcholkaWLiscie(int szukanyWierzcholek)
{
    for (int i = 0; i < listaWierzcholkow.size(); i++)
    {
        if (listaWierzcholkow[i].numer == szukanyWierzcholek)
        {
            return i;
        }
    }
    return -1;
}
void WyrownujeDlugi(Wierzcholek &wierzcholekDoPodzialu)
{
    int iloscSasiadow = Graf[wierzcholekDoPodzialu.numer].size();
    int ileOddaje = ZwracaNajwiekszaWartoscJakaMozeOddac(wierzcholekDoPodzialu.wartosc, iloscSasiadow);
    iloscOperacji += ileOddaje;
    for (int i = 0; i < Graf[wierzcholekDoPodzialu.numer].size(); i++)
    {
        int wierzcholek = Graf[wierzcholekDoPodzialu.numer][i];
        TablicaDocelowych[wierzcholek] += ileOddaje;
        int poz = ZnajdujePozycjeWierzcholkaWLiscie(wierzcholek);
        listaWierzcholkow[poz].wartosc += ileOddaje;
    }
    wierzcholekDoPodzialu.wartosc = wierzcholekDoPodzialu.wartosc - iloscSasiadow * ileOddaje;
    wierzcholekDoPodzialu.ileMusiOddac += ileOddaje;
    TablicaDocelowych[wierzcholekDoPodzialu.numer] = wierzcholekDoPodzialu.wartosc;
}
int main()
{

    cin >> n;
    int *aktualnaTablicaKosztow = new int[n + 1];
    TablicaDocelowych = new int[n + 1];
    int sumaWartosci = 0;

    for (int i = 1; i <= n; i++)
    {
        int wartosc;
        cin >> wartosc;
        aktualnaTablicaKosztow[i] = wartosc;
        sumaWartosci += wartosc;
    }
    int sumaWartosciPoZamianie = 0;
    for (int i = 1; i <= n; i++)
    {
        int wartosc;
        cin >> wartosc;
        TablicaDocelowych[i] = aktualnaTablicaKosztow[i] - wartosc;
        sumaWartosciPoZamianie += wartosc;
        Wierzcholek nowy;
        nowy.numer = i;
        nowy.wartosc = TablicaDocelowych[i];
        listaWierzcholkow.push_back(nowy);
    }
    if (sumaWartosciPoZamianie != sumaWartosci)
    {
        cout << "NIE - roznica w ilosci pieniedzy" << endl;
        return 0;
    }
    sort(listaWierzcholkow.begin(), listaWierzcholkow.end(), PorownujePrzedzialy);

    vector<int> wypelniacz;
    for (int i = 0; i <= n; i++)
    {
        Graf.push_back(wypelniacz);
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int wierzcholek, sasiad;
        cin >> wierzcholek >> sasiad;
        Graf[wierzcholek].push_back(sasiad); //dodajemy krawedz nieskierowana
        Graf[sasiad].push_back(wierzcholek);
    }
    //DrukujeWartosciWierzcholkow();

    while (listaWierzcholkow.front().wartosc != 0)
    {
        WyrownujeDlugi(listaWierzcholkow.front());
        sort(listaWierzcholkow.begin(), listaWierzcholkow.end(), PorownujePrzedzialy);
        //DrukujeWartosciWierzcholkow();
    }
    cout << "TAK" << endl;
    cout << iloscOperacji << endl;
    // for (int i = 1; i <= listaWierzcholkow.size(); i++)
    // {
    //     cout << listaWierzcholkow[ZnajdujePozycjeWierzcholkaWLiscie(i)].ileMusiOddac << " ";
    // }
    cout << endl;

    return 0;
}
