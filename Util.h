#ifndef UTIL_H
#define UTIL_H

//include "Strategy.h"

// Devuelve el �ngulo a girar por un jugador para queda mirando a la posici�n xf yf.
double CalcularAnguloAGirar2(double x0,double y0, double xf, double yf, double rr);

double CalcularAngulo2Pts(double xo, double yo, double xf, double yf);

// Deveulve el �ngulo en grados pasado como par�metro en radianes.
double Deg2Rad(double dAngGrados);

// Deveulve el �ngulo en radianes pasado como par�metro en grados.
double Rad2Deg(double dAngRad);

// Calcula la distancia entre dos puntos.
double Distancia(double x0,double y0,double xf,double yf);

// Devuelve el menor de los dos valores pasados como par�metros.
double Menor(double a, double b);

// Devuelve el mayor de los dos valores pasados como par�metros.
double Mayor(double a, double b);

// Devuelve 0 si el n�mero pasado como par�metro es 0, -1 si es negativo, y 1 si es positivo.
int Signo(double n);

// Calcula el �ngulo que hay entre dos puntos.
double CalcularAngulo2Pts2(double x0, double y0, double xf, double yf);

// Devuelve el n�mero de zona en donde se encuentra el punto pasado como par�metro.
int Zona (double x, double y);

double Distancia_2Pts(double X1 ,double X2,double Y1, double Y2);

double Angulo_2Pts(double Distancia, double Op);

double Radianes_Grados(double Angulo_R);

double Angulo_girar(double Angulo, double Op, double Ady, double rotation);

double NormalizarAngulo(double angulo);

int Velocidad(double Distancia);



#endif // UTIL_H