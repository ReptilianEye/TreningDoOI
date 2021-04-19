#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Wierzcholek
{
public:
    int x = 0;
    int y = 0;
    int numer = 0;
};

vector<vector<Wierzcholek>> listaSasiedztwa;
vector<Wierzcholek> wierzcholki;

bool ZnajdujePolaczenia(int n, int m, int k, bool **TablicaPolaczen)
{
    vector<Wierzcholek> Q;

    int licznikWzietych = 0;
    int ileMozemyWziac = 1;
    int ileSasiadow = 0;
    int dlugosc = 0;
    bool CzyZmienilo = false;
    int licznikWierzcholkow = 0;

    Wierzcholek start;
    Q.push_back(start); // W kolejce umieszczamy wierzchołek startowy

    while (!Q.empty())
    {
        Wierzcholek v = Q.front(); // Pobieramy z kolejki wierzchołek v
        Q.erase(Q.begin());
        wierzcholki.push_back(v);
        vector<Wierzcholek> sasiedzi;
        listaSasiedztwa.push_back(sasiedzi);

        // Przeglądamy sąsiadów wierzchołka v
        if (dlugosc > k)
            return false;

        Wierzcholek nowy;

        if (v.y + 1 < m)
            if (TablicaPolaczen[v.x][v.y + 1] == false)
            {
                licznikWierzcholkow++;
                nowy = v;
                nowy.y++;
                nowy.numer = licznikWierzcholkow;
                TablicaPolaczen[nowy.x][nowy.y] = true;
                listaSasiedztwa[v.numer].push_back(nowy);
                Q.push_back(nowy);
                ileSasiadow++;
                CzyZmienilo = true;
            }
        if (v.x + 1 < n)
            if (TablicaPolaczen[v.x + 1][v.y] == false)
            {
                licznikWierzcholkow++;
                nowy = v;
                nowy.x++;
                nowy.numer = licznikWierzcholkow;
                TablicaPolaczen[nowy.x][nowy.y] = true;
                listaSasiedztwa[v.numer].push_back(nowy);
                Q.push_back(nowy);
                ileSasiadow++;
                CzyZmienilo = true;
            }
        licznikWzietych++;
        if (licznikWzietych == ileMozemyWziac)
        {
            if (!CzyZmienilo)
                break;
            dlugosc++;
            licznikWzietych = 0;
            ileMozemyWziac = ileSasiadow;
            ileSasiadow = 0;
        }
    }
    return true;
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
