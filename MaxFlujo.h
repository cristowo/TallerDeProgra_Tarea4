#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

class MaxFlujo {
    public:
        // valiable que almacena el grafo
        vector<vector<int>> grafo;
        // valiable que almacena el maximo
        int max;
        // Constructor con parametros
        MaxFlujo(vector<vector<int>> grafo);
        // imprime el grafo
        void print(vector<vector<int>> a);
        // retorna true si el grafo tiene camino desde el nodo fuente al nodo sumidero
        bool DFS(int s, int t, int padre[], int max);
        // retorna el flujo maximo
        int fordFulkerson(int s, int t, int max);
        // funcion que transforma el archivo de texto en un grafo
        vector<vector<int>> load(string nombreArchivo);
};