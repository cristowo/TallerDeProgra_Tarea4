#include "MaxFlujo.h"

/*
* Clase Max Flujo, encargada de encontrar el flujo maximo
*/

// Constructor
MaxFlujo::MaxFlujo(){

}
// Constructor con parametros
MaxFlujo::MaxFlujo(vector<vector<int>> grafo){
    this-> grafo = grafo;
}

/*
* retorna true si el grafo tiene camino desde el nodo fuente al nodo sumidero
* parametros: grafo, nodo fuente, nodo sumidero, vector de padres, maximo
* retorno: true si existe un camino desde el nodo fuente al nodo sumidero
*/
bool MaxFlujo::DFS(int s, int t, int parent[], int max)
{
    // crea un arreglo de visitados
    bool visited[max];
    memset(visited, 0, sizeof(visited));
    
    // crea una cola
    queue<int> q;
    q.push(s);
    // marca el nodo fuente como visitado
    visited[s] = true;
    parent[s] = -1;

    // mientras la cola no este vacia
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < max ; v++) {
            if (visited[v] == false && grafo[u][v] > 0) {
                // Si encontramos un camino desde el nodo fuente al nodo sumidero
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
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
    int parent[max];
    int max_flow = 0;

    // Mientras exista un camino desde el nodo fuente al nodo sumidero
    while (DFS(s, t, parent, max)) {
        // Encuentra el flujo maximo a traves del camino
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, grafo[u][v]);
        }

        // Actualiza los residuos de los arcos y los arcos reversos
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            grafo[u][v] -= path_flow;
            grafo[v][u] += path_flow;
        }

        // Agrega el flujo maximo al flujo total
        max_flow += path_flow;
    }

    // Retorna el flujo total
    return max_flow;
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




