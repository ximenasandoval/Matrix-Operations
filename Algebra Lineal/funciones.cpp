/*
Nombre del archivo: funciones.cpp
Nombre del autor: Sandoval del Hoyo María Ximena
Fecha: 090219
Descripción: Archivo donde se encuentran las funciones para operar matrices y vectores
                por medio de punteros; la documentación se encuentra en funciones.h
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include<windows.h>

#include "funciones.h"


using namespace std;

int main()
{
    system("pause");
    return 0;
}

//---------------------------------------------------------------------------------------------

void imprimeMatriz(float *m1, int m, int n){
    float *ptr;
    ptr = m1;
    cout.precision(4);
    enum simbSimple{BV= 179, ESD = 191, EII, BH = 196, EID = 217, ESI};
    cout << char(ESI);
    for (int i = 0; i < n*10; ++i) cout << " ";
    cout << char(ESD) << endl;
    for (int i = 0; i < m; ++i){
        cout << char(BV);
        for (int j = 0; j < n; ++j, ptr++){
            cout << setw(10) << (*ptr);
        }
        cout << char(BV)<< endl;
    }
    cout << char(EII);
    for (int i = 0; i < n*10; ++i) cout << " ";
    cout << char(EID) << endl;
}

void imprimeVector(float *v, int n){
    imprimeMatriz(v, n, 1);
}

void sumaVectores(float *v1, float *v2, float *resul, int n){
    float *ptr1, *ptr2, *ptr3;
    ptr1 = v1;
    ptr2 = v2;
    ptr3 = resul;

    for (int i = 0; i < n; i++, ptr1++, ptr2++, ptr3++){
        *ptr3 = (*ptr1) + (*ptr2);
    }
}

void restaVectores(float *v1, float *v2, float *resul, int n){
    float *ptr1, *ptr2, *ptr3;
    ptr1 = v1;
    ptr2 = v2;
    ptr3 = resul;

    for (int i = 0; i < n; i++, ptr1++, ptr2++, ptr3++){
        *ptr3 = (*ptr1) - (*ptr2);
    }
}

void multiplicaEscalar(float *v1, float *resul, int n, float c){
    float *ptr1, *ptr2;
    ptr1 = v1;
    ptr2 = resul;

    for (int i = 0; i < n; i++, ptr1++, ptr2++){
        *ptr2 = (*ptr1) * c;
    }
}

float productoPunto(float *v1, float *v2, int n){
    float *ptr1, *ptr2, resul = 0;
    ptr1 = v1;
    ptr2 = v2;

    for (int i = 0; i < n; i++, ptr1++, ptr2++){
        resul += (*ptr1) * (*ptr2);
    }

    return resul;

}

float normaVector(float *v1,int n){
    float *ptr1, resul;
    ptr1 = v1;
    resul = productoPunto(v1, v1, n);

    return sqrt(resul);
}

float anguloVectores(float *v1, float *v2, int n){
    float *ptr1,*ptr2, resul;
    ptr1 = v1;
    ptr2 = v2;
    resul = productoPunto(v1, v2, n) / (normaVector(v1, n) * normaVector(v2, n));

    return acos(resul);
}

void sumaMatrices(float *m1, float *m2, float *m3, int m, int n){
    float *ptr1, *ptr2, *ptr3;
    ptr1 = m1;
    ptr2 = m2;
    ptr3 = m3;

    for(int i = 0; i < m * n; i++, ptr1++, ptr2++, ptr3++){
        *ptr3 = (*ptr1) + (*ptr2);
    }
}

float* creaMatriz(int m, int n){
    float *arreglo = NULL;

    try {
         arreglo = new float [m * n];

    } catch(std::bad_alloc &exc){
        delete [] arreglo;
        arreglo = NULL;
        throw "Ocurri\xA2 un error en la localizaci\xA2n de la memoria para la creaci\xA2n del arreglo";
        return NULL;
    }

   return arreglo;
}

float *creaVector(int n){
    return creaMatriz(n, 1);
}

void destruyeMatriz(float *&matriz){
    delete [] matriz;
    matriz = NULL;
}

void restaMatrices(float *m1, float *m2, float *m3, int m, int n){
    float *ptr1, *ptr2, *ptr3;
    ptr1 = m1;
    ptr2 = m2;
    ptr3 = m3;

    for(int i = 0; i < m * n; i++, ptr1++, ptr2++, ptr3++){
        *ptr3 = (*ptr1) - (*ptr2);
    }
}

void matrizPorEscalar(float *m1, float *m2, int m, int n, int c){
    multiplicaEscalar(m1, m2, m * n, c);
}

void multiplaMatrices(float *m1, float *m2, float *m3, int m, int n, int p){
    float *p1, *p2, *p3;
    p1 = m1;
    p2 = m2;
    p3 = m3;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < p; j++, p3++){
            float resultado = 0;
            p1 = m1 + n * i;
            p2 = m2 + j;
            for (int k = 0; k < n; k++, p1++, p2+=p){
                resultado += (*p1) * (*p2);
            }
            *p3 = resultado;
            /*
            system("cls");
            imprimeMatriz(m3, m, p);
            Sleep(500);
            */
        }
    }
}

