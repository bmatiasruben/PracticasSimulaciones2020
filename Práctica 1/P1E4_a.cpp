// Markov en red cuadrada

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main() {
    // Defino mis variables
    float P[16][16] = {{0.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                      {0.25,0.25,0.25,0,0,0.25,0,0,0,0,0,0,0,0,0,0},
                      {0,0.25,0.25,0.25,0,0,0.25,0,0,0,0,0,0,0,0,0},
                      {0,0,0.25,0.5,0,0,0,0.25,0,0,0,0,0,0,0,0},
                      {0.25,0,0,0,0.25,0.25,0,0,0.25,0,0,0,0,0,0,0},
                      {0,0.25,0,0,0.25,0,0.25,0,0,0.25,0,0,0,0,0,0},
                      {0,0,0.25,0,0,0.25,0,0.25,0,0,0.25,0,0,0,0,0},
                      {0,0,0,0.25,0,0,0.25,0.25,0,0,0,0.25,0,0,0,0},
                      {0,0,0,0,0.25,0,0,0,0.25,0.25,0,0,0.25,0,0,0},
                      {0,0,0,0,0,0.25,0,0,0.25,0,0.25,0,0,0.25,0,0},
                      {0,0,0,0,0,0,0.25,0,0,0.25,0,0.25,0,0,0.25,0},
                      {0,0,0,0,0,0,0,0.25,0,0,0.25,0.25,0,0,0,0.25},
                      {0,0,0,0,0,0,0,0,0.25,0,0,0,0.5,0.25,0,0},
                      {0,0,0,0,0,0,0,0,0,0.25,0,0,0.25,0.25,0.25,0},
                      {0,0,0,0,0,0,0,0,0,0,0.25,0,0,0.25,0.25,0.25},
                      {0,0,0,0,0,0,0,0,0,0,0,0.25,0,0,0.25,0.5}};
    const int pasos = 2;
    
    float P_iteraciones[pasos][16] = {0};

    // Me abro dos archivo para guardar los datos
    ofstream myfile1 ("Prob_vs_Celda_Ej4.txt");
    if (myfile1.is_open()) {
        myfile1 << "# Celda    Probabilidad" << endl;
    }
    else cout << "Unable to open file";

    P_iteraciones[0][15] = 1;

    for (int i = 1; i < pasos; i++){
        for (int a = 0; a < 16; a++){
            for (int b = 0; b < 16; b++){
                P_iteraciones[i][a] += P[a][b] * P_iteraciones[i-1][b];
            }
        }
    }

    for (int k = 0; k < 16; k++){
        cout << P_iteraciones[pasos-1][k] << " ";
    }
    
    myfile1.close();
    return 0;
}