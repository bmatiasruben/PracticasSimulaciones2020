#include <gsl/gsl_rng.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>

using namespace std;

#define SIZE 30

int neighbourCalc(int lattice[SIZE][SIZE]) {
    int neighbour = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            neighbour += lattice[i][j] * (lattice[(i+SIZE-1)%SIZE][j] + lattice[(i+1)%SIZE][j] + lattice[i][(j+SIZE-1)%SIZE] + lattice[i][(j+1)%SIZE]);
        }
    }
    neighbour /= 2;
    return neighbour;
}

void mcStep(int spins[SIZE][SIZE], double* magnetization, double temperature, gsl_rng* numberGen, double J, double h){
    for(int i = 0; i < SIZE*SIZE; i++){
        int swapX = gsl_rng_uniform_int(numberGen, SIZE);
        int swapY = gsl_rng_uniform_int(numberGen, SIZE);

        int deltaMagnet = -2 * spins[swapX][swapY];
        int deltaNeighbour = -2 * spins[swapX][swapY] * (spins[(swapX+SIZE-1)%SIZE][swapY] + spins[(swapX+1)%SIZE][swapY] + spins[swapX][(swapY+SIZE-1)%SIZE] + spins[swapX][(swapY+1)%SIZE]);
        double deltaEnergy = -J * deltaNeighbour - h * deltaMagnet;

        if (deltaEnergy <= 0 || gsl_rng_uniform(numberGen) < exp(-deltaEnergy / temperature)) {
            spins[swapX][swapY] *= -1;
            *magnetization += deltaMagnet;
        }
    }
}

int main() {
    double J = 1.0;
    double h = 0.0;
    int spinLattice[SIZE][SIZE];
    long long int steps = 1000;
    gsl_rng* numberGen = gsl_rng_alloc(gsl_rng_gfsr4);

    ofstream myFile3("P4E2_autocorrTime_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile3.is_open()) {
    }
    else cout << "Unable to open file";

    for (double temperature = 1.0; temperature < 5.0; temperature += 0.05) {
        double magnetization = 0, magnetizationArray[steps] = {0};
        double autocorr[steps] = {0};
        double autocorrAux = 0;

        // Creo una distribución aleatoria de spin ups and downs y calculo la energía

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int generatedNumber = gsl_rng_uniform_int(numberGen, 2);
                if (generatedNumber == 0) {
                    spinLattice[i][j] = generatedNumber - 1;
                    magnetization--;
                } else {
                    spinLattice[i][j] = generatedNumber;
                    magnetization++;
                }
            }
        }

        // Proceso de termalización

        for (int i = 0; i < 1000; i++) {
            mcStep(spinLattice, &magnetization, temperature, numberGen, J, h);
        } 

        // Proceso de medida sobre el sistema en equilibrio
        
        for (int i = 0; i < steps; i++) {
            mcStep(spinLattice, &magnetization, temperature, numberGen, J, h);
            magnetizationArray[i] = magnetization / (SIZE * SIZE);
        }
        myFile3 << temperature;
        for (int i = 0; i < steps; i++) {
            autocorrAux = 0;
            autocorr[i] = 0;
            for (int j = 0; j < steps - i; j++) {
                for (int k = 0; k < steps - i; k++) {
                    autocorrAux += magnetizationArray[k] / (steps - i + 1);
                }
                autocorr[i] += magnetizationArray[j + i] * (magnetizationArray[i] - autocorrAux);
            }
            autocorr[i] /= (steps - i + 1);
            myFile3 << "   " << autocorr[i];
        }
        myFile3 << endl;
    }
}