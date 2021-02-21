// Calculo de pi por cadena de Markov

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std; // Me permite nombrar objetos y variables de la libreria estandar

int main() {
    // Defino mis variables
    int points; // Numero de puntos que genero
    int points_in_circle; // Numero de puntos que cayeron dentro del circulo
    int points_accepted; // Para el grado de aceptacion
    float x; // Numero aleatorio para el eje x
    float y; // Numero aleatorio para el eje y
    float dx; // Paso de la cadena en x
    float dy; // Paso de la cadena en y
    float pi_aprox; // Defino mi valor aproximado de pi
    float var;
    float delta = 0.3;
    float delta_2;
    const float pi = 3.14159265359;
    float aceptacion;

    // Me abro dos archivo para guardar los datos
    // ofstream myfile1 ("Var_vs_N_Ej2.txt");
    // if (myfile1.is_open()) {
    //     myfile1 << "#N    Variance" << endl;
    // }
    // else cout << "Unable to open file";

    ofstream myfile2 ("Pi_vs_N_Ej2.txt");
    if (myfile2.is_open()) {
        myfile2 << "#N    Pi" << endl;
    }
    else cout << "Unable to open file";

    for (int N_exp = 1; N_exp <= 8; N_exp++) {
        delta_2 = 2*delta;
        points = pow(10,N_exp);
        points_in_circle = 0; // Inicio estos puntos en cero
        points_accepted = 0;
        x = 1;
        y = 1;

        for (int i = 0; i <= points; i++) {
            dx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/delta_2)); // Me genero un numero aleatorio entre 0 y 2
            dy = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/delta_2)); // Mismo que antes
            dx -= delta;
            dy -= delta;
            // cout << dx << "  " << dy << endl;
            if (abs(x+dx) < 1. && abs(y+dy) < 1.) {
                x += dx;
                y += dy;
                points_accepted += 1;
            }
            if (x*x + y*y <= 1) {
                points_in_circle += 1;
            }
        }
        // Calculo el cociente entre ambas
        cout << points_in_circle << endl;
        pi_aprox = 4.0 * points_in_circle / points;
        //cout << pi_aprox << endl;     
        var = pow(pi_aprox - pi,2);

        // myfile1 << N_exp << "     " << var << endl; // Agrego los datos para una tabla
        myfile2 << N_exp << "     " << pi_aprox << endl;

    }
    // myfile1.close();
    myfile2.close();



    // Me abro dos archivo para guardar los datos
    ofstream myfile3 ("Var_vs_delta_Ej2.txt");
    if (myfile3.is_open()) {
        myfile3 << "#delta    Varianza" << endl;
    }
    else cout << "Unable to open file";

    ofstream myfile4 ("Accept_vs_delta_Ej2.txt");
    if (myfile4.is_open()) {
        myfile4 << "#delta    Acceptacion" << endl;
    }
    else cout << "Unable to open file";

    delta = 0;

    while (delta <= 3) {
        delta_2 = 2*delta;
        points_in_circle = 0; // Inicio estos puntos en cero
        points_accepted = 0;
        x = 1;
        y = 1;

        for (int i = 0; i <= 1000000; i++) {
            dx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/delta_2)); // Me genero un numero aleatorio entre 0 y 2
            dy = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/delta_2)); // Mismo que antes
            dx -= delta;
            dy -= delta;
            // cout << dx << "  " << dy << endl;
            if (abs(x+dx) < 1. && abs(y+dy) < 1.) {
                x += dx;
                y += dy;
                points_accepted += 1;
            }
            if (x*x + y*y <= 1) {
                points_in_circle += 1;
            }
        }
        // Calculo el cociente entre ambas
        pi_aprox = 4.0 * points_in_circle / 1000000.;
        aceptacion = points_accepted / 1000000.;
        //cout << pi_aprox << endl;     
        var = pow(pi_aprox - pi,2);

        myfile3 << delta << "     " << var << endl; // Agrego los datos para una tabla
        myfile4 << delta << "     " << aceptacion << endl;

        delta += 0.01;

    }
    myfile3.close();
    myfile4.close();

    return 0;
}