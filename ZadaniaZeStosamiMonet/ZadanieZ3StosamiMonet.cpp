#include <iostream>
#include <string>
#include <cstdlib>
#include <stack>

using namespace std;

const int iloscStosow = 3;

class elementStosu
{
public:
    int wartosc = 0;
    int skadPrzyszla;
};

class Stos
{
public:
    stack<elementStosu> Stos;
    int iloscDodanych = 0;
};

void UstawiaStosy(Stos TablicaStosow[], int ktoryStosDoUstawienia)
{
    for (int i = 0; i < iloscWStosie; i++)
    {
        int iloscWStosie = TablicaStosow[ktoryStosDoUstawienia].Stos.size();

        elementStosu el;
        el.wartosc = TablicaStosow[ktoryStosDoUstawienia].Stos.top().wartosc;
        TablicaStosow[ktoryStosDoUstawienia].Stos.pop();
        el.skadPrzyszla = ktoryStosDoUstawienia;
        if (iloscWStosie % 2 == 1)
        {
            if (el.wartosc < TablicaStosow[iloscStosow - ktoryStosDoUstawienia].Stos.top())
                TablicaStosow[iloscStosow - ktoryStosDoUstawienia].Stos.push(el);
            else
            {
                elementStosu elDoPrzeniesienia = TablicaStosow[iloscStosow - ktoryStosDoUstawienia].Stos.top().wartosc;
                int skadPrzyszedla = TablicaStosow[iloscStosow - ktoryStosDoUstawienia].Stos.top().skadPrzyszla;
                TablicaStosow(iloscStosow - ktoryStosDoUstawienia).Stos.pop() for (int j = 0; j < iloscWStosie; j++)
                {
                    if (j != iloscStosow - ktoryStosDoUstawienia && skadPrzyszedla)
                    {
                        elDoPrzeniesienia.skadPrzyszla = ktoryStosDoUstawienia;
                        TablicaStosow[j].push(elDoPrzeniesienia);
                        TablicaStosow[iloscStosow - ktoryStosDoUstawienia].Stos.push(el);
                    }
                }
            }
        }
        else
        {
            TablicaStosow[0].Stos.push(el)
        }
    }
}

int main()
{
    //********** wczytywanie wejscia

    Stos TablicaStosow[iloscStosow];
    for (int i = 5; i > 0; i--) //robocze wczytanie wejscia
    {
        elementStosu wart;
        wart.wartosc = i;
        TablicaStosow[0].Stos.push(wart);
    }
    while (TablicaStosow[0].Stos.empty() == false)
    {
        int kolejny = TablicaStosow[0].Stos.top().wartosc;
        TablicaStosow[0].Stos.pop();
        for (int i = 0; i < 3; i++)
        {
            if (TablicaStosow[i].Stos.empty())
            {
                elementStosu nowyElement;
                nowyElement.wartosc = kolejny;
                TablicaStosow[i].Stos.push(nowyElement);
                TablicaStosow[i].iloscDodanych++;
            }
        }
    }

    cout << iloscKolorow << endl;
    return 0;
}