void multiplaMatrices2(float *m1, float *m2, float *m3, int m, int n, int p){
    float *p1, *p2, *p3;
    p1 = m1;
    p2 = m2;
    p3 = m3;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < p; j++){
            float resultado = 0;
            p1 = m1 + n * i;
            p2 = m2 + p - j - 1;
            p3 = m3 + p * (i + 1) - j - 1;
            for (int k = 0; k < n; k++, p1++, p2+=p){
                resultado += (*p1) * (*p2);
            }
            *p3 = resultado;
            /*
            system("cls");
            imprimeMatriz(m3, m, p);
            Sleep(500);
            */
        }
    }
}

void multiplaMatrices3(float *m1, float *m2, float *m3, int m, int n, int p){
    float *p1, *p2, *p3;
    p1 = m1;
    p2 = m2;
    p3 = m3;

    for (int i = 0; i < p; i++){
        p3 = m3 + i;
        for (int j = 0; j < m; j++, p3+=p){
            float resultado = 0;
            p1 = m1 + n * j;
            p2 = m2 + i;
            for (int k = 0; k < n; k++, p1++, p2+=p){
                resultado += (*p1) * (*p2);
            }
            *p3 = resultado;
            /*
            system("cls");
            imprimeMatriz(m3, m, p);
            Sleep(500);
            */
        }
    }
}


void matrizPorVector(float *m1, float *v1, float *resul, int m, int n){
    multiplaMatrices(m1, v1, resul, m, n, 1);
}

void leeMatrices(float *&m1, float *&m2, int &m, int &n, int &p){
    float *ptr1, *ptr2;
    char nombreArchivo[100];
    ifstream archivo;

    cout << "Introduce el nombre del archivo donde est\xA0n guardadas las matrices a operar" << endl;
    cout << "(Recuerda agregar la extensi\xA2n del archivo): ";
    cin.getline(nombreArchivo, 100);

    archivo.open(nombreArchivo);

    if (!archivo){
        cout << "Error en la lectura del archivo" << endl;
        archivo.close();
        return;
    }

    archivo >> m;

    if (!archivo){
        cout << "\nError en la captura del archivo" << endl;
        cout << "Cerrando archivo" << endl;
        archivo.close();
        system("pause");
        return;
    }

    archivo >> n;

    if (!archivo){
        cout << "\nError en la captura del archivo" << endl;
        cout << "Cerrando archivo" << endl;
        archivo.close();
        system("pause");
        return;
    }

    archivo >> p;

    if (!archivo){
        cout << "\nError en la captura del archivo" << endl;
        cout << "Cerrando archivo" << endl;
        archivo.close();
        system("pause");
        return;
    }

    m1 = creaMatriz(m, n);
    m2 = creaMatriz(n, p);

    ptr1 = m1;
    ptr2 = m2;

    try {
        for (int i = 0; i < m * n; i++, ptr1++){
            float aux;
            archivo >> aux;
            *ptr1 = aux;
        }

        for (int i = 0; i < m * n; i++, ptr2++){
            float aux;
            archivo >> aux;
            *ptr2 = aux;
        }
    } catch (exception e){
        cout << "Ocurri\xA2 un error en la captura de los valores" << endl;
        destruyeMatriz(m1);
        destruyeMatriz(m2);
        archivo.close();
        return;
    }
    archivo.close();

}

