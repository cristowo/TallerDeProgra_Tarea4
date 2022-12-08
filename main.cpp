#include "ToThink.h"
#include <ctime>

int main(){
    ToThink toThink;
    srand(time(NULL));
    clock_t ti, tf;
    //solicitar el nombre del archivo por consola
    cout << "Ingrese el nombre del archivo: " << endl;
    cout << "Ejemplo: CompletoItaliano.txt" << endl;
    string nombreArchivo;
    cin >> nombreArchivo;   
    //------------------------------------------
    ti = clock();
    toThink.solve(nombreArchivo);
    //toThink.solve("prueba.txt");
    tf = clock();
    double tiempo = (tf - ti) / (double)CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecucion: " << tiempo << " segundos." <<std::endl;
    return 0;
}