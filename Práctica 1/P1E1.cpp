// Calculo de pi por muestreo directo

#include <iostream> // Libreria de archivos, deja trabajar con objetos input y output (como cout)
// cout (see-out) funciona con el operador insecion (<<) para imprimir texto
// cin (see-in)  funciona con el operador extraccion (>>) para pedirle input al usuario
#include <cmath>
#include <fstream>
using namespace std; // Me permite nombrar objetos y variables de la libreria estandar

int main() {
    // Defino mis variables
    int points; // Numero de puntos que genero
    int points_in_circle; // Numero de puntos que cayeron dentro del circulo
    float x; // Numero aleatorio para el eje x
    float y; // Numero aleatorio para el eje y
    float pi_aprox; // Defino mi valor aproximado de pi
    float suma;
    float var;
    float pi_suma;
    float pi_prom;
    const float pi = 3.14159265359;


    // Me abro dos archivo para guardar los datos
    ofstream myfile1 ("Var_vs_N_Ej1.txt");
    if (myfile1.is_open()) {
        myfile1 << "#N    Variance" << endl;
    }
    else cout << "Unable to open file";

    ofstream myfile2 ("Pi_vs_N_Ej1.txt");
    if (myfile2.is_open()) {
        myfile2 << "#N    Pi" << endl;
    }
    else cout << "Unable to open file";

    for (int N_exp = 1; N_exp <= 8; N_exp++) {
        suma = 0;
        pi_suma = 0;
        for (int est = 0; est <= 20; est++) {
            points = int(pow(static_cast<double>(10),static_cast<int>(N_exp)));
            //cout << N_exp << endl;
            //cout << points << endl; 
            points_in_circle = 0; // Inicio estos puntos en cero

            for (int i = 0; i <= points - 1; i++) {
                x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2)); // Me genero un numero aleatorio entre 0 y 2
                y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2)); // Mismo que antes
                x -= 1;
                y -= 1;
                //cout << x;
                //cout << y;
                if (x*x + y*y <= 1) {
                    points_in_circle += 1;
                }
            }
            // Calculo el cociente entre ambas

            pi_aprox = 4.0 * points_in_circle / points;
            //cout << pi_aprox << endl;
            suma += pow(pi_aprox - pi,2); 
            pi_suma += pi_aprox;  
        }
        var = suma / 21;
        pi_prom = pi_suma / 21;

        myfile1 << N_exp << "     " << var << endl; // Agrego los datos para una tabla
        myfile2 << N_exp << "     " << pi_prom << endl;

        // cout << points << "  " << var[N_exp] << endl;
    }
    myfile1.close();
    myfile2.close();
    return 0;
}
