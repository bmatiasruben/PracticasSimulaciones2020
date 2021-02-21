// Markov en red cuadrada

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main() {
    // Defino mis variables
    int pasos = pow(10,6);
    const int estimaciones = 20;
    float Hits[estimaciones][4][4] = {0};
    int n;
    float Hits_avg[4][4] = {0};
    float P[4][4] = {0};

    // Me abro dos archivo para guardar los datos
    ofstream myfile1 ("Hits_vs_Celda_Ej4b.txt");
    if (myfile1.is_open()) {
        myfile1 << "#    0       1       2       3" << endl;
    }
    else cout << "Unable to open file";

    ofstream myfile2 ("Prob_vs_Celda_Ej4b.txt");
    if (myfile2.is_open()) {
        myfile2 << "#     0         1         2         3" << endl;
    }
    else cout << "Unable to open file";

    for (int est = 0; est < estimaciones; est++){
        int i = 0;
        int j = 0;
        Hits[est][i][j] = 1;
        for (int k = 0; k < pasos; k++){
            n = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/4));
            
            if (n == 0 && i-1 >= 0) {
                i -= 1;
                Hits[est][i][j] += 1;
            } else if (n == 1 && j+1 <= 3){
                j += 1;
                Hits[est][i][j] += 1;
            } else if (n == 2 && i+1 <= 3){
                i += 1;
                Hits[est][i][j] += 1;
            } else if (n == 3 && j-1 >= 0){
                j -= 1;
                Hits[est][i][j] += 1;
            } else{
                Hits[est][i][j] += 1;
            }
            // cout << n << " " << i << " " << j << " "<< Hits[est][i][j] << endl;
        }
    }

    for (int mr = 0; mr < 4; mr++){
        for (int mk = 0; mk < 4; mk++){
            for (int kr = 0; kr < estimaciones; kr++){
                Hits_avg[mk][mr] += Hits[kr][mk][mr];
                // cout << mk << " " << mr << " " << Hits[kr][mk][mr] << endl;
            }
            Hits_avg[mk][mr] = Hits_avg[mk][mr] / estimaciones;
            P[mk][mr] = Hits_avg[mk][mr] * 1. / pasos;
        }
    }

    for (int mj = 0; mj < 4; mj++){
        myfile1 << mj << " " << Hits_avg[mj][0] << " " << Hits_avg[mj][1] << " " << Hits_avg[mj][2] << " " << Hits_avg[mj][3] <<endl;
        myfile2 << mj << " " << P[mj][0] << " " << P[mj][1] << " " << P[mj][2] << " " << P[mj][3] <<endl;
    }

    myfile1.close();
    return 0;
}