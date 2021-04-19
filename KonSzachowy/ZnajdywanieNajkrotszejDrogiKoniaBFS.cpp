#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>

using namespace std;

class PoleNaSzachownicy
{
public:
    int wspX = -1;
    int wspY = -1;
    int numer = -1;
};
int n, m;
int iloscRuchow = 0;
int pozycje[8][2] =
    {
        {2, 1},
        {2, -1},
        {-2, 1},
        {-2, -1},
        {1, 2},
        {1, -2},
        {-1, 2},
        {-1, -2}};
// Procedura szukania ścieżki
// vs - numer wierzchołka startowego
// vk - numer wierzchołka końcowego
//----------------------------------

void BFSDlaKoniaSzachowego(bool **Odwiedzone, PoleNaSzachownicy vs, PoleNaSzachownicy vk, int n, int m)
{
    bool CzyZnalezlismySciezke = false;
    vector<PoleNaSzachownicy> Q;
    Q.push_back(vs);
    PoleNaSzachownicy P[n*m];
    PoleNaSzachownicy v;
    while (!Q.empty())
    {
        iloscRuchow++;
        v = Q.front();
        Q.erase(Q.begin());
        Odwiedzone[v.wspX][v.wspY] = true;
        if (v.wspX == vk.wspX && v.wspY == vk.wspY)
        {
            CzyZnalezlismySciezke = true;
            break;
        }
        for (auto poz : pozycje)
        {
            int nowaPozX = vs.wspX + poz[0];
            int nowaPozY = vs.wspY + poz[1];
            if (nowaPozX >= 0 && nowaPozX < m && nowaPozY >= 0 && nowaPozY < n)
            {
                if (!Odwiedzone[nowaPozX][nowaPozY])
                {
                    PoleNaSzachownicy nowySasiad;
                    nowySasiad.wspX = nowaPozX;
                    nowySasiad.wspY = nowaPozY;
                    nowySasiad.numer = v.numer+1;
                    Q.push_back(nowySasiad);
                }
            }
        }
    }
    if (!CzyZnalezlismySciezke)
        cout << "BRAK"; // Ścieżka nie została znaleziona
    else
        while (v.numer > -1)
        {
            cout << setw(3) << v.numer; // Wypisujemy wierzchołki ścieżki
            v = P[v.numer];             // Cofamy się do poprzedniego wierzchołka ścieżki
        }
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
    //********** wczytywanie wejscia
    cin >> n >> m;
    bool **OdwiedzoneNaSzachownicy = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        OdwiedzoneNaSzachownicy[i] = new bool[m];
    }
    int pole;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> pole;
            if (pole == -2)
                OdwiedzoneNaSzachownicy[i][j] = true;
            else
                OdwiedzoneNaSzachownicy[i][j] = false;
        }
    }

    PoleNaSzachownicy start;
    cin >> start.wspX >> start.wspY;
    PoleNaSzachownicy koniec;
    cin >> koniec.wspX >> koniec.wspY;
    BFSDlaKoniaSzachowego(OdwiedzoneNaSzachownicy, start, koniec, n, m);
    return 0;
}