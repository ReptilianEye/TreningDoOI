#include <iostream>
#include <vector>

using namespace std;

// Typy danych

class Wierzcholek
{
public:
    int gdzieProwadzi;
    int koszt;
};
class DoOdwiedzenia
{
public:
    int KrokTrasy = 0;
    int Dokad = 0;
    int koszt;
};
class ZnalezionaRestauracja
{
public:
    int numerWierzcholka = 0;
    int kosztDojscia = 0;
};
int n;
int *RestauracjiDlaWierzcholkow;
const int MAXINT = 2147483647;

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
void WstawiaPosortowanie(vector<ZnalezionaRestauracja> &Tablica, ZnalezionaRestauracja element)
{
    if (Tablica.empty())
    {
        Tablica.push_back(element);
        return;
    }
    for (int i = 0; i < Tablica.size(); i++)
    {
        if (Tablica[i].numerWierzcholka > element.numerWierzcholka)
        {
            Tablica.insert(Tablica.begin() + i, element);
            return;
        }
    }
}
void DFS(int wierzcholekStartowy, int szukanyRodzajRestauracji, vector<ZnalezionaRestauracja> &TablicaWynikow, vector<vector<Wierzcholek>> Graf)
{
    // Initially mark all verices as not visited
    //vector<bool> visited(n + 1, 0);
    bool *visited = new bool[n + 1]{false};
    vector<DoOdwiedzenia> wierzcholkiDoOdwiedzenia;

    vector<DoOdwiedzenia> Trasa;
    int KosztTrasy = 0;

    //wstawienie na stos punktu startowego
    DoOdwiedzenia Wierzcholek;
    Wierzcholek.KrokTrasy = 1;
    Wierzcholek.Dokad = wierzcholekStartowy;
    wierzcholkiDoOdwiedzenia.push_back(Wierzcholek);

    while (!wierzcholkiDoOdwiedzenia.empty())
    {
        DoOdwiedzenia aktualnyWierzcholek;

        // pobieramy wierzcholek do przerobienia
        aktualnyWierzcholek = wierzcholkiDoOdwiedzenia.back();
        wierzcholkiDoOdwiedzenia.pop_back();

        //petla ktora odpowiada za wycofanie z iteracyjnej rekurencji
        //zdejmuje ze stosu - zdejmuje wierzcholki z dotychczasowej trasy
        //wracamy ze stosu do momentu az sztos bedzie mniejszy do numeru kroku
        while (Trasa.size() >= aktualnyWierzcholek.KrokTrasy)
        {
            DoOdwiedzenia numerWierzcholka = Trasa.back();
            KosztTrasy = KosztTrasy - numerWierzcholka.koszt;
            Trasa.pop_back();
        }
        //dodajemy do trasy wierzcholek do ktorego wchodzimy
        Trasa.push_back(aktualnyWierzcholek);

        //zaznaczmy w ze bylismy w wierzcholku
        visited[aktualnyWierzcholek.Dokad] = true;

        //zwiekszamy koszt - na potrzeby zadania
        KosztTrasy = KosztTrasy + aktualnyWierzcholek.koszt;
        if (RestauracjiDlaWierzcholkow[aktualnyWierzcholek.Dokad] == szukanyRodzajRestauracji)
        {
            ZnalezionaRestauracja znalezionaRestauracja;
            znalezionaRestauracja.kosztDojscia = KosztTrasy;
            znalezionaRestauracja.numerWierzcholka = aktualnyWierzcholek.Dokad;
            WstawiaPosortowanie(TablicaWynikow,znalezionaRestauracja);
        }

        //dopisanie wszystkich kolejnych sasiadow do sprawdzenia
        for (auto i = 0; i < Graf[aktualnyWierzcholek.Dokad].size(); i++)
        {
            if (!visited[Graf[aktualnyWierzcholek.Dokad][i].gdzieProwadzi])
            {
                DoOdwiedzenia nowyWierzcholek;
                nowyWierzcholek.Dokad = Graf[aktualnyWierzcholek.Dokad][i].gdzieProwadzi;
                nowyWierzcholek.koszt = Graf[aktualnyWierzcholek.Dokad][i].koszt;
                nowyWierzcholek.KrokTrasy = Trasa.size() + 1;
                wierzcholkiDoOdwiedzenia.push_back(nowyWierzcholek);
            }
        }
    }
}
int main()
{

    int iloscRodzajiRestauracji;
    cin >> n >> iloscRodzajiRestauracji; //wczytanie wierzcholka startowego, liczby wierzcholkow i krawedzi

    // Tworzymy tablice dynamiczne
    RestauracjiDlaWierzcholkow = new int[n + 1]{0}; // Tablica kosztów dojścia
    bool *CzyRestaracjaIstnieje = new bool[iloscRodzajiRestauracji+1]{false};
    vector<vector<Wierzcholek>> Graf; // Tablica list sąsiedztwa

    // Odczytujemy dane wejściowe
    for (int i = 0; i <= n; i++)
    {
        vector<Wierzcholek> a;
        Graf.push_back(a);
    }

    int restauracja;
    for (int i = 1; i <= n; i++)
    {
        cin >> restauracja;
        RestauracjiDlaWierzcholkow[i] = restauracja;
        CzyRestaracjaIstnieje[restauracja] = true;
    }
    int v1, v2, waga;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> v1 >> v2 >> waga;
        Wierzcholek nowy;
        nowy.gdzieProwadzi = v2;
        nowy.koszt = waga;
        Graf[v1].push_back(nowy); // Element dołączamy do listy
        nowy.gdzieProwadzi = v1;
        Graf[v2].push_back(nowy);
    }

    
    int liczbaOperacji;
    cin >> liczbaOperacji;
    for (int i = 0; i < liczbaOperacji; i++)
    {
        int pierwszyWierzcholekPoczatkowy, drugiWierzcholekPoczatkowy, szukanaRestaruacja;
        cin >> pierwszyWierzcholekPoczatkowy >> drugiWierzcholekPoczatkowy >> szukanaRestaruacja;
        vector<ZnalezionaRestauracja> PierwszeZnalezioneRestauracje;
        vector<ZnalezionaRestauracja> DrugieZnalezioneRestauracje;
        if (!CzyRestaracjaIstnieje[szukanaRestaruacja])
        {
            cout << -1 << endl;
            continue;
        }
        DFS(pierwszyWierzcholekPoczatkowy, szukanaRestaruacja, PierwszeZnalezioneRestauracje, Graf);
        DFS(drugiWierzcholekPoczatkowy, szukanaRestaruacja, DrugieZnalezioneRestauracje, Graf);
        int najmniejszyKoszt = MAXINT;
        for (int i = 0; i < PierwszeZnalezioneRestauracje.size(); i++)
        {
            int koszt = PierwszeZnalezioneRestauracje[i].kosztDojscia + DrugieZnalezioneRestauracje[i].kosztDojscia;
            if (najmniejszyKoszt > koszt)
                najmniejszyKoszt = koszt;
        }
        cout << najmniejszyKoszt << endl;
    }
    return 0;
}
