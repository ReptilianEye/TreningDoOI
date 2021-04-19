#include <iostream>
#include <time.h>
#include <bitset>
#include <math.h>
#include <fcntl.h>
#include <vector>

using namespace std;

// C++ Implementation for random
// tree generator using Prufer Sequence

// Prints edges of tree
// represented by give Prufer code
void printTreeEdges(int prufer[], int m)
{
    int vertices = m + 2;
    int vertex_set[vertices];

    // Initialize the array of vertices
    for (int i = 0; i < vertices; i++)
        vertex_set[i] = 0;

    // Number of occurrences of vertex in code
    for (int i = 0; i < vertices - 2; i++)
        vertex_set[prufer[i] - 1] += 1;

    int j = 0;

    // Find the smallest label not present in
    // prufer[].
    for (int i = 0; i < vertices - 2; i++)
    {
        for (j = 0; j < vertices; j++)
        {

            // If j+1 is not present in prufer set
            if (vertex_set[j] == 0)
            {

                // Remove from Prufer set and print
                // pair.
                vertex_set[j] = -1;
                cout << (j + 1) << " " << prufer[i] << " " << endl;
                vertex_set[prufer[i] - 1]--;

                break;
            }
        }
    }

    j = 0;

    // For the last element
    for (int i = 0; i < vertices; i++)
    {
        if (vertex_set[i] == 0 && j == 0)
        {

            cout << (i + 1) << " ";
            j++;
        }
        else if (vertex_set[i] == 0 && j == 1)
            cout << (i + 1);
    }
}

// generate random numbers in between l an r
int ran(int l, int r)
{
    return l + (rand() % (r - l + 1));
}

// Function to Generate Random Tree
void generateRandomTree(int n)
{

    int length = n - 2;
    int arr[length];

    // Loop to Generate Random Array
    for (int i = 0; i < length; i++)
    {
        arr[i] = ran(0, length + 1) + 1;
    }
    printTreeEdges(arr, length);
}

void GenerujeGwiazde(int n)
{
    for (int i = 2; i <= n; i++)
    {
        cout << 1 << " " << i << endl;
    }
}
// Driver Code
int main()
{

    _setmode(_fileno(stdout), _O_TEXT);
    srand((unsigned)time(NULL));
    int maxN = 10; //pow(10,6);
    long long n = maxN;
    cout << n << endl;
    long long sumaWartosci = 0;
    for (int i = 0; i < n; i++)
    {
        int wartosc = rand() % 50;
        sumaWartosci += wartosc;
        cout << wartosc << " ";
    }
    cout << endl;
    long long sumaWartosciPotem = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int wartosc = rand() % 50;
        sumaWartosciPotem += wartosc;
        cout << wartosc << " ";
    }
    long long roznica = sumaWartosci - sumaWartosciPotem;
    cout << roznica << endl;
    //generateRandomTree(n);
    GenerujeGwiazde(n);
    return 0;
}