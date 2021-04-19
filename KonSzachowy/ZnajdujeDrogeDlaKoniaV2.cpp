#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

class PoleNaSzachownicy
{
public:
    int wspX = -1;
    int wspY = -1;
    //bool CzyOdwiedzony = false;
};
int iloscRuchow = 0;
int pozycje1[4] = {2, -2, 1, -1};
int pozycje2[4] = {1, -1, 2, -2};

void ZnajdujeMiejscaSkoku(PoleNaSzachownicy start, PoleNaSzachownicy koniec, bool Odwiedzone[][5], int Szachownica[][5], int m, int n)
{
    Odwiedzone[start.wspX][start.wspY] = true;
    if (start.wspX == koniec.wspX && start.wspY == koniec.wspY)
    {
        cout << start.wspX << start.wspY << endl;
        return;
    }
    vector<PoleNaSzachownicy> sasiedzi;
    for (auto poz1 : pozycje1)
    {
        for (auto poz2 : pozycje2)
        {
            int suma = poz1 + poz2;
            if (suma == 0 || suma == 2 || suma == 4)
                continue;
            int nowaPozX = start.wspX + poz1;
            int nowaPozY = start.wspY + poz2;
            if (nowaPozX >= 0 && nowaPozX < m && nowaPozY >= 0 && nowaPozY < n)
            {
                if (Szachownica[nowaPozX][nowaPozY] == 0)
                    if (!Odwiedzone[nowaPozX][nowaPozY])
                    {
                        PoleNaSzachownicy nowySasiad;
                        nowySasiad.wspX = nowaPozX;
                        nowySasiad.wspY = nowaPozY;
                        sasiedzi.push_back(nowySasiad);
                    }
            }
        }
    }
    for (auto sasiad : sasiedzi)
    {
        ZnajdujeMiejscaSkoku(sasiad, koniec, Odwiedzone, Szachownica, m, n);
    }
}

int main()
{
    //********** wczytywanie wejscia
    int m, n;
    cin >> m;
    n = 5;
    int Szachownica[m][5];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> Szachownica[i][j];
        }
    }
    PoleNaSzachownicy start;
    cin >> start.wspX >> start.wspY;
    PoleNaSzachownicy koniec;
    cin >> koniec.wspX >> koniec.wspY;
    bool Odwiedzone[m][5] = {false};
    ZnajdujeMiejscaSkoku(start, koniec, Odwiedzone, Szachownica, m, n);
    cout << iloscRuchow << endl;
    return 0;
}