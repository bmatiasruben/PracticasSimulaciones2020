// ------------------------------------------------------------------------------------------------------------------------------------------
// REGLAS DEL JUEGO: 
// ------------------------------------------------------------------------------------------------------------------------------------------
//
// 1 - El "mundo" está representado por una grid en 2D 
// 2 - Cada cuadrado del grid representa una criatura, o "celula". Cada celula puede estar viva (blanco) o muerta (negro)
// 3 - En cada momento del tiempo (paso de la simulacion) cada celula revisa el estado de sus primeros vecinos. El estado 
// de la celula cambia segun el numero de vecinos vivos:
//    a - Cada celula viva con menos de dos vecinos vivos muere ("underpopulation")
//    b - Cada celula viva con dos o tres vecinos sobrevive a la proxima generación
//    c - Cada celula viva con mas de tres vecinos vivos muere ("overpopulation")
//    d - Cada celula muerta con exactamente tres vecinos se vuelve una celula viva ("reproduction")
//
// ------------------------------------------------------------------------------------------------------------------------------------------

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <new>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define NX (XSIZE / PIXEL)
#define NY (YSIZE / PIXEL)
#define PIXEL 3
#define PROB 3      // Probabilidad de celula viva, ayuda a controlar la densidad de poblacion
#define XSIZE 900
#define YSIZE 900

#define GLIDERGUNX 36
#define GLIDERGUNY 9

#define EATER 4

#define GATE 270

#define FRAMERATE 10

int **mat1, **mat2;

void setup(){
    srand(time(NULL));      // seed del RNG en funcion de la hora de sistema
    mat1 = new int*[NX];    // Paso actual
    mat2 = new int*[NX];    // Siguiente paso

    for (int i = 0; i < NX; i++) {
        mat1[i] = new int[NY];
        mat2[i] = new int[NY];
    }

    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            mat1[i][j] = 0;
            mat2[i][j] = 0;
        }
    }

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, XSIZE, 0, YSIZE, -1, 1);     // Establece sistema de coordenadas
    glClearColor(0.0, 0.0, 0.0, 0.0);       // Establece el color RGB-alpha del fondo
}

int survives(int x, int y){
    int aux = 0;
    if (!x || !y || (x == NX - 1) || (y == NY - 1)) {
        // Si la celula se encuentra en el borde derecho, superior, izquierdo, e inferior, está muerta
        return 0;
    } else {
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                aux += mat1[i][j];
            }
        }
        aux -= mat1[x][y];      // Resta 1 si la celula está viva, 0 si no.
        aux = (mat1[x][y]) ? ((aux == 2) || (aux == 3)) : (aux == 3);
        // Condicional resumido. Si mat1[x][y] = 1, entonces chequea aux y devuelve un 1 si es igual a 2 o 3.
        // Si mat1[x][y] = 0, entonces chequea aux y devuelve un 1 solo si es igual a 3.
        return aux;
    }
}

// Función para crear una configuración inicial aleatoria
void randomConfig(){
    srand(time(NULL));

    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            mat1[i][j] = PROB > (rand()%10);
        }
    }    
}

// Funciones para flipear una matriz cuadrada
void flipVertical(int startX, int startY, int sizeX, int sizeY){
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY / 2; j++) {
            int temp = mat1[startX + i][startY + j];
            mat1[startX + i][startY + j] = mat1[startX + i][startY + sizeY - j - 1];
            mat1[startX + i][startY + sizeY - j - 1] = temp;
        }
    }    
}
void flipHorizontal(int startX, int startY, int sizeX, int sizeY){
    for (int j = 0; j < sizeY; j++) {
        for (int i = 0; i < sizeX / 2; i++) {
            int temp = mat1[startX + i][startY + j];
            mat1[startX + i][startY + j] = mat1[startX + sizeX - i - 1][startY + j];
            mat1[startX + sizeX - i - 1][startY + j] = temp;
        }
    }
}

