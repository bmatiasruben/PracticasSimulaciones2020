// Calculo de pi por metodo de Bouffon

#include <iostream> 
#include <cmath>
#include <fstream>
using namespace std; 

int main() {
    // Defino mis variables
    int needles; // Numero de agujas que genero
    int needle_hits; // Numero de agujas que tocan una linea
    float x_center; // Centro aleatorio de la aguja
    float dx; // Intervalo aleatorio en x
    float dy; // Intervalo aleatorio en y
    float x_tip; // Punta de la aguja
    float pi_aprox; // Defino mi valor aproximado de pi
    float b = 1;
    float a = 1;
    float b_2;
    float gamma;
    float pi_sum;
    float gamma_temp;
    int estimaciones = 20;
    float pi_final;

    // Me abro un archivo para guardar los datos
    ofstream myfile1 ("Pi_vs_N_Ej3.txt");
    if (myfile1.is_open()) {
        myfile1 << "# N    Pi" << endl;
    }
    else cout << "Unable to open file";

    b_2 = b/2;

    for (int N_exp = 1; N_exp <= 9; N_exp++) {
        pi_sum = 0;
        for (int est = 1; est <= estimaciones; est++) {
            needles = pow(10,N_exp);
            //cout << N_exp << endl;
            //cout << points << endl; 
            needle_hits = 0; // Inicio estos puntos en cero

            for (int i = 0; i <= needles - 1; i++) {
                x_center = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/b_2)); // Me genero un numero aleatorio entre 0 y b/2
                RETRY: dx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1)); // Me genero los intervalos aleatorios en x e y
                dy = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1)); // Mismo que antes
                gamma_temp = dx*dx + dy*dy;
                gamma = sqrt(gamma_temp);
                if (1 < gamma){
                    goto RETRY;
                }
                x_tip = x_center - a * dx / (2 * gamma);
                if (x_tip < 0) {
                    needle_hits += 1;
                }
            }
            // Calculo el cociente entre ambas

            pi_aprox = 2.0 * needles / needle_hits;
            pi_sum += pi_aprox;
            // cout << pi_aprox << endl;
        }
        pi_final = pi_sum / (estimaciones*1.);
        myfile1 << " " << N_exp << "     " << pi_final << endl; // Agrego los datos para una tabla
        // cout << points << "  " << var[N_exp] << endl;
    }
    myfile1.close();

    return 0;
}