void leeMatrizVector(float *&m1, float *&v, int &m, int &n){
    float *ptr1, *ptr2;
    char nombreArchivo[100];
    ifstream archivo;

    cout << "Introduce el nombre del archivo donde est\xA0n guardados la matriz y vector a operar" << endl;
    cout << "(Recuerda agregar la extensi\xA2n del archivo): ";
    cin.getline(nombreArchivo, 100);

    archivo.open(nombreArchivo);

    if (!archivo){
        cout << "Error en la lectura del archivo" << endl;
        archivo.close();
        return;
    }

    archivo >> m;

    if (!archivo){
        cout << "\nError en la captura del archivo" << endl;
        cout << "Cerrando archivo" << endl;
        archivo.close();
        system("pause");
        return;
    }

    archivo >> n;

    if (!archivo){
        cout << "\nError en la captura del archivo" << endl;
        cout << "Cerrando archivo" << endl;
        archivo.close();
        system("pause");
        return;
    }

    m1 = creaMatriz(m, n);
    v = creaVector(n);

    ptr1 = m1;
    ptr2 = v;

    try {
        for (int i = 0; i < m * n; i++, ptr1++){
            float aux;
            archivo >> aux;
            *ptr1 = aux;
        }
        for (int i = 0; i < n; i++, ptr2++){
            float aux;
            archivo >> aux;
            *ptr2 = aux;
        }
    } catch (exception e){
        cout << "Ocurri\xA2 un error en la captura de los valores" << endl;
        destruyeMatriz(m1);
        destruyeMatriz(v);
        archivo.close();
        return;
    }
    archivo.close();

}

void leeMatriz(float *&m1, int &m, int &n){
    float *ptr1;
    char nombreArchivo[100];
    ifstream archivo;

    cout << "Introduce el nombre del archivo donde est\xA0 guardada a matriz" << endl;
    cout << "(Recuerda agregar la extensi\xA2n del archivo): ";
    cin.getline(nombreArchivo, 100);

    archivo.open(nombreArchivo);

    if (!archivo){
        cout << "Error en la lectura del archivo" << endl;
        archivo.close();
        return;
    }

    archivo >> m;

    if (!archivo){
        cout << "\nError en la captura del archivo" << endl;
        cout << "Cerrando archivo" << endl;
        archivo.close();
        system("pause");
        return;
    }

    archivo >> n;

    if (!archivo){
        cout << "\nError en la captura del archivo" << endl;
        cout << "Cerrando archivo" << endl;
        archivo.close();
        system("pause");
        return;
    }

    m1 = creaMatriz(m, n);

    ptr1 = m1;

    try {
        for (int i = 0; i < m * n; i++, ptr1++){
            float aux;
            archivo >> aux;
            *ptr1 = aux;
        }
    } catch (exception e){
            cout << "Ocurri\xA2 un error en la captura de los valores" << endl;
            destruyeMatriz(m1);
            archivo.close();
            return;
    }
    archivo.close();
}

void guardaMatriz(float *m1, int m, int n){
    ofstream archivo;
    char nombreArchivo[100];
    float *ptr;
    ptr = m1;

    cout << "Introduce el nombre del archivo a guardar" << endl;
    cout << "(Recuerda agregar la extensi\xA2n del archivo): ";
    cin.getline(nombreArchivo, 100);

    archivo.open(nombreArchivo);
    archivo << m << "\t" << n << endl;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++, ptr++){
            archivo << *ptr << "\t";
        }
        archivo << endl;
    }

    archivo.close();

}

void guardaVector(float *v, int n){
    guardaMatriz(v, n, 1);
}

float hacerUnoSD(float *p, int n){
    float *p1;
    p1 = p;
    float valor = *p1;
    for (int i = 0; i < n; i++, p1++){
        *p1 = *p1 / valor;
    }
    return valor;
}

float hacerCeroSD(float *p, float *q, int n){
    float *p1, *q1;
    float valor;
    p1 = p;
    q1 = q;
    valor = *q1;

    for (int i = 0; i < n; i++, p1++, q1++){
        *q1 = *q1 - (valor) * (*p1);
    }
    return valor;
}

void hacerCeroAfectaVector(float *v, int vPiv, int vCam, float valor){
    float *v1, *v2;
    v1 = v + vPiv;
    v2 = v + vCam;

    *v2 = *v2 - (*v1 * valor);
}


