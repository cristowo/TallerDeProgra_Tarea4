#include "MaxFlujo.h"

int main(){
    // notar flujo en minicula
    vector<vector<int>> graph;
    MaxFlujo maxflujo = MaxFlujo(graph);
    graph = maxflujo.load("test_MaxFlujo.txt");
    // notar Flujo en mayuscula
    MaxFlujo maxFlujo = MaxFlujo(graph);
    cout << "El flujo maximo es " << maxFlujo.fordFulkerson(0, 5, 6) << endl;

    return 0;
}
