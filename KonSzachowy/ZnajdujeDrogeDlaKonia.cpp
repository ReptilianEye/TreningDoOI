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

PoleNaSzachownicy SymulujeKonia(PoleNaSzachownicy start, int X, int Y)
{
    PoleNaSzachownicy nowyPunkt;
    nowyPunkt.wspX = start.wspX + X;
    nowyPunkt.wspY = start.wspY + Y;
    return nowyPunkt;
}

void ZnajdujeDrogeDlaKonia(PoleNaSzachownicy start, PoleNaSzachownicy koniec, int Szachownica[][5], int m, int n)
{
    iloscRuchow++;
    //ZnajdywanieSasiadow
    PoleNaSzachownicy sasiedzi[8];
    sasiedzi[0] = SymulujeKonia(start, 2, 1);
    sasiedzi[1] = SymulujeKonia(start, 2, -1);
    sasiedzi[2] = SymulujeKonia(start, -2, 1);
    sasiedzi[3] = SymulujeKonia(start, -2, -1);
    sasiedzi[4] = SymulujeKonia(start, 1, 2);
    sasiedzi[5] = SymulujeKonia(start, 1, -2);
    sasiedzi[6] = SymulujeKonia(start, -1, 2);
    sasiedzi[7] = SymulujeKonia(start, -1, -2);
    for (int i = 0; i < 8; i++)
    {
        if (sasiedzi[i].wspX == koniec.wspX && sasiedzi[i].wspY == koniec.wspY)
        {
            cout << sasiedzi[i].wspX << sasiedzi[i].wspY;
            return;
        }
        if (sasiedzi[i].wspX > m || sasiedzi[i].wspY > n)
            continue;
        if (Szachownica[sasiedzi[i].wspX][sasiedzi[i].wspY] == 0)
            Szachownica[sasiedzi[i].wspX][sasiedzi[i].wspY] = iloscRuchow;
    }
    for (auto sasiad : sasiedzi)
    {
        ZnajdujeDrogeDlaKonia(sasiad, koniec, Szachownica, m, n);
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
    ZnajdujeDrogeDlaKonia(start, koniec, Szachownica, m, n);

    cout << iloscRuchow << endl;
    return 0;
}