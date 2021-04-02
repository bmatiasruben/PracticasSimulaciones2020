#include <gsl/gsl_rng.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>

using namespace std;

#define SIZE 100

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

int main() {
    int spinLattice[SIZE][SIZE];
    long long int monteCarloSteps = 1000000000;
    const long int averageSteps1 = 100000;
    const long int averageSteps2 = 10000;
    double h = 0.0;
    gsl_rng* numberGen = gsl_rng_alloc(gsl_rng_gfsr4);
    
    ofstream myFile1("P4E2_E_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile1.is_open()) {
        myFile1 << "# Temp     Energy" << endl;
    }
    else cout << "Unable to open file";

    ofstream myFile2("P4E2_cv_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile2.is_open()) {
        myFile2 << "# Temp     Specific Heat" << endl;
    }
    else cout << "Unable to open file";    

    ofstream myFile3("P4E2_M_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile3.is_open()) {
        myFile3 << "# Temp     Magnetization" << endl;
    }
    else cout << "Unable to open file";

    ofstream myFile4("P4E2_suscep_N=" + to_string(SIZE) + "_h=" + to_string(h) + ".txt");
    if (myFile4.is_open()) {
        myFile4 << "# Temp     Magn. susceptibility" << endl;
    }
    else cout << "Unable to open file";
    
    for (double temperature = 1.0; temperature < 5.0; temperature += 0.05) {
        double J = 1.0;
        double energyAverage = 0, energySqrAverage = 0;
        double magnetizationAverage = 0, magnetizationSqrAverage = 0;
        double energyTotal[averageSteps1] = {0};
        double magnetizationTotal[averageSteps1] = {0};

        // Creo una distribución aleatoria de spin ups and downs
        magnetizationTotal[0] = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int generatedNumber = gsl_rng_uniform_int(numberGen, 2);
                if (generatedNumber == 0) {
                    spinLattice[i][j] = generatedNumber - 1;
                    magnetizationTotal[0]--;
                } else {
                    spinLattice[i][j] = generatedNumber;
                    magnetizationTotal[0]++;
                }
            }
        }

        // Hago llegar la red al equilibrio

        for (int i = 0; i < monteCarloSteps; i++) {
            int swapX = gsl_rng_uniform_int(numberGen, SIZE);
            int swapY = gsl_rng_uniform_int(numberGen, SIZE);
 
            int deltaMagnet = -2 * spinLattice[swapX][swapY];
            int deltaNeighbour = -2 * spinLattice[swapX][swapY] * (spinLattice[(swapX+SIZE-1)%SIZE][swapY] + spinLattice[(swapX+1)%SIZE][swapY] + spinLattice[swapX][(swapY+SIZE-1)%SIZE] + spinLattice[swapX][(swapY+1)%SIZE]);
            double deltaEnergy = -J * deltaNeighbour - h * deltaMagnet;

            if (deltaEnergy <= 0 || gsl_rng_uniform(numberGen) < exp(-deltaEnergy / temperature)) {
                spinLattice[swapX][swapY] *= -1;
                magnetizationTotal[0] += deltaMagnet;
            }
        }

        // Mido las variables del sistema ahora que está en equilibrio

        energyTotal[0] = -J * neighbourCalc(spinLattice) - h * magnetizationTotal[0];   

        for (int i = 0; i < SIZE*SIZE; i++) {
            int swapX = gsl_rng_uniform_int(numberGen, SIZE);
            int swapY = gsl_rng_uniform_int(numberGen, SIZE);

            int deltaMagnet = -2 * spinLattice[swapX][swapY];
            int deltaNeighbour = -2 * spinLattice[swapX][swapY] * (spinLattice[(swapX+SIZE-1)%SIZE][swapY] + spinLattice[(swapX+1)%SIZE][swapY] + spinLattice[swapX][(swapY+SIZE-1)%SIZE] + spinLattice[swapX][(swapY+1)%SIZE]);
            double deltaEnergy = - J * deltaNeighbour - h * deltaMagnet;

            if (deltaEnergy <= 0 || gsl_rng_uniform(numberGen) < exp(-deltaEnergy / temperature)) {
                spinLattice[swapX][swapY] *= -1;
                magnetizationTotal[0] += deltaMagnet;
                energyTotal[0] += deltaEnergy;
            }
            // cout << i << "   " <<  magnetizationTotal[0] << endl;
            energySqrAverage += energyTotal[0] * energyTotal[0] / (pow(SIZE,2));
            energyAverage += energyTotal[0] / (pow(SIZE,2));
            magnetizationSqrAverage += magnetizationTotal[0] * magnetizationTotal[0] / (pow(SIZE,2));
            magnetizationAverage += magnetizationTotal[0] / (pow(SIZE,2));        
            // cout << magnetizationAverage * magnetizationAverage << "   " << magnetizationSqrAverage << endl;    
        }
        // cout << magnetizationTotal[0] / (SIZE * SIZE) << "   " << magnetizationAverage << "   " << magnetizationSqrAverage << endl;
        double cv = (energySqrAverage - energyAverage * energyAverage) / (temperature * temperature * SIZE*SIZE);
        double susceptibility = (magnetizationSqrAverage - magnetizationAverage * magnetizationAverage) / (temperature  * SIZE*SIZE);
        // cout << cv << "   " << susceptibility << endl; 


        // Bootstrap para calculo de errores

        double bootCvAverage = 0, bootCvSqrAverage = 0;
        double bootSuscepAverage = 0, bootSuscepSqrAverage = 0;

        for (int i = 1; i < averageSteps1; i++) {
            int swapX = gsl_rng_uniform_int(numberGen, SIZE);
            int swapY = gsl_rng_uniform_int(numberGen, SIZE);

            int deltaMagnet = -2 * spinLattice[swapX][swapY];
            int deltaNeighbour = -2 * spinLattice[swapX][swapY] * (spinLattice[(swapX+SIZE-1)%SIZE][swapY] + spinLattice[(swapX+1)%SIZE][swapY] + spinLattice[swapX][(swapY+SIZE-1)%SIZE] + spinLattice[swapX][(swapY+1)%SIZE]);
            double deltaEnergy = - J * deltaNeighbour - h * deltaMagnet;

            if (deltaEnergy <= 0 || gsl_rng_uniform(numberGen) < exp(-deltaEnergy / temperature)) {
                spinLattice[swapX][swapY] *= -1;
                magnetizationTotal[i] = magnetizationTotal[i-1] + deltaMagnet;
                energyTotal[i] = energyTotal[i-1] + deltaEnergy;
            } else {
                magnetizationTotal[i] = magnetizationTotal[i-1];
                energyTotal[i] = energyTotal[i-1];
            }
        }

        for (int i = 0; i < averageSteps2; i++) {
            double bootEnergySqrAverage = 0;
            double bootEnergyAverage = 0;
            double bootMagnetizationSqrAverage = 0;
            double bootMagnetizationAverage = 0;
            for (int j = 0; j < averageSteps1; j++) {
                int arrayPos = gsl_rng_uniform_int(numberGen, averageSteps1);
                bootEnergyAverage += energyTotal[arrayPos] / averageSteps1;
                bootEnergySqrAverage += energyTotal[arrayPos] * energyTotal[arrayPos] / averageSteps1;
                bootMagnetizationAverage += magnetizationTotal[arrayPos] / averageSteps1;
                bootMagnetizationSqrAverage += magnetizationTotal[arrayPos] * magnetizationTotal[arrayPos] / averageSteps1;
            }
            bootCvAverage += (bootEnergySqrAverage - bootEnergyAverage * bootEnergyAverage) / (SIZE * SIZE * temperature * temperature * averageSteps2);
            bootCvSqrAverage += (bootEnergySqrAverage - bootEnergyAverage * bootEnergyAverage) * (bootEnergySqrAverage - bootEnergyAverage * bootEnergyAverage) / (pow(SIZE, 4) * pow(temperature, 4) * averageSteps2);
            bootSuscepAverage += (bootMagnetizationSqrAverage - bootMagnetizationAverage * bootMagnetizationAverage) / (SIZE * SIZE * temperature * averageSteps2);
            bootSuscepSqrAverage += (bootMagnetizationSqrAverage - bootMagnetizationAverage * bootMagnetizationAverage) * (bootMagnetizationSqrAverage - bootMagnetizationAverage * bootMagnetizationAverage) / (pow(SIZE, 4) * pow(temperature, 2) * averageSteps2);
        }

        double errorCv = sqrt(bootCvSqrAverage - bootCvAverage * bootCvAverage);
        double errorSuscep = sqrt(bootSuscepSqrAverage - bootSuscepAverage * bootSuscepAverage);

        myFile1 << temperature << "   " << energyTotal[0] / (SIZE * SIZE) << "   " << errorEnergy << endl;
        myFile2 << temperature << "   " << cv << "   " << errorCv << endl;
        myFile3 << temperature << "   " << magnetizationTotal[0] / (SIZE * SIZE) << "   " << errorMagnetization << endl;
        myFile4 << temperature << "   " << susceptibility << "   " << errorSuscep << endl;
    }
}


            // Correlación

            double corrSpinSpinAux[SIZE] = {0};
            double distTimes[SIZE] = {0};

            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    int dist = abs(j - k);
                    corrSpinSpinAux[dist] = spinLattice[i][i]*spinLattice[j][i];
                    corrSpinSpinAux[dist] = spinLattice[i][i]*spinLattice[i][j];
                    distTimes[dist] += 2;
                }
            }
            for (int j = 0; j < SIZE; j++) {
                corrSpinSpin[j] += corrSpinSpinAux[i] / ((double)distTimes[j] * steps);
            }
        }

        for (int i = 0; i < SIZE; i++) {
            // cout << corrSpinSpinAux[i] << "   " << distTimes[i] << endl;
            corrSpinSpin[j] -= magnetizationAverage * magnetizationAverage;