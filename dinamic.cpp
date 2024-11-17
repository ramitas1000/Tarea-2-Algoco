#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <chrono>
using namespace std;

vector<int> del;
vector<int> ins;
vector<vector<int>> sub;
vector<vector<int>> trans;

void leer_del(){
    ifstream f("cost_delete.txt");
    if (!f.is_open()) {
        cerr << "error" << endl;
        return;
    }

    string linea;
    if (getline(f,linea)){
        istringstream stream(linea);
        int num;
        while (stream >> num){
            del.push_back(num);
        }
    }
    f.close();

}

void leer_ins(){
    ifstream f("cost_insert.txt");
    if (!f.is_open()) {
        cerr << "error" << endl;
        return;
    }

    string linea;
    if (getline(f,linea)){
        istringstream stream(linea);
        int num;
        while (stream >> num){
            ins.push_back(num);
        }
    }
    f.close();
}

void leer_sub(){
    ifstream f("cost_replace.txt");
    if (!f.is_open()) {
        cerr << "error" << endl;
        return;
    }

    string linea;
    while (getline(f, linea)) { // Lee cada línea del archivo
        istringstream stream(linea);
        vector<int> fila;
        int numero;
        while (stream >> numero) { // Lee cada número en la línea
            fila.push_back(numero);
        }
        sub.push_back(fila); // Agrega la fila a la matriz
    }

    f.close();

}

void leer_trans(){
        ifstream f("cost_transpose.txt");
    if (!f.is_open()) {
        cerr << "error" << endl;
        return;
    }

    string linea;
    while (getline(f, linea)) { // Lee cada línea del archivo
        istringstream stream(linea);
        vector<int> fila;
        int numero;
        while (stream >> numero) { // Lee cada número en la línea
            fila.push_back(numero);
        }
        trans.push_back(fila); // Agrega la fila a la matriz
    }

    f.close();
}

int costo_sub(char a, char b){
    int cost = sub[a-97][b-97];
    return cost;
}

int costo_ins(char b){
    int cost = ins[b-97];
    return cost;
}

int costo_del(char a){
    int cost = del[a-97];
    return cost;
}

int costo_trans(char a, char b){
    int cost = trans[a-97][b-97];
    return cost;
}



int min_cost(string &s1, string &s2){
    int m = s1.size();
    int n = s2.size();
    int del, ins, sub, trans;

    //matriz de costos
    vector<vector<int>> cost(m + 1, vector<int>(n + 1, 0));

    //rellenar con los costos base
    for (int i = 1; i <= m; ++i) {
        cost[i][0] = cost[i - 1][0] + costo_del(s1[i - 1]);
    }

    for (int j = 1; j <= n; ++j) {
        cost[0][j] = cost[0][j - 1] + costo_ins(s2[j - 1]);
    }


    //for principal
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            del = cost[i-1][j] + costo_del(s1[i - 1]);
            ins = cost[i][j-1] + costo_ins(s2[j-1]);

            if (s1[i-1] == s2[j-1]){
                sub = cost[i-1][j-1];
            }else{
                sub = cost[i-1][j-1] + costo_sub(s1[i-1],s2[j-1]);
            }

            trans = INT_MAX;
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                trans = cost[i - 2][j - 2] + costo_trans(s1[i - 1], s1[i - 2]);
            }

            cost[i][j] = min({del,ins,sub,trans});
        }
    }
    return cost[m][n];
}

int main() {
    string s1,s2;
    getline(cin,s1);
    getline(cin,s2);

    leer_del();
    leer_ins();
    leer_sub();
    leer_trans();

    auto start = chrono::high_resolution_clock::now();
    cout << min_cost(s1,s2) << endl;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Tiempo transcurrido para Dinamico: " << elapsed.count() << " segundos." << endl;
    
    return 0;
}


