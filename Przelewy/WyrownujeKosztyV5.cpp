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
int najmniejszyLisc = INT32_MAX;

class Wierzcholek
{
public:
    int poziom;
    int numer;
    int wartoscPoczatkowa;
    int ilePotomkow = 0;
    ll wartoscWypadkowa;
    ll wartoscWypadkowaNarastajaca = 0;
    ll iloscOdbic = 0;
    ll iloscOperacji = 0;
};
vector<int> WierzcholkiDoSprawdzenia;
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
        cout << listaWierzcholkow[i].ilePotomkow << " ";
    }
    cout << endl;
}
void UstawiaWierzcholkiOdKorzeniaDoLisci(int NumerKorzenia)
{
    bool *visited = new bool[n + 1]{false};
    vector<int> StosDoSprawdzenia;
    listaWierzcholkow[NumerKorzenia].poziom = 0;
    Wierzcholek korzen = listaWierzcholkow[NumerKorzenia];
    StosDoSprawdzenia.push_back(korzen.numer);
    while (!StosDoSprawdzenia.empty())
    {
        int numerOjca = StosDoSprawdzenia.front();
        Wierzcholek ojciec = listaWierzcholkow[numerOjca];
        StosDoSprawdzenia.erase(StosDoSprawdzenia.begin());

        WierzcholkiDoSprawdzenia.push_back(numerOjca);

        visited[numerOjca] = true;

        for (int i = 0; i < Graf[ojciec.numer].size(); i++)
        {
            int numerWierzcholka = Graf[ojciec.numer][i];
            if (!visited[numerWierzcholka])
            {
                listaWierzcholkow[numerWierzcholka].poziom = ojciec.poziom + 1;
                Wierzcholek syn = listaWierzcholkow[numerWierzcholka];
                StosDoSprawdzenia.push_back(syn.numer);
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
void ObliczaIlosciPrzodkow(int numerKorzenia)
{
    for (int i = WierzcholkiDoSprawdzenia.size() - 1; i >= 0; i--)
    {
        int numerWierzcholkaDoSprawdzenia = WierzcholkiDoSprawdzenia[i];
        Wierzcholek &obliczanyWierzcholek = listaWierzcholkow[numerWierzcholkaDoSprawdzenia];
        if (Graf[obliczanyWierzcholek.numer].size() == 1)
        {
            obliczanyWierzcholek.ilePotomkow = 0;
            continue;
        }
        int sumaDzieciSynow = 0;
        for (int i = 0; i < Graf[obliczanyWierzcholek.numer].size(); i++)
        {
            Wierzcholek syn = listaWierzcholkow[Graf[obliczanyWierzcholek.numer][i]];
            if (syn.poziom > obliczanyWierzcholek.poziom)
            {
                sumaDzieciSynow += syn.ilePotomkow;
            }
        }
        obliczanyWierzcholek.ilePotomkow = Graf[obliczanyWierzcholek.numer].size() + sumaDzieciSynow;
        if (obliczanyWierzcholek.numer != numerKorzenia)
        {
            obliczanyWierzcholek.ilePotomkow--;
        }
    }
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
void ObliczaWartoscWierzcholka(Wierzcholek &ja)
{
    ll NajwiekszaDziura = LONG_LONG_MIN;
    ll oIleZwiekszamy = 0;
    if (Graf[ja.numer].size() > 1) //nie jestem w lisciu
    {
        int numerSynaZDziura;
        ll sumaWartosciSynow = 0;
        for (int i = 0; i < Graf[ja.numer].size(); i++) //szukanie najwiekszej dziury
        {
            int numerSynaAnalizowanego = Graf[ja.numer][i];
            if (listaWierzcholkow[numerSynaAnalizowanego].poziom > ja.poziom) //szuka wsrod synow
            {
                sumaWartosciSynow += listaWierzcholkow[numerSynaAnalizowanego].wartoscWypadkowa; //podlicza sume wartosci wypadkowych synow
                ll dziuraOdSyna = listaWierzcholkow[numerSynaAnalizowanego].wartoscWypadkowaNarastajaca;
                if (NajwiekszaDziura < dziuraOdSyna)
                {
                    NajwiekszaDziura = dziuraOdSyna;
                    numerSynaZDziura = numerSynaAnalizowanego;
                }
            }
        }
        ja.wartoscWypadkowa = sumaWartosciSynow - ja.wartoscPoczatkowa;
        ja.wartoscWypadkowaNarastajaca = NajwiekszaDziura + ja.wartoscWypadkowa;
        if (ja.wartoscWypadkowa >= 0) //to znaczy ze ten wierzcholek nie wysyla nic do gory
        {
            ja.iloscOperacji = NajwiekszaDziura;
            for (int i = 0; i < Graf[ja.numer].size(); i++) //zwieksza wartosci synow o nadmiar z dziury
            {
                int numerSynaAnalizowanego = Graf[ja.numer][i];
                if (listaWierzcholkow[numerSynaAnalizowanego].poziom > ja.poziom) //omija ojca
                {
                    if (numerSynaAnalizowanego != numerSynaZDziura) //omija dziure
                    {
                        oIleZwiekszamy += (listaWierzcholkow[numerSynaAnalizowanego].ilePotomkow + 1) * NajwiekszaDziura;
                    }
                }
            }
        }
        else //to znaczy ze ten wierzcholek wysyla do gory
        {
            if (NajwiekszaDziura > -ja.wartoscWypadkowa)
            {
                ja.iloscOperacji = NajwiekszaDziura;
            }
            else
            {
                ja.iloscOperacji = -ja.wartoscWypadkowa;
                oIleZwiekszamy = ja.ilePotomkow * (ja.iloscOperacji);
            }
        }
    }
    else //jestem w lisciu
    {
        NajwiekszaDziura = 0;
        ja.wartoscWypadkowa = -ja.wartoscPoczatkowa;
        ja.wartoscWypadkowaNarastajaca = ja.wartoscWypadkowa;
        ja.iloscOperacji = -ja.wartoscWypadkowa;
    }

    sumaWszystkichOperacji += oIleZwiekszamy;

    sumaWszystkichOperacji += ja.iloscOperacji;

    if (najmniejszyLisc > ja.wartoscPoczatkowa)
        najmniejszyLisc = ja.wartoscPoczatkowa;
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
    ObliczaIlosciPrzodkow(numerKorzenia);
    while (!WierzcholkiDoSprawdzenia.empty())
    {
        int numerWierzcholka = WierzcholkiDoSprawdzenia.back();
        WierzcholkiDoSprawdzenia.pop_back();
        Wierzcholek &wierzcholekObliczony = listaWierzcholkow[numerWierzcholka];
        ObliczaWartoscWierzcholka(wierzcholekObliczony);
        //cout << wierzcholekObliczony.wartoscPoczatkowa << " " << sumaWszystkichOperacji << endl;
        //DrukujeWartosciOdbicWierzcholkow();
    }
    sumaWszystkichOperacji -= najmniejszyLisc;
    cout << "TAK" << endl;
    cout << sumaWszystkichOperacji << endl;
    //DrukujeWartosciOdbicWierzcholkow();
    return 0;
}
