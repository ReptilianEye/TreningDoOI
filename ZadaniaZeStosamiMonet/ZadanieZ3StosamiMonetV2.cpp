#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

const int iloscStosow = 3;
int licznikRuchow = 0;

void WyswietlaStosy(vector<int> stosA, vector<int> stosB, vector<int> stosC)
{
    cout << "Stos 1"
         << "\t"
         << "Stos 2"
         << "\t "
         << "Stos 3" << endl;
    while (!stosA.empty() || !stosB.empty() || !stosC.empty())
    {
        if (!stosA.empty())
        {
            cout << *(stosA.rbegin());
            (stosA).pop_back();
        }

        cout << "\t";

        if(!stosB.empty())
        {
            cout << *(stosB.rbegin());
            stosB.pop_back();
        }             
        cout << "\t";

        if (!stosC.empty())
        {
            cout << *(stosC.rbegin());
            stosC.pop_back();
        }
        cout << endl;
    }
}

void UstawiaStosy(vector<int> *stosSkad, vector<int> *stosDokad, vector<int> *stosPom, int ileElementowDoUstawienia)
{
    if (ileElementowDoUstawienia == 1)
    {
        (*stosDokad).push_back(*(*stosSkad).rbegin());
        (*stosSkad).pop_back();
        licznikRuchow++;
        WyswietlaStosy(*stosSkad, *stosDokad, *stosPom);
        return;
    }
    else
    {
        UstawiaStosy(stosSkad, stosPom, stosDokad, ileElementowDoUstawienia - 1);
        UstawiaStosy(stosSkad, stosDokad, stosPom, 1);
        UstawiaStosy(stosPom, stosDokad, stosSkad, ileElementowDoUstawienia - 1);
    }
}

int main()
{
    //********** wczytywanie wejscia
    int iloscLiczbNaStosie = 3;
    vector<int> stosA;
    vector<int> stosB;
    vector<int> stosC;

    for (int i = iloscLiczbNaStosie; i > 0; i--)
    {
        stosA.push_back(i);
    }
    UstawiaStosy(&stosA, &stosC, &stosB, iloscLiczbNaStosie);
    cout << licznikRuchow << endl;
    return 0;
}