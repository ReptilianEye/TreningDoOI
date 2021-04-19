#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

void ZwracaLiczbyPierwszeZPrzedzialuSitemEratostenesaV2(long granicaPrzedzialu)
{

    long *PrzedzialLiczb = new long[granicaPrzedzialu + 1];     //funkcja dziala podobnie jak ta wyzej tylko ze uzywa bool zamiast int
    long ostatniaDoSprawdzenia = (long)sqrt(granicaPrzedzialu); //ostatnia liczbe ktora sprawdzi bedzie pierwiastek z ostatniej liczby w ciagu
    vector<vector<long>> Kandydaci;
    vector<long> tym;
    for (int i = 0; i <= granicaPrzedzialu; i++)
        Kandydaci.push_back(tym);

    for (long wskaznik = 2; wskaznik <= ostatniaDoSprawdzenia; wskaznik++)
    {

        long wielokrotonosc = wskaznik * wskaznik;
        while (wielokrotonosc <= granicaPrzedzialu)
        {
            PrzedzialLiczb[wielokrotonosc]++; //funkcja nadaje wartosc true kazdej wielokrotnosci - czyli liczbie zlozonej (nie-pierwszej)
            Kandydaci[wielokrotonosc].push_back(wskaznik);
            wielokrotonosc = wielokrotonosc + wskaznik; //funkcja zamiast mnozenia liczby dodaje do siebie wartosc pierwszej
        }
    }
    int Liczba1NajwiecejDzielnikow = 0;
    for (int i = 0; i < Kandydaci.size(); i++)
    {
        if(Kandydaci[Liczba1NajwiecejDzielnikow].size() < Kandydaci[i].size())
        {
            Liczba1NajwiecejDzielnikow = i;
        }
    }
    int Liczba2Najwiecej = 0;
    for(int i = Kandydaci.size(); i > 0; i++)
    {
        for(int j = 0; j < Kandydaci[Liczba1NajwiecejDzielnikow].size();j++)
        {
            int k = j;
        }
    }
        vector<long> Pierwsze;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
    int n, m, k;

    cin >> n >> m >> k; // Czytamy liczbę wierzchołków i krawędzi

    bool **TablicaPolaczen = new bool *[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            TablicaPolaczen[i] = new bool[m];
            TablicaPolaczen[i][j] = false;
        }
    TablicaPolaczen[0][0] = true;

    if (ZnajdujePolaczenia(n, m, k, TablicaPolaczen))
    {
        cout << "TAK" << endl;
        for (int i = 0; i < listaSasiedztwa.size(); i++)
        {
            for (int j = 0; j < listaSasiedztwa[i].size(); j++)
            {
                cout << wierzcholki[i].x + 1 << " " << wierzcholki[i].y + 1 << " " << listaSasiedztwa[i][j].x + 1 << " " << listaSasiedztwa[i][j].y + 1 << endl;
            }
        }
    }
    else
    {
        cout << "NIE" << endl;
    }

    return 0;
}
