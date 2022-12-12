#include "MaxFlujo.h"

/*
* Clase Max Flujo, encargada de encontrar el flujo maximo
*/

// Constructor con parametros
MaxFlujo::MaxFlujo(vector<vector<int>> grafo){
    this-> grafo = grafo;
}

/*
* retorna true si el grafo tiene camino desde el nodo fuente al nodo sumidero
* parametros: grafo, nodo fuente, nodo sumidero, vector de padres, maximo
* retorno: true si existe un camino desde el nodo fuente al nodo sumidero
*/
bool MaxFlujo::DFS(int s, int t, int padre[], int max)
{
    // crea un arreglo de visitados
    bool visitados[max];
    memset(visitados, 0, sizeof(visitados));
    
    // crea una cola
    queue<int> cola;
    cola.push(s);
    // marca el nodo fuente como visitado
    visitados[s] = true;
    padre[s] = -1;

    // mientras la cola no este vacia
    while (!cola.empty()) {
        int u = cola.front();
        cola.pop();
        for (int v = 0; v < max ; v++) {
            if (visitados[v] == false && grafo[u][v] > 0) {
                // Si encontramos un camino desde el nodo fuente al nodo sumidero
                if (v == t) {
                    padre[v] = u;
                    return true;
                }
                cola.push(v);
                padre[v] = u;
                visitados[v] = true;
            }
        }
    }

    // Si no existe un camino desde el nodo fuente al nodo sumidero
    return false;
}

/*
* retorna el flujo maximo
* parametros: grafo, nodo fuente, nodo sumidero, maximo
* retorno: flujo maximo
*/
int MaxFlujo::fordFulkerson(int s, int t, int max)
{
    int u, v;
    // Crea una matriz de residuos
    int padre[max];
    int FlujoMaximo = 0;

    // Mientras exista un camino desde el nodo fuente al nodo sumidero
    while (DFS(s, t, padre, max)) {
        // Encuentra el flujo maximo a traves del camino
        int CaminoFlujo = INT_MAX;
        for (v = t; v != s; v = padre[v]) {
            u = padre[v];
            CaminoFlujo = min(CaminoFlujo, grafo[u][v]);
        }

        // Actualiza los residuos de los arcos y los arcos reversos
        for (v = t; v != s; v = padre[v]) {
            u = padre[v];
            grafo[u][v] -= CaminoFlujo;
            grafo[v][u] += CaminoFlujo;
        }

        // Agrega el flujo maximo al flujo total
        FlujoMaximo += CaminoFlujo;
    }

    // Retorna el flujo total
    return FlujoMaximo;
}

/*
* transforma el grafo en un grafo de flujo
* parametros: grafo, maximo
* retorno: grafo de flujo
*/
vector<vector<int>> MaxFlujo::load(string nombreArchivo){
    string line;
	// neceitamos la libreria de manejo de archivo fstream
	// sstream stream de string
	fstream txt_stream(nombreArchivo);
	stringstream charStream;
	string number_txt;
	vector<int> *number;
	
	if (!txt_stream.is_open()){
		cout<<"Archivo: " << nombreArchivo << " no encontrado" << endl;
	} else {
		cout<<"Archivo encontrado " << endl;
	}

    // obtenermos la cantidad de procesadores y tareas
	getline(txt_stream, line); 				            // lee caracteres hasta fin de linea
	charStream <<line;
	getline(charStream, number_txt, ' '); 	            // el string hasta que encuentre un espacio
	int total =stoi(number_txt); 			            // transforma string a int
    
    // creamos el matriz de flujo con solo 0
    vector<vector<int>> g;
    for(int i=0;i< total; i++){
        number=new vector<int>;
        for(int j=0;j< total; j++){
            number->insert(number->begin(),0);
        }
        g.push_back(*number);
    }
    //agrergamos los valores a la matriz
    while(getline(txt_stream, line)){
        charStream.clear();
        charStream <<line;
        getline(charStream, number_txt, ' '); 	        // el string hasta que encuentre un espacio
        int procesador =stoi(number_txt); 			    // transforma string a int
        getline(charStream, number_txt, ' '); 	        // el string hasta que encuentre un espacio
        int tarea =stoi(number_txt); 			        // transforma string a int
        getline(charStream, number_txt, ' '); 	        // el string hasta que encuentre un espacio
        int valor =stoi(number_txt); 			        // transforma string a int
        g[procesador][tarea] = valor;
    }
    return g;
}




