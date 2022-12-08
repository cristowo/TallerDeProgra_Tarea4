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
	vector<int> *number;
	
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
	int total_procesadores =stoi(number_txt); 			// transforma string a int
    getline(charStream, number_txt, ' '); 	            // el string hasta que encuentre un espacio
    int total_tareas =stoi(number_txt); 			    // transforma string a int

    vector<vector<int>> a;
    // determinar el maximo entre total de procesadores y total de tareas
    if(total_procesadores<total_tareas){
        max = total_tareas;
    }else{
        max = total_procesadores;
    }
    // generar una matriz de ceros
    for(int i=0;i< max; i++){
        number=new vector<int>;
        for(int j=0;j< max; j++){
            number->insert(number->begin(),0);
        }
        a.push_back(*number);
    }
    // leer el archivo y llenar la matriz a con 1 si la tarea i puede ser ejecutada en el procesador j
    while(getline(txt_stream, line)){
        charStream.clear();
        charStream <<line;
        getline(charStream, number_txt, ' ');
        int procesador =stoi(number_txt);
        getline(charStream, number_txt, ' ');
        int tarea =stoi(number_txt);
        a[procesador][tarea]=1;
    }
    // cerrar el archivo
    txt_stream.close();
    // asignar la matriz a a grafoB
    this->grafoB = a;

    return true;
}

/*
*  Transforma el grafo bipartito en un grafo de maximo flujo
*  parametros:
*  retorno:
*/
void ToThink::transformGrafo(){
    vector<vector<int>> grafoAux = this-> grafoB;
    //--------- agregamos un nodo inicial y uno final-----------
    // agregamos un 1 al final de cada fila
    for(int i=0;i< max; i++){
        grafoAux[i].push_back(1);
    }
    // agregamos una fila de 1 al inciio
    vector<int> fila;
    for(int i=0;i< max+1; i++){
        fila.push_back(1);
    }
    // chupapinga daigo
    grafoAux.insert(grafoAux.begin(),fila);
    grafoAux[0][max]=0;
    //----------------------------------------------------------
    // asignamos el grafo transformado a grafoM
    this->grafoM = grafoAux;
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
    // resolver el problema
    MaxFlujo maxFlujo = MaxFlujo(grafoM);
    int fluj = maxFlujo.fordFulkerson(0, max, max+1);
    // imprimir el resultado
    //print(grafoM);
    cout << "El maximo flujo es: " << fluj << endl;
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