#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

int *TablicaDocelowych;
int iloscOperacji = 0;
int n;

class Wierzcholek
{
public:
    int poziom;
    int numer;
    int wartosc;
    int ileMusiOddac = 0;
};
vector<Wierzcholek> WierzcholkiDoSprawdzenia;
vector<Wierzcholek> listaWierzcholkow;
vector<vector<int>> Graf;

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
void UstawiaWierzcholkiOdKorzeniaDoLisci(int NumerKorzenia)
{
    bool *visited = new bool[n + 1]{false};
    vector<Wierzcholek> StosDoSprawdzenia;
    listaWierzcholkow[NumerKorzenia].poziom = 0;
    Wierzcholek korzen = listaWierzcholkow[NumerKorzenia];
    StosDoSprawdzenia.push_back(korzen);
    WierzcholkiDoSprawdzenia.push_back(korzen);
    while (!StosDoSprawdzenia.empty())
    {
        Wierzcholek ojciec = StosDoSprawdzenia.front();
        StosDoSprawdzenia.erase(StosDoSprawdzenia.begin());
        visited[ojciec.numer] = true;

        for (int i = 0; i < Graf[ojciec.numer].size(); i++)
        {
            int numerWierzcholka = Graf[ojciec.numer][i];
            if (!visited[numerWierzcholka])
            {
                listaWierzcholkow[numerWierzcholka].poziom = ojciec.poziom + 1;
                Wierzcholek syn = listaWierzcholkow[numerWierzcholka];
                StosDoSprawdzenia.push_back(syn);
                WierzcholkiDoSprawdzenia.push_back(syn);
            }
        }
    }
}
int ZnajdujeKorzen()
{
    int korzen;
    int najwiecejSasiadow = -1;
    for (int i = 1; i < Graf.size(); i++)
    {
        int iloscSasiadow = Graf[i].size();
        if (najwiecejSasiadow < iloscSasiadow)
        {
            najwiecejSasiadow = Graf[i].size();
            korzen = i;
        }
    }
    return korzen;
}
void ZwiekszaIloscOperacjiWierzcholka(Wierzcholek ojciec, int oIleZwiekszamy)
{
    for (int i = 0; i < Graf[ojciec.numer].size(); i++)
    {
        Wierzcholek syn = listaWierzcholkow[Graf[ojciec.numer][i]];
        if (syn.poziom > ojciec.poziom)
        {
            syn.wartosc += oIleZwiekszamy;
            syn.ileMusiOddac += oIleZwiekszamy;
            listaWierzcholkow[syn.numer] = syn;
            ZwiekszaIloscOperacjiWierzcholka(syn, oIleZwiekszamy);
        }
    }
}
void ObliczaWartoscWierzcholka(Wierzcholek obliczanyWierzcholek)
{
    int najmniejszaWartoscSyna = INT_MAX;
    int numerNajmniejszegoSyna;
    for (int i = 0; i < Graf[obliczanyWierzcholek.numer].size(); i++)
    {
        Wierzcholek sprawdzanySyn = listaWierzcholkow[Graf[obliczanyWierzcholek.numer][i]];
        if (najmniejszaWartoscSyna < sprawdzanySyn.wartosc)
        {
            najmniejszaWartoscSyna = sprawdzanySyn.wartosc;
            numerNajmniejszegoSyna = sprawdzanySyn.numer;
        }
    }
    obliczanyWierzcholek.wartosc += najmniejszaWartoscSyna;
    for (int i = 0; i < Graf[obliczanyWierzcholek.numer].size(); i++)
    {
        Wierzcholek sprawdzanySyn = listaWierzcholkow[Graf[obliczanyWierzcholek.numer][i]];
        if (sprawdzanySyn.numer != numerNajmniejszegoSyna)
        {
            ZwiekszaIloscOperacjiWierzcholka(sprawdzanySyn, najmniejszaWartoscSyna);
        }
    }
    listaWierzcholkow[obliczanyWierzcholek.numer] = obliczanyWierzcholek;
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
    Wierzcholek wartownik;
    listaWierzcholkow.push_back(wartownik);
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
    DrukujeWartosciWierzcholkow();
    int numerKorzenia = ZnajdujeKorzen();
    UstawiaWierzcholkiOdKorzeniaDoLisci(numerKorzenia);
    while (!WierzcholkiDoSprawdzenia.empty())
    {
        Wierzcholek obliczanyWierzcholek = WierzcholkiDoSprawdzenia.back();
        WierzcholkiDoSprawdzenia.pop_back();
        ObliczaWartoscWierzcholka(obliczanyWierzcholek);
    }
    for(int i = 0 ; i < listaWierzcholkow.size();i++)
    {
        iloscOperacji += listaWierzcholkow[i].wartosc;
    }
    cout << "TAK" << endl;
    cout << iloscOperacji << endl;
    for (int i = 1; i <= listaWierzcholkow.size(); i++)
    {
        cout << listaWierzcholkow[ZnajdujePozycjeWierzcholkaWLiscie(i)].ileMusiOddac << " ";
    }
    cout << endl;

    return 0;
}
