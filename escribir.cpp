#include<bits/stdc++.h>
using namespace std;

vector<int> numeros;

vector<vector<int>> matriz;

void escribirNumerosEnArchivo(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo); // Abre el archivo en modo escritura
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    for (int num : numeros) { // Escribe cada número en el archivo
        archivo << num << " ";
    }

    archivo.close();
}


void escribirMatrizEnArchivo(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo); // Abre el archivo en modo escritura
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    for (const auto& fila : matriz) { // Itera sobre cada fila de la matriz
        for (int num : fila) { // Itera sobre cada elemento en la fila
            archivo << num << " ";
        }
        archivo << endl; // Nueva línea después de cada fila
    }

    archivo.close();
}


int main(){
    random_device rd; 
    mt19937 gen(rd()); // Generador Mersenne Twister
    uniform_int_distribution<> distrib(1, 5); // Distribución uniforme entre 1 y 5
    int r;

    for (int i = 0; i < 26; i++){
        r = distrib(gen);
        numeros.push_back(r);
    }
    
    vector<int> fila;
    for (int i = 0; i < 26; i++){
        fila.clear();
        for(int j = 0; j < 26; j++){
            if (i == j){
                fila.push_back(0);
            }else{
                r = distrib(gen);
                fila.push_back(r);
            }
        }
        matriz.push_back(fila);
    }

    //escribirNumerosEnArchivo("cost_delete.txt");
    //escribirNumerosEnArchivo("cost_insert.txt");
    //escribirMatrizEnArchivo("cost_replace.txt");
    //escribirMatrizEnArchivo("cost_transpose.txt");
    
    return 0;
}