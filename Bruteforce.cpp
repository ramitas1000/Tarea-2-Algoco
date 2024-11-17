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



int min_cost(string &s1, string &s2, int m, int n){
    if (m == 0) {
        int cost = 0;
        for (int k = 0; k < n; ++k) {
            cost += costo_ins(s2[k]);
        }
        return cost;
    }

    if (n == 0) {
        int cost = 0;
        for (int k = 0; k < m; ++k) {
            cost += costo_del(s1[k]);
        }
        return cost;
    }

    int del, ins, sub, trans;

    del = min_cost(s1,s2,m-1,n) + costo_del(s1[m-1]);

    ins = min_cost(s1,s2,m,n-1) + costo_ins(s2[n-1]);

    if (s1[m-1] == s2[n-1]){
        sub = min_cost(s1,s2,m-1,n-1);
    }else{
        sub = min_cost(s1,s2,m-1,n-1) + costo_sub(s1[m-1],s2[n-1]);
    }
    
    trans = INT_MAX;
    if(m > 1 && m > 1 && s1[m-1] == s2[n-2] && s1[m - 2] == s2[n - 1]){
        trans = min_cost(s1,s2,m-2,n-2) + costo_trans(s1[m-1],s1[m-2]);
    }

    return min({del,ins,sub,trans});
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
    cout << min_cost(s1,s2,s1.size(),s2.size()) << endl;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Tiempo transcurrido para Dinamico: " << elapsed.count() << " segundos." << endl;
    
    
    return 0;
}



