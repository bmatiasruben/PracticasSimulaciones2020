#include <gsl/gsl_rng.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>

using namespace std;
#define E 1.0

void mcStep(double temperature, double* inEnergy, gsl_rng *numberGen) {
    double finEnergy;
    int c = 0;
    if (gsl_rng_uniform_int(numberGen, 2) == 0) {
        finEnergy = 0;
    } else {
        finEnergy = E;
    }
    double deltaEnergy = finEnergy - *inEnergy;
    if (deltaEnergy <= 0 || gsl_rng_uniform(numberGen) < exp(-deltaEnergy / temperature)) {
        *inEnergy = finEnergy;
    }
}


int main() {
    const long int steps = pow(10,5);
    double temperature = 6.0;
    int corrAmount = 30;
    double energyAux;
    gsl_rng* numberGen = gsl_rng_alloc(gsl_rng_gfsr4);
    double energy[steps];
    double correlation[corrAmount];

    ofstream myFile1("P4E1a_T=" + to_string(temperature) + ".txt");
    if (!myFile1.is_open()) {
        cout << "Unable to open file";
    }

    if (gsl_rng_uniform_int(numberGen, 2) == 0) {
        energyAux = 0;
    } else {
        energyAux = E;
    }

    for (int i = 0; i < steps; i++) {
        energy[i] = energyAux;
        mcStep(temperature, &energyAux, numberGen);
    }

    for (int i = 0; i < corrAmount; i++) {
        double prodAvg = 0, energyAvg = 0, displacedEnergyAvg = 0;
        for (int j = 0; j < steps - i; j++) {
            prodAvg += energy[j] * energy[j+i] / (steps - i);
            energyAvg += energy[j] / (steps - i);
            displacedEnergyAvg += energy[j+i] / (steps - i);
        }
        correlation[i] = prodAvg - energyAvg * displacedEnergyAvg;
        myFile1 << i << "    " << correlation[i] << endl;
    }

    myFile1.close();
}
