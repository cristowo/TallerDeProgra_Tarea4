#include "ToThink.h"
// basicamente es el metodo de asignacion con un nombre pulento

/*
*  Clase ToThink (Asignacion)
*/

// Constructor
ToThink::ToThink(){
    this->grafoB;   //grafo bipartito
    this->grafoM;   //grafo de maximo flujo
    int max;
    int total_procesadores;
    int total_tareas;
}

/*
*  Lee el archivo de texto y lo carga en la matriz grafoB
*  parametros: nombre del archivo
*  retorno: true si el archivo fue encontrado, false si no
*/
bool ToThink::load(string filename){
	string line;
	// neceitamos la libreria de manejo de archivo fstream
	// sstream stream de string
	fstream txt_stream(filename);
	stringstream charStream;
	string number_txt;
	vector<int> *numero;
	
	if (!txt_stream.is_open()){
		cout<<"Archivo: " << filename << " no encontrado" << endl;
		return false;
	} else {
		cout<<"Archivo encontrado " << endl;
	}

    // obtenermos la cantidad de procesadores y tareas
	getline(txt_stream, line); 				            // lee caracteres hasta fin de linea
	charStream <<line;
	getline(charStream, number_txt, ' '); 	            // el string hasta que encuentre un espacio
	total_procesadores =stoi(number_txt); 			// transforma string a int
    getline(charStream, number_txt, ' '); 	            // el string hasta que encuentre un espacio
    total_tareas =stoi(number_txt); 			    // transforma string a int

    // Suma entre el total de procesadores, el total de tares, y los 2 nuevos nodos
    max = total_procesadores + total_tareas + 2;
    // generar una matriz de ceros
    for(int i=0;i< max; i++){
        numero=new vector<int>;
        for(int j=0;j< max; j++){
            numero->insert(numero->begin(),0);
        }
        this->grafoB.push_back(*numero);
    }
    // leer el archivo y llenar la matriz a con 1 si la tarea i puede ser ejecutada en el procesador j
    while(getline(txt_stream, line)){
        charStream.clear();
        charStream <<line;
        getline(charStream, number_txt, ' ');
        int procesador =stoi(number_txt);
        getline(charStream, number_txt, ' ');
        int tarea =stoi(number_txt);
        this->grafoB[procesador + 1][total_procesadores + tarea + 1]=1;
    }
    // cerrar el archivo
    txt_stream.close();
    return true;
}

/*
*  Transforma el grafo bipartito en un grafo de maximo flujo
*  parametros:
*  retorno:
*/
void ToThink::transformGrafo(){
    //--------- agregamos un nodo inicial y uno final-----------
    //------------------Junto a sus direcciones----------------
    for(int i=0;i< total_procesadores; i++){
        this-> grafoB[0][i+1]=1;
    }
    for(int i=0;i< total_tareas; i++){
        this-> grafoB[i+total_procesadores+1][max-1]=1;
    }
    this->grafoM = this->grafoB;
}

/*
* Resuelve el problema
* parametros: nombre del archivo
* retorno:
*/
void ToThink::solve(string filename){
    // cargar el archivo
    load(filename);
    // transformar el grafo
    transformGrafo();
    // inicializar el MaxFlujo
    MaxFlujo maxFlujo = MaxFlujo(grafoM);
    //obtener el maximo flujo
    int solve = maxFlujo.fordFulkerson(0, max-1, max);
    cout << "El maximo flujo es: " << solve << endl;
}

/*
* Imprime la matriz
* parametros: matriz a imprimir
* retorno:
*/
void ToThink::print(vector<vector<int>> a){
    //printea la matriz
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < a[i].size(); j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}