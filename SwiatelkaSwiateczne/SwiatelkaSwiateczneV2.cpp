#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    //********** wczytywanie wejscia
    int iloscLampek;
    int iloscOperacji;
    cin >> iloscLampek >> iloscOperacji;

    set<int> TablicaLampekWLancuchu[iloscLampek];
    int iloscKolorow = iloscLampek;
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
            if (TablicaLampekWLancuchu[i].empty() && TablicaLampekWLancuchu[j].empty())
            {
                set<int> nowyZbior = {i, j};
                TablicaLampekWLancuchu[i] = nowyZbior;
                TablicaLampekWLancuchu[j] = nowyZbior;
                iloscKolorow--;
            }

            if (TablicaLampekWLancuchu[i].empty())
            {
                TablicaLampekWLancuchu[j].insert(i);
                TablicaLampekWLancuchu[i] = TablicaLampekWLancuchu[j];
                iloscKolorow--;
            }

            if (TablicaLampekWLancuchu[j].empty())
            {
                TablicaLampekWLancuchu[i].insert(j);
                TablicaLampekWLancuchu[j] = TablicaLampekWLancuchu[i];
                iloscKolorow--;
            }

            if (TablicaLampekWLancuchu[i] != TablicaLampekWLancuchu[j])
            {
                for (auto i : TablicaLampekWLancuchu[i])
                {
                    TablicaLampekWLancuchu[j].insert(i);
                    //merge(TablicaLampekWLancuchu[i].begin(), TablicaLampekWLancuchu[i].end(),
                    //      TablicaLampekWLancuchu[j].begin(), TablicaLampekWLancuchu[i].end(),
                    //      inserter(nowyZbior, nowyZbior.begin()));
                }
                TablicaLampekWLancuchu[i] = TablicaLampekWLancuchu[j];
                iloscKolorow--;
            }
            i++;
            j++;
        }
    }
    cout << iloscKolorow << endl;
    return 0;
}