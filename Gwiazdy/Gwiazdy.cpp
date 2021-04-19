#include <iostream>
#include <vector>

using namespace std;

// Typy danych
const int MAXINT = 2147483647;
int n;
long long Koszt = 0;
int LicznikOdwiedzonych = 1;
int *Galaktyka;
vector<int> Trasa;
// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int ZnajdujeWolneMiejsce(char kierunek, int wskaznik)
{
    if (kierunek == 'L')
    {
        for (int i = wskaznik; i <= n; i++)             //idzie w prawa strone i znajduje miejsce gdzie gwiazda byla jeszcze nie odwiedzona
            if (Galaktyka[i] == 0)
                return i;
    }
    else
    {
        for (int i = wskaznik; i > 0; i--)              //idzie w lewa strone i znajduje miejsce gdzie gwiazda byla jeszcze nie odwiedzona
            if (Galaktyka[i] == 0)
                return i;
    }
    return -1;
}
//odwraca kolejnosc wierzcholkow i dodaje je do Trasy
void OdwracaIDodajeDoTrasy(vector<int> stos)
{
    while (!stos.empty())
    {
        Trasa.push_back(stos.back());           
        stos.pop_back();
    }
}
//Odwiedza gwiazdy i zwraca wolny idex nieodwiedzonej gwiazdy
int OdwiedzaGwiazdyIZwracaWolnyIndex(char kierunek, int wskaznik, int iloscDoOdwiedzenia)
{
    int licznikDoNumeru;
    int licznikOdwiedzonych = 0;
    int i = wskaznik;
    vector<int> stos;
    if (kierunek == 'L')
    {
        licznikDoNumeru = LicznikOdwiedzonych + iloscDoOdwiedzenia;

        while (licznikOdwiedzonych < iloscDoOdwiedzenia)
        {
            i = ZnajdujeWolneMiejsce(kierunek, i);          
            licznikOdwiedzonych++;
            Galaktyka[i] = licznikDoNumeru;             //oznacza wierzcholki jako odwiedzone idac od granic galaktyki
            licznikDoNumeru--;
            stos.push_back(i);          //poniewaz gwiazdy sa dodawane w odwroconej kolejnosci, dodajemy je na stos aby potem dodac je do trasy w poprawnej kolejnosci
        }
    }
    if (kierunek == 'P')
    {
        licznikDoNumeru = LicznikOdwiedzonych + iloscDoOdwiedzenia;
        while (licznikOdwiedzonych < iloscDoOdwiedzenia)
        {
            i = ZnajdujeWolneMiejsce(kierunek, i);
            licznikOdwiedzonych++;
            Galaktyka[i] = licznikDoNumeru;         //oznacza wierzcholki jako odwiedzone idac od granic galaktyki
            licznikDoNumeru--;
            stos.push_back(i);      //poniewaz gwiazdy sa dodawane w odwroconej kolejnosci, dodajemy je na stos aby potem dodac je do trasy w poprawnej kolejnosci
        }
    }
    LicznikOdwiedzonych += iloscDoOdwiedzenia;
    OdwracaIDodajeDoTrasy(stos);
    return ZnajdujeWolneMiejsce(kierunek, i);
}
//Znajduje najmniejsza roznice = najmniejszy koszt zmiany kierunku na nieoptymalny
void ZnajdujeNajlepszaZmianeKierunku(int ileMiejscNaZnalezienie, long long *TablicaKosztow, char naCoTrzebaZmienic, vector<char> &listaKierunkow)
{
    int najmniejszaRoznica = MAXINT;
    int pozycjaNajmniejszej = -1;
    for (int i = 1; i <= ileMiejscNaZnalezienie; i++)               
    {
        if (najmniejszaRoznica > TablicaKosztow[i])
        {
            najmniejszaRoznica = TablicaKosztow[i];
            pozycjaNajmniejszej = i;
        }
    }
    listaKierunkow[pozycjaNajmniejszej] = naCoTrzebaZmienic;
    Koszt += najmniejszaRoznica;
}