bool pivotajeParcialSD(float *m, float *p, float *v, int n, int r){
    float *p1, *q1;
    float mayor = *p;
    int indice = 0;
    p1 = p + r;

    for (int i = 0; i < n; i++, p1 += r){
        if (abs(*p1) > abs(mayor)){
            mayor = *p1;
            indice = i + 1;
        }
    }

    if (mayor != 0){
        permutaComponentesVector(v, v + indice);
        permutaRenglonesMatriz(p, p + indice * r, r);
        return true;
    } else {
        return false;
    }
}


void permutaRenglonesMatriz(float *p, float *q, int n){
    float *p1, *q1;
    p1 = p;
    q1 = q;
    for (int i = 0; i < n; i++, p1++, q1++){
        float aux;
        aux = *p1;
        *p1 = *q1;
        *q1 = aux;
    }
}

void permutaComponentesVector(float *v1, float *v2){
    permutaRenglonesMatriz(v1, v2, 1);
}

void reduceSD(float *p, int n, float *v){
    float *p1, *q1, *v1;
    p1 = p;
    v1 = v;

    for (int i = 0; i < n; i++, p1+= n + 1){
        q1 = p1 + n;
        if (pivotajeParcialSD(p, p1, v1 + i, n - i - 1, n)){
            float valor = hacerUnoSD(p1, n - i);
            hacerUnoAfectaVector(v1, i, valor);
            for (int j = 0; j < n - i - 1; j++, q1 += n){
                valor = hacerCeroSD(p1, q1, n - i);
                hacerCeroAfectaVector(v1, i, i + j + 1, valor);
            }
        } else {
            cout << "La matriz es singular y no se puede reducir" << endl;
            return;
        }
    }
}

void hacerUnoAfectaVector(float *v, int n, float valor){
    float *v1;
    v1 = v;
    v1 += n;
    *v1 = *v1 / valor;
}


void resolverSD(float *m1, float *v1, int n){
    float *p1, *q1, valor;

    for (int i = 0; i < n - 1; i++){
        valor = *(v1 + (n - 1 - i));
        q1 = v1;
        p1 = m1 + (n - 1 - i);

        for (int j = 0; j < n - 1 - i; j++, p1 += n, q1++){
            *q1 = *q1 - valor * (*p1);
        }
    }
}

void permutaRenglonesMatriz(float *m1, int n, int r1, int r2){
    float *p1, *p2;

    p1 = m1 + r1 * n;
    p2 = m1 + r2 * n;

    for (int i = 0; i < n; i++, p1++, p2++){
        float aux;
        aux = *p1;
        *p1 = *p2;
        *p2 = aux;
    }
}

void permutaComponentesVector(float *v, int c1, int c2){
    permutaRenglonesMatriz(v, 1, c1, c2);
}

float hacerUnoSI(float *p, int n){
    float *p1;
    p1 = p;
    float valor = *p1;
    for (int i = 0; i < n; i++, p1--){
        *p1 = *p1 / valor;
    }
    return valor;
}

float hacerCeroSI(float *p, float *q, int n){
    float *p1, *q1;
    float valor;
    p1 = p;
    q1 = q;
    valor = *q1;

    for (int i = 0; i < n; i++, p1--, q1--){
        *q1 = *q1 - (valor) * (*p1);
    }
    return valor;
}


void resolverSI(float *m1, float *v1, int n){
    float *p1, *q1, valor;

    for (int i = 0; i < n - 1; i++){
        valor = *(v1 + (n - 1 - i));
        q1 = v1;
        p1 = m1 + i;

        for (int j = 0; j < n - 1- i; j++, p1 += n, q1++){
            *q1 = *q1 - valor * (*p1);
        }
    }

    // Se resuelve de manera similar a la triangular derecha superior
    // pero al dar el vector al revés se utiliza un vector auxiliar para arreglar los valores

    q1 = v1 + n;
    float *aux, *r;
    aux = creaVector(n);
    r = aux;
    q1 = v1;
    for (int i = 0; i < n; i++, r++, q1++){
        *r = *q1;
    }
    r = aux;
    q1 = v1 + n - 1;

    for (int i = 0; i < n; i++, r++, q1--){
        *q1 = *r;
    }

    destruyeMatriz(aux);
}

