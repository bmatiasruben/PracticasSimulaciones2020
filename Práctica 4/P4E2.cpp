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

void mcStep(int spins[SIZE][SIZE], double* energy, double* magnetization, double temperature, gsl_rng* numberGen, double J, double h){
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
    }
}

int main() {
    double J = 1.0;
    double h = 1.0;
    int spinLattice[SIZE][SIZE];
    long long int steps = 10000;
    int bootSteps = 100;
    gsl_rng* numberGen = gsl_rng_alloc(gsl_rng_gfsr4);
    
    ofstream myFile1("P4E2_E_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile1.is_open()) {
        myFile1 << "# T    Energy" << endl;
    }
    else cout << "Unable to open file";

    ofstream myFile2("P4E2_cv_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile2.is_open()) {
        myFile2 << "# T    Cv" << endl;
    }
    else cout << "Unable to open file";    

    ofstream myFile3("P4E2_M_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile3.is_open()) {
        myFile3 << "# T    M" << endl;
    }
    else cout << "Unable to open file";

    ofstream myFile4("P4E2_suscep_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile4.is_open()) {
        myFile4 << "# T    Suscep. magnética" << endl;
    }
    else cout << "Unable to open file";

    for (double temperature = 0.5; temperature < 8.0; temperature += 0.05) {
        double energy = 0, energyArray[steps] = {0};
        double magnetization = 0, magnetizationArray[steps] = {0};
        double energyAverage = 0, energySqrAverage = 0;
        double magnetizationAverage = 0, magnetizationSqrAverage = 0;
        double energyError = 0, magnetizationError = 0;

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

        for (int i = 0; i < 10000; i++) {
            mcStep(spinLattice, &energy, &magnetization, temperature, numberGen, J, h);
        } 

        // Proceso de medida sobre el sistema en equilibrio
        
        for (int i = 0; i < steps; i++) {
            mcStep(spinLattice, &energy, &magnetization, temperature, numberGen, J, h);

            energyArray[i] = energy;
            magnetizationArray[i] = magnetization;

            energySqrAverage += energy * energy / (steps * pow(SIZE, 4));
            energyAverage += energy / (steps * pow(SIZE, 2));
            magnetizationSqrAverage += magnetization * magnetization / (steps * pow(SIZE, 4));
            magnetizationAverage += magnetization / (steps * pow(SIZE, 2));
        }
        
        double cv = (energySqrAverage - energyAverage * energyAverage) / (temperature * temperature);
        double susceptibility = (magnetizationSqrAverage - magnetizationAverage * magnetizationAverage) / (temperature);

        // Proceso de bootstrap para calculo de errores

        double bootCvAverage = 0, bootCvSqrAverage = 0;
        double bootSuscepAverage = 0, bootSuscepSqrAverage = 0;

        for (int i = 0; i < bootSteps; i++) {
            double bootEnergySqrAverage = 0;
            double bootEnergyAverage = 0;
            double bootMagnetizationSqrAverage = 0;
            double bootMagnetizationAverage = 0;
            for (int j = 0; j < steps; j++) {
                int arrayPos = gsl_rng_uniform_int(numberGen, steps);
                bootEnergyAverage += energyArray[arrayPos] / (SIZE * SIZE * steps);
                bootEnergySqrAverage += energyArray[arrayPos] * energyArray[arrayPos] / (pow(SIZE, 4) * steps);
                bootMagnetizationAverage += magnetizationArray[arrayPos] / (SIZE * SIZE * steps);
                bootMagnetizationSqrAverage += magnetizationArray[arrayPos] * magnetizationArray[arrayPos] / (pow(SIZE, 4) * steps);
            }
            energyError += bootEnergySqrAverage / bootSteps - bootEnergyAverage * bootEnergyAverage / (bootSteps);
            magnetizationError += bootMagnetizationSqrAverage / bootSteps - bootMagnetizationAverage * bootMagnetizationAverage / (bootSteps);
            
            bootCvAverage += (bootEnergySqrAverage - bootEnergyAverage * bootEnergyAverage) / (temperature * temperature * bootSteps);
            bootCvSqrAverage += (bootEnergySqrAverage - bootEnergyAverage * bootEnergyAverage) * (bootEnergySqrAverage - bootEnergyAverage * bootEnergyAverage) / (pow(temperature, 4) * bootSteps);
            bootSuscepAverage += (bootMagnetizationSqrAverage - bootMagnetizationAverage * bootMagnetizationAverage) / (temperature * bootSteps);
            bootSuscepSqrAverage += (bootMagnetizationSqrAverage - bootMagnetizationAverage * bootMagnetizationAverage) * (bootMagnetizationSqrAverage - bootMagnetizationAverage * bootMagnetizationAverage) / (pow(temperature, 2) * bootSteps);
        }        
        energyError = sqrt(energyError);
        magnetizationError = sqrt(magnetizationError);
        double cvError = sqrt(bootCvSqrAverage - bootCvAverage * bootCvAverage);
        double suscepError = sqrt(bootSuscepSqrAverage - bootSuscepAverage * bootSuscepAverage);

        // cout << bootCvAverage << "   " << bootCvSqrAverage << "   " << cvError << endl;

        myFile1 << temperature << "   " << energyAverage << "   " << energyError << endl;
        myFile2 << temperature << "   " << cv << "   " << cvError << endl;
        myFile3 << temperature << "   " << magnetizationAverage << "   " << magnetizationError << endl;
        myFile4 << temperature << "   " << susceptibility << "   " << suscepError << endl;
    }
}
