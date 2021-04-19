#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Strzal
{
public:
    long long wartosc;
    long long sumaStrzalowDoTejPory;
};

int n;
vector<long long> Tablica;
//long long *Tablica = new long long[n];
const int _maxN = 500000;

int point = 0;
int ileRazyWywolana = 0;
long long circular_shift(int x)
{
    ileRazyWywolana++;

    point += x;
    point %= n;
    return Tablica[point];
    // for (int i = 0; i < x; i++)
    // {
    //     long long poczatek = Tablica[0];
    //     Tablica.erase(Tablica.begin());
    //     Tablica.push_back(poczatek);
    // }
    return Tablica[0];
}
long long ZwracaKiedyWartoscJuzWystapila(vector<Strzal> &listaStrzalow, long long wartosc, long long aktualnaSumaStrzalow)
{
    for (int i = 0; i < listaStrzalow.size(); i++)
    {
        if (listaStrzalow[i].wartosc == wartosc)
        {
            return aktualnaSumaStrzalow - listaStrzalow[i].sumaStrzalowDoTejPory;
        }
    }
    Strzal nowy;
    nowy.sumaStrzalowDoTejPory = aktualnaSumaStrzalow;
    nowy.wartosc = wartosc;
    listaStrzalow.push_back(nowy);
    return -1;
}
long long OkreslDlugoscCiagu(int dolnyPrzedzial)
{
    vector<Strzal> listaStrzalow;
    long long sumaDlugoscStrzalow = 0;
    int aktualnyDolnyPrzedzial = 0;

    long long start = circular_shift(0);
    Strzal pierwszyStrzal;
    pierwszyStrzal.sumaStrzalowDoTejPory = 0;
    pierwszyStrzal.wartosc = start;
    listaStrzalow.push_back(pierwszyStrzal);

    long long poprzedni = start;

    bool CzyBylUpadek = false;

    for (long long i = 0; i < 100; i++)
    {
        long long dlugoscStrzalu = pow(2, i);
        if (i == 0)
            dlugoscStrzalu += dolnyPrzedzial;
        sumaDlugoscStrzalow += dlugoscStrzalu;
        long long strzal = circular_shift(dlugoscStrzalu);

        long long WKtorymKrokuWystapila = ZwracaKiedyWartoscJuzWystapila(listaStrzalow, strzal, sumaDlugoscStrzalow);
        if (WKtorymKrokuWystapila != -1)
            return WKtorymKrokuWystapila;

        if (strzal == poprzedni)
            return dlugoscStrzalu;

        if (CzyBylUpadek)
        {
            if (strzal >= start || strzal < poprzedni)
            {
                return OkreslDlugoscCiagu(aktualnyDolnyPrzedzial);
            }
            if (strzal < start)
            {
                aktualnyDolnyPrzedzial += dlugoscStrzalu;
                poprzedni = strzal;
                continue;
            }
        }
        else
        {

            if (strzal > poprzedni)
            {
                aktualnyDolnyPrzedzial += dlugoscStrzalu;
                poprzedni = strzal;
                continue;
            }
            if (strzal < poprzedni && strzal <= start)
            {
                CzyBylUpadek = true;
                aktualnyDolnyPrzedzial += dlugoscStrzalu;
                poprzedni = strzal;
                continue;
            }
            if (strzal > start)
            {
                return OkreslDlugoscCiagu(aktualnyDolnyPrzedzial);
            }
        }
    }
}

void WczytujeTablice()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        long long wartosc;
        cin >> wartosc;
        Tablica.push_back(wartosc);
    }
    int przesuniecie;
    cin >> przesuniecie;
    circular_shift(przesuniecie);
}

int main()
{
    WczytujeTablice();
    long long wynik = OkreslDlugoscCiagu(0);
    cout << wynik << endl;
    cout << "Wywolanie funkcji " << ileRazyWywolana << endl;
}