// Función para crearme Glider Guns con las diferentes orientaciones posibles (u = up, d = down, r = right, l = left), donde me permite ingresar el paso en el que se encuentra con step
void gliderGunH(int startX, int startY, string orientation, int step){
    for (int i = startX; i < GLIDERGUNX; i++) {
        for (int j = startY; j < GLIDERGUNY; j++) {
            mat1[i][j] = 0;
        }
    }
    // Cuadrado izquierdo
    mat1[startX][startY + 4] = 1;
    mat1[startX][startY + 5] = 1;
    mat1[startX + 1][startY + 4] = 1;
    mat1[startX + 1][startY + 5] = 1;

    // Cuadrado derecho
    mat1[startX + GLIDERGUNX - 1][startY + 2] = 1;
    mat1[startX + GLIDERGUNX - 1][startY + 3]  = 1;
    mat1[startX + GLIDERGUNX - 2][startY + 2] = 1;
    mat1[startX + GLIDERGUNX - 2][startY + 3]  = 1;

    // Forma izquierda inicial
    mat1[startX + 12][startY + 2] = 1;
    mat1[startX + 13][startY + 2] = 1;
    mat1[startX + 11][startY + 3] = 1;
    mat1[startX + 15][startY + 3] = 1;
    mat1[startX + 10][startY + 4] = 1;
    mat1[startX + 16][startY + 4] = 1;   
    mat1[startX + 10][startY + 5] = 1;
    mat1[startX + 14][startY + 5] = 1;
    mat1[startX + 16][startY + 5] = 1;
    mat1[startX + 17][startY + 5] = 1;
    mat1[startX + 10][startY + 6] = 1;
    mat1[startX + 16][startY + 6] = 1; 
    mat1[startX + 11][startY + 7] = 1;
    mat1[startX + 15][startY + 7] = 1; 
    mat1[startX + 12][startY + 8] = 1;
    mat1[startX + 13][startY + 8] = 1;   

    // Forma derecha inicial
    mat1[startX + 24][startY] = 1;
    mat1[startX + 22][startY + 1] = 1;
    mat1[startX + 24][startY + 1] = 1;
    mat1[startX + 20][startY + 2] = 1;
    mat1[startX + 21][startY + 2] = 1;
    mat1[startX + 20][startY + 3] = 1;
    mat1[startX + 21][startY + 3] = 1;
    mat1[startX + 20][startY + 4] = 1;
    mat1[startX + 21][startY + 4] = 1;
    mat1[startX + 22][startY + 5] = 1;
    mat1[startX + 24][startY + 5] = 1;
    mat1[startX + 24][startY + 6] = 1;

    int tempArray[GLIDERGUNX][GLIDERGUNY];
    for (int steps = 0; steps < step; steps++) {
        for (int i = 0; i < GLIDERGUNX; i++) {
            for (int j = 0; j < GLIDERGUNY; j++) {
                mat2[startX + i][startY + j] = survives(startX + i, startY + j);
            }
        }
        for (int i = 0; i < GLIDERGUNX; i++) {
            for (int j = 0; j < GLIDERGUNY; j++) {
                tempArray[i][j] = mat1[startX + i][startY + j];
            }
        }
        for (int i = 0; i < GLIDERGUNX; i++) {
            for (int j = 0; j < GLIDERGUNY; j++) {
                mat1[startX + i][startY + j] = mat2[startX + i][startY + j];
                mat2[startX + i][startY + j] = tempArray[i][j];
            }
        }    
        // Estos dos pasos me aseguran que no se me rompa todo al poner pasos mayores a 15
        mat1[startX + 22][startY + GLIDERGUNY - 1] = 0;
        mat1[startX + 21][startY + GLIDERGUNY - 1] = 0;
    }

    if (orientation == "dr") {
        flipVertical(startX, startY, GLIDERGUNX, GLIDERGUNY);
    } else if (orientation == "ul") {
        flipHorizontal(startX, startY, GLIDERGUNX, GLIDERGUNY);
    } else if (orientation == "dl") {
        flipVertical(startX, startY, GLIDERGUNX, GLIDERGUNY);
        flipHorizontal(startX, startY, GLIDERGUNX, GLIDERGUNY);
    }

}
void gliderGunV(int startX, int startY, string orientation, int step){
    for (int i = startX; i < GLIDERGUNY; i++) {
        for (int j = startY; j < GLIDERGUNX; j++) {
            mat1[i][j] = 0;
        }
    }
    // Cuadrado izquierdo
    mat1[startX + 4][startY] = 1;
    mat1[startX + 5][startY] = 1;
    mat1[startX + 4][startY + 1] = 1;
    mat1[startX + 5][startY + 1] = 1;

    // Cuadrado derecho
    mat1[startX + 2][startY + GLIDERGUNX - 1] = 1;
    mat1[startX + 3][startY + GLIDERGUNX - 1]  = 1;
    mat1[startX + 2][startY + GLIDERGUNX - 2] = 1;
    mat1[startX + 3][startY + GLIDERGUNX - 2]  = 1;

    // Forma izquierda inicial
    mat1[startX + 2][startY + 12] = 1;
    mat1[startX + 2][startY + 13] = 1;
    mat1[startX + 3][startY + 11] = 1;
    mat1[startX + 3][startY + 15] = 1;
    mat1[startX + 4][startY + 10] = 1;
    mat1[startX + 4][startY + 16] = 1;   
    mat1[startX + 5][startY + 10] = 1;
    mat1[startX + 5][startY + 14] = 1;
    mat1[startX + 5][startY + 16] = 1;
    mat1[startX + 5][startY + 17] = 1;
    mat1[startX + 6][startY + 10] = 1;
    mat1[startX + 6][startY + 16] = 1; 
    mat1[startX + 7][startY + 11] = 1;
    mat1[startX + 7][startY + 15] = 1; 
    mat1[startX + 8][startY + 12] = 1;
    mat1[startX + 8][startY + 13] = 1;   

    // Forma derecha inicial
    mat1[startX][startY + 24] = 1;
    mat1[startX + 1][startY + 22] = 1;
    mat1[startX + 1][startY + 24] = 1;
    mat1[startX + 2][startY + 20] = 1;
    mat1[startX + 2][startY + 21] = 1;
    mat1[startX + 3][startY + 20] = 1;
    mat1[startX + 3][startY + 21] = 1;
    mat1[startX + 4][startY + 20] = 1;
    mat1[startX + 4][startY + 21] = 1;
    mat1[startX + 5][startY + 22] = 1;
    mat1[startX + 5][startY + 24] = 1;
    mat1[startX + 6][startY + 24] = 1;

    int tempArray[GLIDERGUNX][GLIDERGUNY];
    for (int steps = 0; steps < step; steps++) {
        for (int i = 0; i < GLIDERGUNY; i++) {
            for (int j = 0; j < GLIDERGUNX; j++) {
                mat2[startX + i][startY + j] = survives(startX + i, startY + j);
            }
        }
        for (int i = 0; i < GLIDERGUNY; i++) {
            for (int j = 0; j < GLIDERGUNX; j++) {
                tempArray[i][j] = mat1[startX + i][startY + j];
            }
        }
        for (int i = 0; i < GLIDERGUNY; i++) {
            for (int j = 0; j < GLIDERGUNX; j++) {
                mat1[startX + i][startY + j] = mat2[startX + i][startY + j];
                mat2[startX + i][startY + j] = tempArray[i][j];
            }
        }    
        // Estos dos pasos me aseguran que no se me rompa todo al poner pasos mayores a 15
        mat1[startX + GLIDERGUNY - 1][startY + 22] = 0;
        mat1[startX + GLIDERGUNY - 1][startY + 22] = 0;
    }

    if (orientation == "dr") {
        flipVertical(startX, startY, GLIDERGUNY, GLIDERGUNX);
    } else if (orientation == "ul") {
        flipHorizontal(startX, startY, GLIDERGUNY, GLIDERGUNX);
    } else if (orientation == "dl") {
        flipVertical(startX, startY, GLIDERGUNY, GLIDERGUNX);
        flipHorizontal(startX, startY, GLIDERGUNY, GLIDERGUNX);
    }
}