bool pivotajeParcialSI(float *m, float *p, float *v, int n, int r){
    float *p1;
    float mayor = *p;
    int indice = 0;
    p1 = p + r;

    for (int i = 0; i < n; i++, p1 += r){
        if (abs(*p1) > abs(mayor)){
            mayor = *p1;
            indice = i + 1;
        }
    }

    if (mayor != 0){
        permutaComponentesVector(v, v + indice);
        permutaRenglonesMatriz(p, p + indice * r, r);
        return true;
    } else {
        return false;
    }
}


void reduceSI(float *p, int n, float *v){
    float *p1, *q1, *v1;
    p1 = p + n - 1; // Se coloca en el pivote
    v1 = v;


    for (int i = 0; i < n; i++, p1+= n - 1){
        q1 = p1 + n;
        if (pivotajeParcialSD(p, p1, v + i, n - i - 1, n)){
            imprimeMatriz(p, n, n);
            imprimeVector(v, n);
            float valor = hacerUnoSI(p1, n - i);
            hacerUnoAfectaVector(v1, i, valor);
            for (int j = 0; j < n - i - 1; j++, q1 += n){
                valor = hacerCeroSI(p1, q1, n - i);
                hacerCeroAfectaVector(v1, i, i + j + 1, valor);
            }
        } else {
            cout << "La matriz es singular y no se puede reducir" << endl;
            return;
        }
    }
}


bool pivotajeParcialID(float *m, float *p, float *v, int n, int r){
    float *p1;
    float mayor = *p;
    int indice = 0;
    p1 = p - r;

    for (int i = 0; i < n; i++, p1 -= r){
        if (abs(*p1) > abs(mayor)){
            mayor = *p1;
            indice = i + 1;
        }
    }

    if (mayor != 0){
        cout << *(p - indice * r) << endl;
        permutaComponentesVector(v, v - indice);
        permutaRenglonesMatriz(p, p - indice * r, n);
        return true;
    } else {
        return false;
    }
}

void reduceID(float *m1, int n, float *v){
    float *p1, *q1, *v1;

    p1 = m1 + n*(n - 1); // Se coloca en el pivote
    v1 = v;

    for (int i = 0; i < n; i++, p1-= n - 1){
        q1 = p1 - n;
        if (pivotajeParcialID(m1, p1, v + n - 1 - i, n - i - 1, n)){
            imprimeMatriz(m1, n, n);
            imprimeVector(v, n);
            float valor = hacerUnoSD(p1, n - i);
            hacerUnoAfectaVector(v1, n - i - 1, valor);
            for (int j = 0; j < n - i - 1; j++, q1 -= n){
                valor = hacerCeroSD(p1, q1, n - i);
                hacerCeroAfectaVector(v1, n - i - 1, n - i - j - 2, valor);
            }
        } else {
            cout << "La matriz es singular y no se puede reducir" << endl;
            return;
        }
    }
}


void resolverID(float *m1, float *v1, int n){
    float *p1, *q1, valor;

    for (int i = 0; i < n - 1; i++){
        valor = *(v1 + i);
        q1 = v1 + i + 1;
        p1 = m1 + n + (n - 1 - i) + i * n;

        for (int j = 0; j < n - 1 - i; j++, p1 += n, q1++){
            *q1 = *q1 - valor * (*p1);
        }
    }

    // Se resuelve de manera similar a la triangular derecha superior
    // pero al dar el vector al revés se utiliza un vector auxiliar para arreglar los valores

    q1 = v1 + n;
    float *aux, *r;
    aux = creaVector(n);
    r = aux;
    q1 = v1;
    for (int i = 0; i < n; i++, r++, q1++){
        *r = *q1;
    }
    r = aux;
    q1 = v1 + n - 1;

    for (int i = 0; i < n; i++, r++, q1--){
        *q1 = *r;
    }

    destruyeMatriz(aux);
}

bool pivotajeParcialII(float *m, float *p, float *v, int n, int r){
    float *p1;
    float mayor = *p;
    int indice = 0;
    p1 = p - r;

    for (int i = 0; i < n; i++, p1 -= r){
        if (abs(*p1) > abs(mayor)){
            mayor = *p1;
            indice = i + 1;
        }
    }

    if (mayor != 0){
        permutaComponentesVector(v, v - indice);
        permutaRenglonesMatriz(p, p - indice * r, n);
        return true;
    } else {
        return false;
    }
}

