#include <iostream>
#include <vector>

using namespace std;

int encontrarMaximo(const vector<int> &v)
{
    int max = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] > max)
        {
            max = v[i];
        }
    }
    return max;
}

int main()
{
    vector<int> lista = {5, 12, 9, 7, 3, 15, 8, 10, 6, 4};

    int max = encontrarMaximo(lista);

    cout << "El máximo elemento de la lista es: " << max << endl;
    return 0;
}