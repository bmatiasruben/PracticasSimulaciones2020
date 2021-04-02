#include <gsl/gsl_rng.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>

using namespace std;

#define SIZE 5

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

void mcStep(int spins[SIZE][SIZE], double* energy, double* magnetization, double temperature, gsl_rng* numberGen, double J, double h, double* magnetAvg, double* magnetSqrAvg){
    double auxMagnetAvg = 0, auxMagnetSqrAvg = 0;
    for(int i = 0; i < SIZE*SIZE; i++){
        int swapX = gsl_rng_uniform_int(numberGen, SIZE);
        int swapY = gsl_rng_uniform_int(numberGen, SIZE);

        int deltaMagnet = -2 * spins[swapX][swapY];
        int deltaNeighbour = -2 * spins[swapX][swapY] * (spins[(swapX+SIZE-1)%SIZE][swapY] + spins[(swapX+1)%SIZE][swapY] + spins[swapX][(swapY+SIZE-1)%SIZE] + spins[swapX][(swapY+1)%SIZE]);
        double deltaEnergy = -J * deltaNeighbour - h * deltaMagnet;

        if (deltaEnergy <= 0 || gsl_rng_uniform(numberGen) < exp(-deltaEnergy / temperature)) {
            spins[swapX][swapY] *= -1;
            *magnetization += deltaMagnet;
            *energy += deltaEnergy;
        }
        auxMagnetAvg += *magnetization / (SIZE * SIZE);
        auxMagnetSqrAvg += *magnetization * *magnetization / (SIZE * SIZE);
    }
    *magnetAvg = *magnetization;
    *magnetSqrAvg = *magnetization * *magnetization;    
}

int main() {
    double J = 1.0;
    double h = 1.0;
    int spinLattice[SIZE][SIZE];
    long long int steps = 10000;
    const double critTemperature = 2 * J / (log(1 + sqrt(2)));
    gsl_rng* numberGen = gsl_rng_alloc(gsl_rng_gfsr4);

    ofstream myFile("P4E4_suscep_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile.is_open()) {
        myFile << "# T    susceptibilidad" << endl;
    }
    else cout << "Unable to open file";

    for (double temperature = 2.0; temperature < 10.0; temperature += 0.05) {
        double energy = 0;
        double magnetization = 0;
        double energyAverage = 0, energySqrAverage = 0;
        double magnetizationAverage = 0, magnetizationSqrAverage = 0;
        double auxEnergyAvg = 0, auxMagnetAvg = 0, auxEnergySqrAvg = 0, auxMagnetSqrAvg = 0;

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
        energy = -J * neighbourCalc(spinLattice) - h * magnetization;

        // Proceso de termalización

        for (int i = 0; i < 1000; i++) {
            mcStep(spinLattice, &energy, &magnetization, temperature, numberGen, J, h, &auxMagnetAvg, &auxMagnetSqrAvg);
        } 

        // Proceso de medida sobre el sistema en equilibrio
        
        for (int i = 0; i < steps; i++) {
            mcStep(spinLattice, &energy, &magnetization, temperature, numberGen, J, h, &auxMagnetAvg, &auxMagnetSqrAvg);

            magnetizationSqrAverage += auxMagnetSqrAvg / (pow(SIZE, 4) * steps);
            magnetizationAverage += auxMagnetAvg / (pow(SIZE, 2) * steps);
        }
        
        double susceptibility = (magnetizationSqrAverage - magnetizationAverage * magnetizationAverage) / (temperature);
        cout << magnetizationAverage << "   " << magnetizationSqrAverage << "   " << susceptibility << endl;
        myFile << temperature << "   " << susceptibility << endl;
    }
}