void reduceII(float *m1, int n, float *v){
    float *p1, *q1, *v1;

    p1 = m1 + n * n - 1; // Me coloco sobre el primer pivote
    v1 = v;

    for (int i = 0; i < n; i++, p1-= n + 1){
        if (pivotajeParcialII(m1, p1, v + n - 1 - i, n - i, n)){
            q1 = p1 - n;
            float valor = hacerUnoSI(p1, n - i);
            hacerUnoAfectaVector(v1, n - i - 1, valor);
            for (int j = 0; j < n - i - 1; j++, q1 -= n){
                valor = hacerCeroSI(p1, q1, n - i);
                hacerCeroAfectaVector(v1, n - i - 1, n - i - j - 2, valor);
            }
        }
    }
}

void resolverII(float *m1, float *v1, int n){
    float *p1, *q1, valor;

    for (int i = 0; i < n - 1; i++){
        valor = *(v1 + i);
        q1 = v1 + i + 1;
        p1 = m1 + (i + 1) * n + i;

        for (int j = 0; j < n - 1 - i; j++, p1 += n, q1++){
            *q1 = *q1 - valor * (*p1);
        }
    }
}

float* inversa(float *p, int n){
   float *p1, *q1, *r1, *r2, *r;
   r = identidad(n);

   p1 = p;
   r1 = r;

   // Se reduce a triangular superior derecha

   for (int i = 0; i < n; i++, p1+= n + 1, r1 += n){
        // Revisa que el pivote no sea 0, de serlo, comienza a buscar uno en los siguientes renglones
        if (*p1 == 0){
            int aux = i + 1;
            // Variable para ir contando el número de renglones
            while (*p1 == 0 && aux < n){
                permutaRenglonesMatriz(p, n, i, aux);
                permutaRenglonesMatriz(r, n, i, aux);
                aux++;
            }
            if (aux > n){
                // Si no encontró otro pivote, se sale de la función
                cout << "La matriz es singular y no tiene inversa" << endl << endl;
                return NULL;
            }
        }

        q1 = p1 + n;
        r2 = r1 + n;
        float valor = hacerUnoSD(p1, n - i);
        unoAfectaAumentada(r1, n, valor);
        for (int j = 0; j < n - i - 1; j++, q1 += n, r2 += n){
            valor = hacerCeroSD(p1, q1, n - i);
            ceroAfectaAumentada(r1, r2, n, valor);
        }
    }

    // Se reduce a triangular inferior izquierda

    p1 = p + n * n - 1; // Me coloco sobre el primer pivote
    r1 = r + n * (n - 1);

    for (int i = 0; i < n; i++, p1-= n + 1, r1 -= n){
        // Revisa que el pivote no sea 0, de serlo, comienza a buscar uno en los siguientes renglones
        if (*p1 == 0){
            int aux = i + 1;
            // Variable para ir contando el número de renglones
            while (*p1 == 0 && aux < n){
                permutaRenglonesMatriz(p, n, i, aux);
                permutaRenglonesMatriz(r, n, i, aux);
                aux++;
            }
            if (aux > n){
                // Si no encontró otro pivote, se sale de la función
                cout << "La matriz es singular y no tiene inversa" << endl << endl;
                return NULL;
            }
        }
        q1 = p1 - n;
        r2 = r1 - n;
        float valor;
        for (int j = 0; j < n - i - 1; j++, q1 -= n, r2 -= n){
            valor = *q1;
            *q1 = 0;
            ceroAfectaAumentada(r1, r2, n, valor);
        }
    }
    return r;
}

void ceroAfectaAumentada(float *p, float *q, int n, float valor){
    float *p1, *q1;
    p1 = p;
    q1 = q;

    for (int i = 0; i < n; i++, p++, q++){
        *q = *q - (valor) * (*p);
    }
}

void unoAfectaAumentada(float *m, int n, float valor){
    float *m1;
    m1 = m;

    for (int i = 0; i < n; i++, m1++){
        *m1 = *m1 / valor;
    }
}

float* identidad(int n){
    float *q, *q1;
    q = creaMatriz(n, n);
    q1 = q;
    for (int i = 0; i < n * n; i++, q1++){
        *q1 = 0;
    }
    q1 = q;
    for (int i = 0; i < n; i++, q1+= n + 1){
        *q1 = 1;
    }
    return q;
}
