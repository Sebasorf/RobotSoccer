#ifndef UTIL_H
#define UTIL_H

//#include "Strategy.h"

// Devuelve el �ngulo a girar por un jugador para queda mirando a la posici�n xf yf.
double CalcularAnguloAGirar2(double x0,double y0, double xf, double yf, double rr);

double CalcularAngulo2Pts(double xo, double yo, double xf, double yf);

// Calcula el �ngulo que hay entre dos puntos.
double CalcularAngulo2Pts2(double x0, double y0, double xf, double yf);

// Deveulve el �ngulo en radianes pasado como par�metro en grados.
double Rad2Deg(double dAngRad);





#endif // UTIL_H