int main()
{

    int start;
    cin >> n >> start;

    // Tworzymy tablice dynamiczne
    Galaktyka = new int[n + 1]{0};
    long long *TablicaKosztow = new long long[n]{MAXINT};

    Galaktyka[start] = LicznikOdwiedzonych; //ustawiamy start
    Trasa.push_back(start);

    vector<char> listaKierunkow;
    listaKierunkow.push_back('S'); //wstawiamy S jako "zapychacz" bo numerujemy od 1

    // Odczytujemy dane wejściowe
    int iloscLewych = 0;
    int iloscPrawych = 0;

    bool CzyWystapilLewy = false;
    bool CzyWystapilPrawy = false;
    for (int i = 1; i < n; i++)
    {
        int kosztLewy, kosztPrawy;
        cin >> kosztLewy >> kosztPrawy;
        Koszt += min(kosztLewy,kosztPrawy);
        if (kosztLewy <= kosztPrawy)
        {
            CzyWystapilLewy = true;
            if (!CzyWystapilPrawy)
            {
                iloscLewych++; //podliczamy ile razy pojdziemy w jednym kierunku
            }
            listaKierunkow.push_back('L');
            TablicaKosztow[i] = kosztPrawy - kosztLewy;         //obliczamy roznice kosztow
        }
        else
        {
            CzyWystapilPrawy = true;
            if (!CzyWystapilLewy)
            {
                iloscPrawych++; //podliczamy ile razy pojdziemy w jednym kierunku
            }
            TablicaKosztow[i] = kosztLewy - kosztPrawy;         //obliczamy roznice kosztow
            listaKierunkow.push_back('P');
        }
    }
    listaKierunkow.push_back('K');                  //dodajemy koniec listy jako wartownik
    int iloscMiejscPoLewej = start - 1;
    int iloscMiejscPoPrawej = n - start;            //wyliczamy ilosc miejsc ktore sa po lewej i prawej stronie od startu
    if (iloscLewych > iloscMiejscPoLewej)           //i sprawdzamy czy ilosc ruchow w jedynym kierunku ktore wczesniej obliczylismy, sie miesci
    {
        ZnajdujeNajlepszaZmianeKierunku(iloscMiejscPoLewej + 1, TablicaKosztow, 'P', listaKierunkow);       //jesli tak nie jest szukamy najmniejszej roznicy i zamieniamy kierunek
    }                                                                                               
    else if (iloscPrawych > iloscMiejscPoPrawej)
    {
        ZnajdujeNajlepszaZmianeKierunku(iloscMiejscPoPrawej + 1, TablicaKosztow, 'L', listaKierunkow);
    }
    int wskaznikLewa = 1;
    int wskaznikPrawa = n;
    char kierunek = listaKierunkow[1];                  //pobieramy kierunek w ktorym bedziemy szli na poczatku
    int ileWkierunku = 0;
    for (int i = 1; i < listaKierunkow.size(); i++)
    {
        if (kierunek != listaKierunkow[i] || i == listaKierunkow.size() - 1)
        {
            if (kierunek == 'L')
                wskaznikLewa = OdwiedzaGwiazdyIZwracaWolnyIndex(kierunek, wskaznikLewa, ileWkierunku);      //ponownie podliczamy ile razy pojdziemy w jednym kierunku
            else                                                                                            //i odwiedzamy gwiazdy
                wskaznikPrawa = OdwiedzaGwiazdyIZwracaWolnyIndex(kierunek, wskaznikPrawa, ileWkierunku);

            kierunek = listaKierunkow[i];
            ileWkierunku = 1;
        }
        else
        {
            ileWkierunku++;
        }
    }
    cout << Koszt << endl;
    for (int i = 0; i < Trasa.size(); i++)                      //wyswietlamy wyjscie
        cout << Trasa[i] << " ";
    return 0;
}
