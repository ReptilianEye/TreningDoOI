#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int *TablicaDocelowych;
ll iloscOperacji = 0;
int n;
ll sumaWszystkichOperacji = 0;

class Wierzcholek
{
public:
    int poziom;
    int numer;
    int wartoscPoczatkowa;
    ll wartoscWypadkowa;
    ll iloscOdbic = 0;
    ll iloscOperacji = 0;
};
vector<Wierzcholek> WierzcholkiDoSprawdzenia;
vector<Wierzcholek> listaWierzcholkow;
vector<vector<int>> Graf;

void DrukujePoczatkoweWartosciWierzcholkow()
{
    for (int i = 1; i <= n; i++)
    {
        cout << TablicaDocelowych[i] << " ";
    }
    cout << endl;
}
void DrukujeWartosciOdbicWierzcholkow()
{
    for (int i = 1; i < listaWierzcholkow.size(); i++)
    {
        cout << listaWierzcholkow[i].iloscOdbic << " ";
    }
    cout << endl;
}
void UstawiaWierzcholkiOdKorzeniaDoLisci(int NumerKorzenia)
{
    bool *visited = new bool[n + 1]{false};
    vector<Wierzcholek> StosDoSprawdzenia;
    listaWierzcholkow[NumerKorzenia].poziom = 0;
    Wierzcholek korzen = listaWierzcholkow[NumerKorzenia];
    StosDoSprawdzenia.push_back(korzen);
    while (!StosDoSprawdzenia.empty())
    {
        Wierzcholek ojciec = StosDoSprawdzenia.front();
        StosDoSprawdzenia.erase(StosDoSprawdzenia.begin());

        WierzcholkiDoSprawdzenia.push_back(ojciec);

        visited[ojciec.numer] = true;

        for (int i = 0; i < Graf[ojciec.numer].size(); i++)
        {
            int numerWierzcholka = Graf[ojciec.numer][i];
            if (!visited[numerWierzcholka])
            {
                listaWierzcholkow[numerWierzcholka].poziom = ojciec.poziom + 1;
                Wierzcholek syn = listaWierzcholkow[numerWierzcholka];
                StosDoSprawdzenia.push_back(syn);
            }
        }
    }
}
int ZnajdujeKorzen()
{
    int numerKorzenia;
    int najwiecejSasiadow = -1;
    for (int i = 1; i < Graf.size(); i++)
    {
        int iloscSasiadow = Graf[i].size();
        if (najwiecejSasiadow < iloscSasiadow)
        {
            najwiecejSasiadow = Graf[i].size();
            numerKorzenia = i;
        }
    }
    return numerKorzenia;
}
void ZwiekszaIloscOperacjiWierzcholka(Wierzcholek &ojciec, ll oIleZwiekszamy)
{
    ojciec.iloscOdbic = oIleZwiekszamy - ojciec.wartoscWypadkowa;
    oIleZwiekszamy = ojciec.iloscOdbic;
    for (int i = 0; i < Graf[ojciec.numer].size(); i++)
    {
        Wierzcholek &syn = listaWierzcholkow[Graf[ojciec.numer][i]];
        if (syn.poziom > ojciec.poziom)
        {
            ZwiekszaIloscOperacjiWierzcholka(syn, oIleZwiekszamy);
        }
    }
}
Wierzcholek ObliczaWartoscWierzcholka(Wierzcholek ja)
{
    if (Graf[ja.numer].size() > 1)
    {
        ll dziura = LONG_LONG_MIN;
        int numerSynaZDziura;
        ll sumaWartosciSynow = 0;
        for (int i = 0; i < Graf[ja.numer].size(); i++)
        {
            int numerSyna = Graf[ja.numer][i];
            if (listaWierzcholkow[numerSyna].poziom > ja.poziom)
            {
                sumaWartosciSynow += listaWierzcholkow[numerSyna].wartoscWypadkowa;
                ll dziuraOdSyna = listaWierzcholkow[numerSyna].iloscOdbic + listaWierzcholkow[numerSyna].wartoscWypadkowa;
                if (dziura < dziuraOdSyna)
                {
                    dziura = dziuraOdSyna;
                    numerSynaZDziura = numerSyna;
                }
            }
        }
        ja.wartoscWypadkowa = sumaWartosciSynow - ja.wartoscPoczatkowa;
        for (int i = 0; i < Graf[ja.numer].size(); i++)
        {
            int numerSyna = Graf[ja.numer][i];
            if (listaWierzcholkow[numerSyna].poziom > ja.poziom)
            {
                if (dziura < 0)
                {
                    ZwiekszaIloscOperacjiWierzcholka(listaWierzcholkow[numerSyna], 0);
                    continue;
                }
                if (numerSyna != numerSynaZDziura)
                {
                    ZwiekszaIloscOperacjiWierzcholka(listaWierzcholkow[numerSyna], dziura);
                }
            }
        }
        if (dziura > 0)
        {
            ja.iloscOdbic = dziura;

            sumaWszystkichOperacji += dziura;
        }
        else
        {
            ja.iloscOdbic = 0;
        }
    }
    else
    {
        if (ja.wartoscPoczatkowa > 0)
        {
            ja.wartoscWypadkowa = -ja.wartoscPoczatkowa;
            ja.iloscOperacji = ja.wartoscPoczatkowa;

            sumaWszystkichOperacji += ja.wartoscPoczatkowa;
        }
        if (ja.wartoscPoczatkowa <= 0)
        {
            ja.wartoscWypadkowa = -ja.wartoscPoczatkowa;
            ja.iloscOperacji = 0;
        }
    }
    return ja;
}
int main()
{

    cin >> n;
    int *aktualnaTablicaKosztow = new int[n + 1];
    TablicaDocelowych = new int[n + 1];
    ll sumaWartosci = 0;

    for (int i = 1; i <= n; i++)
    {
        int wartosc;
        cin >> wartosc;
        aktualnaTablicaKosztow[i] = wartosc;
        sumaWartosci += wartosc;
    }
    ll sumaWartosciPoZamianie = 0;
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
        nowy.wartoscPoczatkowa = TablicaDocelowych[i];
        listaWierzcholkow.push_back(nowy);
    }
    if (sumaWartosciPoZamianie != sumaWartosci)
    {
        cout << "NIE" << endl;
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
    //DrukujePoczatkoweWartosciWierzcholkow();
    int numerKorzenia = ZnajdujeKorzen();
    UstawiaWierzcholkiOdKorzeniaDoLisci(numerKorzenia);
    while (!WierzcholkiDoSprawdzenia.empty())
    {
        Wierzcholek obliczanyWierzcholek = WierzcholkiDoSprawdzenia.back();
        WierzcholkiDoSprawdzenia.pop_back();
        Wierzcholek wierzcholekObliczony = ObliczaWartoscWierzcholka(obliczanyWierzcholek);
        listaWierzcholkow[wierzcholekObliczony.numer] = wierzcholekObliczony;
        //DrukujeWartosciOdbicWierzcholkow();
    }
    for (int i = 0; i < listaWierzcholkow.size(); i++)
        iloscOperacji += listaWierzcholkow[i].iloscOdbic;
    cout << "TAK" << endl;
    cout << iloscOperacji << endl;
   // DrukujeWartosciOdbicWierzcholkow();
    return 0;
}