// Función para crearme gliders individuales
void glider(int startX, int startY, int step){
    mat1[startX][startY + 1] = 1;
    mat1[startX + 1][startY + 1] = 1;
    mat1[startX + 2][startY + 1] = 1;
    mat1[startX + 2][startY + 2] = 1;
    mat1[startX + 1][startY + 3] = 1;

    int tempArray[4][4];
    for (int steps = 0; steps < step; steps++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                mat2[startX + i][startY + j] = survives(startX + i, startY + j);
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tempArray[i][j] = mat1[startX + i][startY + j];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                mat1[startX + i][startY + j] = mat2[startX + i][startY + j];
                mat2[startX + i][startY + j] = tempArray[i][j];
            }
        }    
    }

}

// Función para crearme un Eater con las diferentes orientaciones posibles
void eaterV(int startX, int startY, string orientation){
    for (int i = 0; i < EATER; i++) {
        for (int j = 0; j < EATER; j++) {
            mat1[startX + i][startY + j] = 0;
        }
    }
    mat1[startX][startY] = 1;
    mat1[startX + 1][startY] = 1;
    mat1[startX][startY + 1] = 1;
    mat1[startX + 2][startY + 1] = 1;
    mat1[startX + 2][startY + 2] = 1;
    mat1[startX + 2][startY + 3] = 1;
    mat1[startX + 3][startY + 3] = 1;
    if (orientation == "dr") {
        for (int i = 0; i < EATER; i++) {
            for (int j = 0; j < EATER / 2; j++) {
                int temp = mat1[startX + i][startY + j];
                mat1[startX + i][startY + j] = mat1[startX + i][startY + EATER - j - 1];
                mat1[startX + i][startY + EATER - j - 1] = temp;
            }
        }
    } else if (orientation == "ul") {
        for (int j = 0; j < EATER; j++) {
            for (int i = 0; i < EATER / 2; i++) {
                int temp = mat1[startX + i][startY + j];
                mat1[startX + i][startY + j] = mat1[startX + EATER - i - 1][startY + j];
                mat1[startX + EATER - i - 1][startY + j] = temp;
            }
        }
    } else if (orientation == "dl") {
        for (int i = 0; i < EATER; i++) {
            for (int j = 0; j < EATER / 2; j++) {
                int temp = mat1[startX + i][startY + j];
                mat1[startX + i][startY + j] = mat1[startX + i][startY + EATER - j - 1];
                mat1[startX + i][startY + EATER - j - 1] = temp;
            }
        }
        for (int j = 0; j < EATER; j++) {
            for (int i = 0; i < EATER / 2; i++) {
                int temp = mat1[startX + i][startY + j];
                mat1[startX + i][startY + j] = mat1[startX + EATER - i - 1][startY + j];
                mat1[startX + EATER - i - 1][startY + j] = temp;
            }
        }
    }
}
void eaterH(int startX, int startY, string orientation){
    for (int i = 0; i < EATER; i++) {
        for (int j = 0; j < EATER; j++) {
            mat1[startX + i][startY + j] = 0;
        }
    }
    mat1[startX][startY] = 1;
    mat1[startX][startY + 1] = 1;
    mat1[startX + 1][startY] = 1;
    mat1[startX + 1][startY + 2] = 1;
    mat1[startX + 2][startY + 2] = 1;
    mat1[startX + 3][startY + 2] = 1;
    mat1[startX + 3][startY + 3] = 1;
    if (orientation == "dr") {
        for (int i = 0; i < EATER; i++) {
            for (int j = 0; j < EATER / 2; j++) {
                int temp = mat1[startX + i][startY + j];
                mat1[startX + i][startY + j] = mat1[startX + i][startY + EATER - j - 1];
                mat1[startX + i][startY + EATER - j - 1] = temp;
            }
        }
    } else if (orientation == "ul") {
        for (int j = 0; j < EATER; j++) {
            for (int i = 0; i < EATER / 2; i++) {
                int temp = mat1[startX + i][startY + j];
                mat1[startX + i][startY + j] = mat1[startX + EATER - i - 1][startY + j];
                mat1[startX + EATER - i - 1][startY + j] = temp;
            }
        }
    } else if (orientation == "dl") {
        for (int i = 0; i < EATER; i++) {
            for (int j = 0; j < EATER / 2; j++) {
                int temp = mat1[startX + i][startY + j];
                mat1[startX + i][startY + j] = mat1[startX + i][startY + EATER - j - 1];
                mat1[startX + i][startY + EATER - j - 1] = temp;
            }
        }
        for (int j = 0; j < EATER; j++) {
            for (int i = 0; i < EATER / 2; i++) {
                int temp = mat1[startX + i][startY + j];
                mat1[startX + i][startY + j] = mat1[startX + EATER - i - 1][startY + j];
                mat1[startX + EATER - i - 1][startY + j] = temp;
            }
        }
    }
}

