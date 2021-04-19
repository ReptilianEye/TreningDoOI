#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

const int iloscStosow = 4;
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

void UstawiaStosy(vector<int> *stosSkad, vector<int> *stosDokad, vector<int> *stosPom,vector<int> *stosPom2, int ileElementowDoUstawienia)
{
    if (ileElementowDoUstawienia == 1)
    {
        (*stosDokad).push_back(*(*stosSkad).rbegin());
        (*stosSkad).pop_back();
        licznikRuchow++;
        //WyswietlaStosy(*stosSkad, *stosDokad, *stosPom);
        return;
    }
    else
    {
        UstawiaStosy(stosSkad, stosPom, stosDokad,stosPom2, ileElementowDoUstawienia - 2);
        UstawiaStosy(stosSkad,stosPom2,stosPom,stosDokad,1);
        UstawiaStosy(stosSkad, stosDokad, stosPom,stosPom2, 1);
        UstawiaStosy(stosPom,stosDokad,stosSkad,stosPom2,1);
        UstawiaStosy(stosPom2, stosDokad, stosSkad,stosPom, ileElementowDoUstawienia - 2);
    }
}

int main()
{
    //********** wczytywanie wejscia
    int iloscLiczbNaStosie = 3;
    vector<int> stosA;
    vector<int> stosB;
    vector<int> stosC;
    vector<int> stosD;

    for (int i = iloscLiczbNaStosie; i > 0; i--)
    {
        stosA.push_back(i);
    }
    UstawiaStosy(&stosA, &stosC, &stosB,&stosD, iloscLiczbNaStosie);
    cout << licznikRuchow << endl;
    return 0;
}