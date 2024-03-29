#include "MaxFlujo.h"

class ToThink {
    public:
        // Constructor
        ToThink();
        // Variable que almacena el grafo bipartito
        vector<vector<int>> grafoB;
        // Variable que almacena el grafo de max flujo
        vector<vector<int>> grafoM;
        // Variable que almacena el maximo (numero de nodos)
        int max;
        // Variables que almacenan el total de procesadores y tareas
        int total_procesadores;
        int total_tareas;
        // lee el archivo de texto
        bool load(string filename);
        // transforma el grafo bipartito en un grafo de max flujo
        void transformGrafo();
        // entrega el resultado
        void solve(string filename);
        // imprime el grafo
        void print(vector<vector<int>> a);
};