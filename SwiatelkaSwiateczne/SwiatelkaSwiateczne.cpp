#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int iloscKolorow = 0;
int main()
{
    //********** wczytywanie wejscia
    int iloscLampek;
    int iloscOperacji;
    cin >> iloscLampek >> iloscOperacji;

    int TablicaLampekWLancuchu[iloscLampek];
    for(int i = 0; i < iloscLampek; i++)
    {
        TablicaLampekWLancuchu[i] = i;
    }

    for (int k = 0; k < iloscOperacji; k++)
    {
        int indexLewy;
        int indexPrawy;
        int dlugoscLancucha;
        cin >> indexLewy >> indexPrawy >> dlugoscLancucha;

        indexLewy--;
        indexPrawy--;
        int i = indexLewy;
        int j = indexPrawy;
        while (i < (indexLewy + dlugoscLancucha))
        {
            if (TablicaLampekWLancuchu[i] == 0 && TablicaLampekWLancuchu[j] == 0)
            {
                TablicaLampekWLancuchu[i] = i - indexLewy + 1;
                TablicaLampekWLancuchu[j] = TablicaLampekWLancuchu[i];
                // iloscKolorow++;
                continue;
            }
            if (TablicaLampekWLancuchu[i] == 0)
                TablicaLampekWLancuchu[i] = TablicaLampekWLancuchu[j];

            if (TablicaLampekWLancuchu[j] == 0)
                TablicaLampekWLancuchu[j] = TablicaLampekWLancuchu[i];

            if (TablicaLampekWLancuchu[i] != TablicaLampekWLancuchu[j])
            {
                for (int a = 0; a < iloscLampek; a++)
                {
                    if (TablicaLampekWLancuchu[a] == TablicaLampekWLancuchu[j])
                    {
                        TablicaLampekWLancuchu[a] = TablicaLampekWLancuchu[i];
                    }
                }
                //iloscKolorow--;
            }
            i++;
            j++;
        }
        //if (iloscKolorow == 1)
        //    break;
    }
    bool tab[iloscLampek/2] = {false};

    for (int i = 0; i < iloscLampek; i++)
    {
        if (!tab[TablicaLampekWLancuchu[i]])
        {
            tab[TablicaLampekWLancuchu[i]] = true;
            iloscKolorow++;
        }
    }
    cout << iloscKolorow << endl;
    return 0;
}