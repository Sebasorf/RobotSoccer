#ifndef UTIL_H
#define UTIL_H

//********************** Libraries / Includes **********************
//==================================================================
//include "Strategy.h"
#include <math.h>
#include <fstream.h>
#include "Const.h"

//********************** User Function Prototypes **********************
//======================================================================
double CalcularAnguloAGirar2(double x0,double y0, double xf, double yf, double rr); // Devuelve el �ngulo a girar por un jugador para queda mirando a la posici�n xf yf
double CalcularAngulo2Pts(double xo, double yo, double xf, double yf) ;// Devuelve el angulo a partir de un punto inicial a uno final
double CalcularAngulo2Pts2(double x0, double y0, double xf, double yf); // Calcula el �ngulo que hay entre dos puntos. Version 2
double Deg2Rad(double dAngGrados); // Deveulve el �ngulo en grados pasado como par�metro en radianes.
double Rad2Deg(double dAngRad); // Deveulve el �ngulo en radianes pasado como par�metro en grados.
double Radianes_Grados(double Angulo_R); // Deveulve el �ngulo en grados pasado como par�metro en radianes. Version 2
double Distancia(double x0,double y0,double xf,double yf); // Calcula la distancia entre dos puntos.
double Distancia_2Pts(double X1 ,double X2,double Y1, double Y2); // Calcula la distancia entre dos puntos. Version 2
double Menor(double a, double b); // Devuelve el menor de los dos valores pasados como par�metros.
double Mayor(double a, double b); // Devuelve el mayor de los dos valores pasados como par�metros.
int Signo(double n); // Devuelve 0 si el n�mero pasado como par�metro es 0, -1 si es negativo, y 1 si es positivo.
int Zona (double x, double y); // Devuelve el n�mero de zona en donde se encuentra el punto pasado como par�metro.
double Angulo_2Pts(double Distancia, double Op); // Falta entender que hace
double Angulo_girar(double Angulo, double Op, double Ady, double rotation); // Falta entender que hace
double NormalizarAngulo(double angulo); // Falta entender que hace
int Velocidad(double Distancia); // Falta entender que hace


#endif // UTIL_H