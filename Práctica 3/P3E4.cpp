#include <gsl/gsl_rng.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>

using namespace std;

int main() {
// Uso el generador gfsr4 [https://webhome.phy.duke.edu/~rgb/General/dieharder.php]
    const int estimaciones = 500;
    const int longitud = pow(10,3);
    gsl_rng* numberGen = gsl_rng_alloc(gsl_rng_gfsr4);
    
    ofstream myFile1("P3E4a.txt");
    if (myFile1.is_open()) {
        myFile1 << "# List" << endl;
    }
    else cout << "Unable to open file";

    for (int i = 0; i < longitud; i++) {
        for (int j = 0; j < estimaciones; j++) {
            double generatedNumber = gsl_rng_uniform(numberGen);
            myFile1 << generatedNumber << " ";
        }  
        myFile1 << endl;    
    }

    myFile1.close();
    return 0;
}
