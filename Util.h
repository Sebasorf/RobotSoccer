#ifndef UTIL_H
#define UTIL_H

//#include "Strategy.h"

// Devuelve el ángulo a girar por un jugador para queda mirando a la posición xf yf.
double CalcularAnguloAGirar2(double x0,double y0, double xf, double yf, double rr);

double CalcularAngulo2Pts(double xo, double yo, double xf, double yf);

// Calcula el ángulo que hay entre dos puntos.
double CalcularAngulo2Pts2(double x0, double y0, double xf, double yf);

// Deveulve el ángulo en radianes pasado como parámetro en grados.
double Rad2Deg(double dAngRad);





#endif // UTIL_H