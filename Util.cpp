#include "stdafx.h"
#include "Util.h"

#include <math.h>
#include <fstream.h>

#include "Const.h"

double CalcularAnguloAGirar2(double x0,double y0, double xf, double yf, double rr) 
{
	double dAnguloEntre2Puntos = CalcularAngulo2Pts(x0, y0, xf, yf);
	double dAnguloAGirar = dAnguloEntre2Puntos - rr;
	if (dAnguloAGirar > 180.0)
		dAnguloAGirar = -360.0 + dAnguloAGirar;
	if (dAnguloAGirar < -180.0)
		dAnguloAGirar = 360.0 + dAnguloAGirar;
	return dAnguloAGirar;
}

double CalcularAngulo2Pts(double xo, double yo, double xf, double yf)
{
	double dx, dy, alfa, constAngle = 0;
	dx = xf - xo;
	dy = yf - yo;

	if (dx == 0 && dy == 0) {
		alfa = 0;
	}
	else if (dx == 0) {
		if (dy > 0)
			alfa = 90;
		else
			alfa = 270;
	}
	else if (dy == 0) {
		if (dx > 0)
			alfa = 0;
		else
			alfa = 180;
	}
	else {
		alfa = atan(fabs(dy) / fabs(dx));
		alfa = Rad2Deg(alfa);	
		if ((dx > 0) && (dy > 0))
			alfa = alfa;
		else if ((dx < 0) && (dy > 0))
			alfa = 180 - alfa;
		else if ((dx < 0) && (dy < 0))
			alfa = 180 + alfa;
		else
			alfa = 360 - alfa;
	}
	return alfa;
}

// Deveulve el �ngulo en radianes pasado como par�metro en grados.
double Rad2Deg(double dAngRad)
{
	return dAngRad * (180.0 / PI);
}




// Calcula el �ngulo que hay entre dos puntos.
double CalcularAngulo2Pts2(double x0, double y0, double xf, double yf) 
{
	double dAngulo;
	double x = xf - x0;
	double y = yf - y0;
	// �ngulo igual a 0.
	if (((x > 0.0) && (y == 0.0)) || ((x == 0.0) && (y == 0.0))) 
		dAngulo = 0.0;
	// �ngulo igual a 90.
	else if ((x == 0.0) && (y > 0.0)) 
		dAngulo = 90.0;
	// �ngulo igual a 180.
	else if ((x < 0.0) && (y == 0.0)) 
		dAngulo = 180.0;
	// �ngulo igual a 270.
	else if ((x == 0.0) && (y < 0.0)) 
		dAngulo = 270.0;
	// Otro valor del �ngulo.
	else {
		double dAngRad = atan(fabs(y) / fabs(x));
		double dAngGrados = ((dAngRad * 180.0) / PI);
		if ((x < 0.0) && (y > 0.0)) 
			dAngulo = 180.0 - dAngGrados;
		else if ((x < 0.0) && (y < 0.0)) 
			dAngulo = 180.0 + dAngGrados;
		else if ((x > 0.0) && (y < 0.0))
			dAngulo = 360.0 - dAngGrados;	
		else
			dAngulo = dAngGrados;
	}
	return dAngulo;
}