void screen(){
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            glPointSize(PIXEL);     // Define el tamaño del pixel a dibujar
            glColor3f(mat1[i][j], mat1[i][j], mat1[i][j]);      // Pinta el pixel de negro si está muerta, y de blanco si está viva
            glBegin(GL_POINTS);     // Empieza a dibujar puntos
                glVertex2f((i + 0.5) * PIXEL, j * PIXEL);       // Multiplico por PIXEL para pasarlo de numero de celda a coordenada
            glEnd();
        }
    }

    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            mat2[i][j] = survives(i, j);
        }
    }
    glutSwapBuffers();
}

void notGate(int startX, int startY, string orientation){
    gliderGunH(startX + 90, startY + 2, "ur", 21);
    eaterH(startX + 166, startY + 26, "dr");
    
    gliderGunV(startX + 64, startY + 110, "dr", 22);
    gliderGunV(startX + 46, startY + 201, "dr", 17);
    gliderGunH(startX + 29, startY + 188, "ur", 28);
    for (int i = 0; i < 3; i++){
        glider(startX + 78 + 15 * i, startY + 115 - 15 * i, 3);
        glider(startX + 71 + 15 * i, startY + 122 - 15 * i, 1);
    }   
    if (orientation == "dr") {
        flipVertical(startX, startY, GATE, GATE);
    }
}

