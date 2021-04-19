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
vector<PoleNaSzachownicy> NajkrotszaSciezka;
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

void drukujeTablice(int dlugoscTablicyWDol, int dlugoscTablicyWPrawo, int Tablica[][5])
{
    for (int i = 0; i < dlugoscTablicyWDol; i++)
    {
        for (int j = 0; j < dlugoscTablicyWPrawo; j++)
        {
            if (Tablica[i][j] == -1)
                cout << "0";
            else if (Tablica[i][j] == -2)
                cout << "X";
            else
                cout << Tablica[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
void ZnajdujeMiejscaSkoku(PoleNaSzachownicy start, PoleNaSzachownicy koniec, vector<PoleNaSzachownicy> sciezka, int glebokosc, int Szachownica[][5], int m, int n)
{
    sciezka.push_back(start);
    Szachownica[start.wspX][start.wspY] = glebokosc;
    drukujeTablice(5, 5, Szachownica);
    if (start.wspX == koniec.wspX && start.wspY == koniec.wspY)
    {
        if (sciezka.size() < NajkrotszaSciezka.size() || NajkrotszaSciezka.size() == 0)
        {
            iloscRuchow = glebokosc;
            NajkrotszaSciezka = sciezka;
            return;
        }
    }
    vector<PoleNaSzachownicy> sasiedzi;

    for (auto poz : pozycje)
    {
        if (sciezka.size() >= NajkrotszaSciezka.size() && NajkrotszaSciezka.size() != 0)
            break;
        int nowaPozX = start.wspX + poz[0];
        int nowaPozY = start.wspY + poz[1];
        if (nowaPozX >= 0 && nowaPozX < m && nowaPozY >= 0 && nowaPozY < n)
        {
            if (Szachownica[nowaPozX][nowaPozY] == -1 || Szachownica[nowaPozX][nowaPozY] > Szachownica[start.wspX][start.wspY])
            {
                PoleNaSzachownicy nowySasiad;
                nowySasiad.wspX = nowaPozX;
                nowySasiad.wspY = nowaPozY;
                ZnajdujeMiejscaSkoku(nowySasiad, koniec, sciezka, glebokosc + 1, Szachownica, m, n);
            }
        }
    }
    return;
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
    vector<PoleNaSzachownicy> sciezka;
    ZnajdujeMiejscaSkoku(start, koniec, sciezka, 1, Szachownica, m, n);
    cout << iloscRuchow << endl;
    for (auto punkt : NajkrotszaSciezka)
    {
        cout << punkt.wspX << punkt.wspY << endl;
    }
    return 0;
}