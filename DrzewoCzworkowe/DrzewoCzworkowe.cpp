#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;
class Punkt
{
public:
    int wspX = 1;
    int wspY = 1;
};
string kod;
int **Tablica;
int wymiarTablicy;
int wskaznik = -1;

int pozycje[4][2] =
    {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}};
void drukujeTablice(int wymiarTablicy, int **Tablica)
{

    for (int kolumna = 0; kolumna < wymiarTablicy; kolumna++)
    {
        for (int wiersz = 0; wiersz < wymiarTablicy; wiersz++)
        {
            cout << Tablica[wiersz][kolumna] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void KolorujeTablice(Punkt LewyGornyRog, Punkt PrawyDolnyRog, int wartosc, int **Tablica)
{
    for (int i = LewyGornyRog.wspX; i <= PrawyDolnyRog.wspX; i++)
        for (int j = LewyGornyRog.wspY; j <= PrawyDolnyRog.wspY; j++)

        {
            Tablica[i - 1][j - 1] = wartosc;
        }
}
void BFSTablicy(int **Tablica, int wymiarTablicy, int kolorWyspy)
{
    vector<Punkt> Q;
    Punkt v;
    int licznikWysep = 0;
    long wielkoscObszaru = 0;
    long NajwiekszaWielkosc = 0;
    for (int i = 0; i < wymiarTablicy; i++)
    {
        for (int j = 0; j < wymiarTablicy; j++)
        {
            Punkt pole;
            if (Tablica[i][j] == 1)
            {
                licznikWysep++;
                pole.wspX = i;
                pole.wspY = j;
                Q.push_back(pole);
                while (!Q.empty())
                {
                    v = Q.front();
                    Q.erase(Q.begin());
                    for (auto poz : pozycje)
                    {
                        int nowaPozX = v.wspX + poz[0];
                        int nowaPozY = v.wspY + poz[1];
                        if (nowaPozX >= 0 && nowaPozX < wymiarTablicy && nowaPozY >= 0 && nowaPozY < wymiarTablicy)
                        {
                            if (Tablica[nowaPozX][nowaPozY] == 1)
                            {
                                wielkoscObszaru++;
                                Punkt nowySasiad;
                                nowySasiad.wspX = nowaPozX;
                                nowySasiad.wspY = nowaPozY;
                                Tablica[nowySasiad.wspX][nowySasiad.wspY] = kolorWyspy;
                                Q.push_back(nowySasiad);
                            }
                        }
                    }
                }
                if (NajwiekszaWielkosc < wielkoscObszaru)
                    NajwiekszaWielkosc = wielkoscObszaru;
                wielkoscObszaru = 0;
                drukujeTablice(wymiarTablicy, Tablica);

                kolorWyspy++;
            }
        }
    }
    //licznikPol = licznikPol % pow(10, 9) + 7;
    cout << licznikWysep << endl;
    cout << NajwiekszaWielkosc << endl;
}
void RozbijaKodTablicyRekurencyjnie(Punkt jeden, Punkt dwa)
{
    wskaznik++;
    if (kod[wskaznik] == '4')
    {
        for (int cwiartka = 1; cwiartka <= 4; cwiartka++)
        {
            wskaznik++;

            Punkt NowyLewyGorny, NowyPrawyDolny;
            if (cwiartka == 1)
            {
                NowyLewyGorny = jeden;
                NowyPrawyDolny.wspX = jeden.wspX + (dwa.wspX - jeden.wspX) / 2;
                NowyPrawyDolny.wspY = jeden.wspY + (dwa.wspY - jeden.wspY) / 2;
            }
            if (cwiartka == 2)
            {
                NowyLewyGorny.wspX = jeden.wspX + (dwa.wspX - jeden.wspX + 1) / 2;
                NowyLewyGorny.wspY = jeden.wspY;

                NowyPrawyDolny.wspX = dwa.wspX;
                NowyPrawyDolny.wspY = jeden.wspY + (dwa.wspY - jeden.wspY + 1) / 2 - 1;
            }
            if (cwiartka == 3)
            {
                NowyLewyGorny.wspX = jeden.wspX;
                NowyLewyGorny.wspY = jeden.wspY + (dwa.wspY - jeden.wspY + 1) / 2;

                NowyPrawyDolny.wspX = jeden.wspX + (dwa.wspX - jeden.wspX + 1) / 2 - 1;
                NowyPrawyDolny.wspY = dwa.wspY;
            }
            if (cwiartka == 4)
            {
                NowyLewyGorny.wspX = jeden.wspX + (dwa.wspX - jeden.wspX + 1) / 2;
                NowyLewyGorny.wspY = jeden.wspY + (dwa.wspY - jeden.wspY + 1) / 2;

                NowyPrawyDolny = dwa;
            }

            if (kod[wskaznik] == '4')
            {
                wskaznik--; // chcemy w rekurencyjnej funkjci przecytac 4 jeszcze raz
                RozbijaKodTablicyRekurencyjnie(NowyLewyGorny, NowyPrawyDolny);
                continue;
            }

            if (kod[wskaznik] == '1')
            {
                KolorujeTablice(NowyLewyGorny, NowyPrawyDolny, 1, Tablica);
                // drukujeTablice(wymiarTablicy, Tablica);
                // cout << endl;
                continue;
            }
            if (kod[wskaznik] == '0')
                continue;
        }
        return;
    }
    if (kod[wskaznik] == '1')
    {
        KolorujeTablice(jeden, dwa, 1, Tablica);
        drukujeTablice(wymiarTablicy, Tablica);
        cout << endl;
        return;
    }
    if (kod[wskaznik] == '0')
        return;
}

int main()
{
    int m;

    cin >> m;

    wymiarTablicy = pow(2, m);
    Tablica = new int *[wymiarTablicy];
    for (int i = 0; i < wymiarTablicy; i++)
    {
        Tablica[i] = new int[wymiarTablicy]{0};
    }
    Punkt LewyGornyRog, PrawyDolnyRog;
    PrawyDolnyRog.wspX = wymiarTablicy;
    PrawyDolnyRog.wspY = wymiarTablicy;
    cin >> kod;
    RozbijaKodTablicyRekurencyjnie(LewyGornyRog, PrawyDolnyRog);
    drukujeTablice(wymiarTablicy, Tablica);
    BFSTablicy(Tablica, wymiarTablicy, 10);

    return 0;
}
