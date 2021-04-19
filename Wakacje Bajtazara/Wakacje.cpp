#include <iostream>
#include <vector>

using namespace std;

// Typy danych

class Wierzcholek
{
public:
    int gdzieProwadzi;
    vector<int> stosWierzcholkowKtoreProwadza;
    int sumaAtrakcyjnosci = 0;
};
class DoOdwiedzenia
{
public:
    int KrokTrasy = 0;
    int Dokad = 0;
};
int n;
int *atrakcyjnoscMiast;
const int MAXINT = 2147483647;

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int DFS(int wierzcholekStartowy, vector<vector<Wierzcholek>> Graf)
{
    // Initially mark all verices as not visited
    vector<int> visited(n + 1, 0);
    vector<DoOdwiedzenia> wierzcholkiDoOdwiedzenia;

    vector<int> Trasa;
    int AtrakcyjnoscTrasy = 0;
    int MaksymalnaAstrakcyjnosc = -1;

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
        //sciaga ze stosu - zdejmuje wierzcholki z dotychczasowej trasy
        //wracamy ze stosu do momentu az sztos bedzie mniejszy do numeru kroku
        while (Trasa.size() >= aktualnyWierzcholek.KrokTrasy)
        {
            int numerWierzcholka = Trasa.back();
            if (Trasa.size() % 2 == 1)
            {
                AtrakcyjnoscTrasy = AtrakcyjnoscTrasy - atrakcyjnoscMiast[numerWierzcholka];
            }

            Trasa.pop_back();
            visited[numerWierzcholka] = 0;
        }
        //dodajemy do trasy wierzcholek do ktorego wchodzimy
        Trasa.push_back(aktualnyWierzcholek.Dokad);

        //zaznaczmy w ze bylismy w wierzcholku
        visited[aktualnyWierzcholek.Dokad] = Trasa.size();

        //zwiekszamy atrakcyjnosc - na potrzeby zadania
        if (Trasa.size() % 2 == 1)
        {
            AtrakcyjnoscTrasy = AtrakcyjnoscTrasy + atrakcyjnoscMiast[aktualnyWierzcholek.Dokad];
            if (MaksymalnaAstrakcyjnosc < AtrakcyjnoscTrasy)
            {
                MaksymalnaAstrakcyjnosc = AtrakcyjnoscTrasy;
                //TODO: przechowac dlugosc i sama trase
            }
        }
        //dopisanie wszystkich kolejnych sasiadow do sprawdzenia
        for (auto i = 0; i < Graf[aktualnyWierzcholek.Dokad].size(); i++)
        {
            if (visited[Graf[aktualnyWierzcholek.Dokad][i].gdzieProwadzi] % 2 == 0) //w parzystych mozemy byc kilka razy - wynika z tresci zadania
            {
                DoOdwiedzenia nowyWierzcholek;
                nowyWierzcholek.Dokad = Graf[aktualnyWierzcholek.Dokad][i].gdzieProwadzi;
                nowyWierzcholek.KrokTrasy = Trasa.size()+1;
                wierzcholkiDoOdwiedzenia.push_back(nowyWierzcholek);
            }
        }
    }
    return MaksymalnaAstrakcyjnosc;
}
int main()
{

    cin >> n; //wczytanie wierzcholka startowego, liczby wierzcholkow i krawedzi

    // Tworzymy tablice dynamiczne
    atrakcyjnoscMiast = new int[n]{0}; // Tablica kosztów dojścia
    vector<vector<Wierzcholek>> Graf;  // Tablica list sąsiedztwa

    // Odczytujemy dane wejściowe
    for (int i = 0; i <= n; i++)
    {
        vector<Wierzcholek> a;
        Graf.push_back(a);
    }
    int atrakcyjnoscMiasta;
    for (int i = 1; i <= n; i++)
    {
        cin >> atrakcyjnoscMiasta; // Odczytujemy krawędź z wagą
        atrakcyjnoscMiast[i] = atrakcyjnoscMiasta;
    }
    int v1, v2;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> v1 >> v2;
        Wierzcholek nowy;
        nowy.gdzieProwadzi = v2;
        Graf[v1].push_back(nowy); // Element dołączamy do listy
        nowy.gdzieProwadzi = v1;
        Graf[v2].push_back(nowy);
    }

    vector<int> KolejkaWierzcholkowDoSprawdzenia;
    bool *WierzcholkiDodane = new bool[n]{false};
    for (int i = 1; i <= n; i++)
    {
        if (Graf[i].size() == 1)
        {
            KolejkaWierzcholkowDoSprawdzenia.push_back(i);
            WierzcholkiDodane[i] = true;
            if (!WierzcholkiDodane[Graf[i][0].gdzieProwadzi])
            {
                KolejkaWierzcholkowDoSprawdzenia.push_back(Graf[i][0].gdzieProwadzi);
                WierzcholkiDodane[Graf[i][0].gdzieProwadzi] = true;
            }
        }
    }
    for (int i = 0; i < KolejkaWierzcholkowDoSprawdzenia.size(); i++)
    {
        int max = DFS(KolejkaWierzcholkowDoSprawdzenia[i], Graf);
        cout << KolejkaWierzcholkowDoSprawdzenia[i] << " " << max << endl;
        cout << endl;
        cout << endl;
    }
    return 0;
}