void andGate(int startX, int startY, string orientation){
    gliderGunV(startX + 65, startY + 6, "ur", 1);
    gliderGunH(startX + 1, startY + 113, "dr", 9);
    eaterH(startX + 81, startY + 82, "ur");
    eaterH(startX + 42, startY + 122, "dl");
    gliderGunH(startX + 6, startY + 166, "dr", 28);
    gliderGunV(startX + 46, startY + 156, "dl", 9);
    gliderGunV(startX + 149, startY + 216, "dl", 2);
    gliderGunV(startX + 154, startY + 51, "ur", 1);
    gliderGunH(startX + 167, startY + 68, "ul", 20);
    gliderGunV(startX + 138, startY + 125, "ur", 15);
    gliderGunH(startX + 121, startY + 165, "dr", 26);
    eaterV(startX + 102, startY + 151, "ul");
    eaterV(startX + 168, startY + 201, "ul");
    gliderGunH(startX + 230, startY + 121, "ul", 12);
    eaterV(startX + 168, startY + 23, "dr");
}

void swap() {
    int **tmp;
    tmp = mat1;
    mat1 = mat2;
    mat2 = tmp;
}

void timer(int) {
    screen();
    swap();
    glutTimerFunc(FRAMERATE, timer, 0);
}

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(XSIZE, YSIZE);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Game of Life");
    setup();
    andGate(20, 20, "dr");
    //randomConfig();
    //gliderGunH(100, 200, "dr", 0);
    //notGate(20, 20, "dr");
    glutDisplayFunc(screen);
    timer(0);
    glutMainLoop();

    return EXIT_SUCCESS;
}