#include <gsl/gsl_rng.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>

using namespace std;

int main() {
// Uso el generador gfsr4 [https://webhome.phy.duke.edu/~rgb/General/dieharder.php]
    gsl_rng* numberGen = gsl_rng_alloc(gsl_rng_gfsr4);

    ofstream myFile1("P3E2_1k.txt");
    if (myFile1.is_open()) {
        myFile1 << "# List" << endl;
    }
    else cout << "Unable to open file";

    ofstream myFile2("P3E2_10k.txt");
    if (myFile2.is_open()) {
        myFile2 << "# List" << endl;
    }
    else cout << "Unable to open file";

    ofstream myFile3("P3E2_100k.txt");
    if (myFile3.is_open()) {
        myFile3 << "# List" << endl;
    }
    else cout << "Unable to open file";

    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < int(pow(static_cast<double>(10), static_cast<int>(i))); j++) {
            double generatedNumber = gsl_rng_uniform(numberGen);
            if (i == 3) {
                myFile1 << generatedNumber << endl;
            }
            else if (i == 4) {
                myFile2 << generatedNumber << endl;
            }
            else {
                myFile3 << generatedNumber << endl;
            }
        }
    }
}
