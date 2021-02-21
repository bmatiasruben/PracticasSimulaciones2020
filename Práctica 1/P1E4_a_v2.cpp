// Markov en red cuadrada

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main() {
    // Defino mis variables
    float P[16][4] = {{1,2,5,1},
                      {2,3,6,1},
                      {3,4,7,2},
                      {4,4,8,3},
                      {1,6,9,5},
                      {2,7,10,5},
                      {3,8,11,6},
                      {4,8,12,7},
                      {5,10,13,9},
                      {6,11,14,9},
                      {7,12,15,10},
                      {8,12,16,11},
                      {9,14,13,13},
                      {10,15,14,13},
                      {11,16,15,14},
                      {12,16,16,15}};
    int pasos;
    int n;
    pasos = pow(10,3);
    int Hits[16] = {0};

    // Me abro dos archivo para guardar los datos
    ofstream myfile1 ("Hits_vs_Celda_Ej4.txt");
    if (myfile1.is_open()) {
        myfile1 << "# Celda    Pasos" << endl;
    }
    else cout << "Unable to open file";

    ofstream myfile2 ("Prob_vs_Celda_Ej4.txt");
    if (myfile2.is_open()) {
        myfile2 << "# Celda    Probabilidad" << endl;
    }
    else cout << "Unable to open file";

    int k = 16;
    Hits[15] = 1;

    for (int i = 0; i < pasos; i++){
        n = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/4));
        k -= 1;
        k = P[k][n];
        // cout << n << "  " << k;
        Hits[k-1] += 1;
    }

    for (int i = 0; i < 16; i++){
        myfile1 << i+1 << "          " << Hits[i] << endl;
        myfile2 << i+1 << "          " << Hits[i]*1.0/pasos << endl;
    //     for (int m = 0; m < 4; m++){
    //         cout << P[i][m] << " ";
    //     }
    //     cout << endl;
    }
        

    myfile1.close();
    return 0;
}