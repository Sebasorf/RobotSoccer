//********************** Libraries / Includes **********************
//==================================================================
#include "stdafx.h"
#include "Util.h"

//********************** User Functions Definitions **********************
//========================================================================
// Devuelve el ángulo a girar por un jugador para queda mirando a la posición xf yf
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

// Devuelve el angulo a partir de un punto inicial a uno final
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

// Calcula el ángulo que hay entre dos puntos. Version 2
double CalcularAngulo2Pts2(double x0, double y0, double xf, double yf) 
{
	double dAngulo;
	double x = xf - x0;
	double y = yf - y0;
	// Ángulo igual a 0.
	if (((x > 0.0) && (y == 0.0)) || ((x == 0.0) && (y == 0.0))) 
		dAngulo = 0.0;
	// Ángulo igual a 90.
	else if ((x == 0.0) && (y > 0.0)) 
		dAngulo = 90.0;
	// Ángulo igual a 180.
	else if ((x < 0.0) && (y == 0.0)) 
		dAngulo = 180.0;
	// Ángulo igual a 270.
	else if ((x == 0.0) && (y < 0.0)) 
		dAngulo = 270.0;
	// Otro valor del ángulo.
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

// Deveulve el ángulo en grados pasado como parámetro en radianes.
double Deg2Rad(double dAngGrados)
{
	return dAngGrados * (PI / 180.0);
}

// Deveulve el ángulo en radianes pasado como parámetro en grados.
double Rad2Deg(double dAngRad)
{
	return dAngRad * (180.0 / PI);
}

// Deveulve el ángulo en grados pasado como parámetro en radianes.Version 2
double Radianes_Grados(double Angulo_R){
	double grados = fabs (Angulo_R * 180 / PI);	
	return grados;
}

// Calcula la distancia entre dos puntos.
double Distancia(double x0,double y0,double xf,double yf) 
{
	double dist_x = xf - x0;;
	double dist_y = yf - y0;
	return sqrt(((dist_x) * (dist_x)) + ((dist_y) * (dist_y)));	
}

// Calcula la distancia entre dos puntos. Version 2
double Distancia_2Pts(double X1 ,double X2,double Y1, double Y2){
	double Op, Ady;
	Op = fabs(Y1 - Y2);
	Ady = fabs(X1 - X2);
	double Distancia = (sqrt((Ady * Ady) + (Op * Op)));	
	return Distancia;		
}

// Devuelve el menor de los dos valores pasados como parámetros.
double Menor(double a, double b)
{
	return a < b ? a : b;
}

// Devuelve el mayor de los dos valores pasados como parámetros.
double Mayor(double a, double b)
{
	return a > b ? a : b;
}

// Devuelve 0 si el número pasado como parámetro es 0, -1 si es negativo, y 1 si es positivo.
int Signo(double n)
{
	return (int)(n == 0 ? 0 : (n / fabs(n)));
}

// Devuelve el número de zona en donde se encuentra el punto pasado como parámetro.
int Zona (double x, double y) 
{
	if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 1;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 2;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) &&
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 3;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 4;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 5;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > LIMITE_INFERIOR_CAMPO) && (y < AREA_GRANDE_LINEA_INFERIOR))
			return 6;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) &&
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 7;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 8;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 9;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 10;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 11;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > AREA_GRANDE_LINEA_INFERIOR) && (y < AREA_CHICA_LINEA_INFERIOR))
			return 12;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 13;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 14;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 15;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 16;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 17;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > AREA_CHICA_LINEA_INFERIOR) && (y < ARCO_LINEA_INFERIOR))
			return 18;
	else if ((x > ARCO_LINEA_DE_ATRAS_IZQUIERDA) && (x < LIMITE_IZQUIERDO_CAMPO) &&
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 19;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 20;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 21;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 22;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 23;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 24;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 25;
	else if ((x > LIMITE_DERECHO_CAMPO) && (x < ARCO_LINEA_DE_ATRAS_DERECHA) && 
		(y > ARCO_LINEA_INFERIOR) && (y < MITAD_DE_CANCHA_EN_Y))
			return 26;
	else if ((x > ARCO_LINEA_DE_ATRAS_IZQUIERDA) && (x < LIMITE_IZQUIERDO_CAMPO) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 27;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 28;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 29;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 30;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) &&
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 31;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 32;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) &&
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 33;
	else if ((x > LIMITE_DERECHO_CAMPO) && (x < ARCO_LINEA_DE_ATRAS_DERECHA) && 
		(y > MITAD_DE_CANCHA_EN_Y) && (y < ARCO_LINEA_SUPERIOR))
			return 34;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 35;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 36;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 37;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 38;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 39;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > ARCO_LINEA_SUPERIOR) && (y < AREA_CHICA_LINEA_SUPERIOR))
			return 40;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 41;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 42;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 43;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 44;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) &&
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 45;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > AREA_CHICA_LINEA_SUPERIOR) && (y < AREA_GRANDE_LINEA_SUPERIOR))
			return 46;
	else if ((x > LIMITE_IZQUIERDO_CAMPO) && (x < AREA_CHICA_LINEA_IZQUIERDA) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 47;
	else if ((x > AREA_CHICA_LINEA_IZQUIERDA) && (x < AREA_GRANDE_LINEA_IZQUIERDA) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 48;
	else if ((x > AREA_GRANDE_LINEA_IZQUIERDA) && (x < MITAD_DE_CANCHA_EN_X) &&
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 49;
	else if ((x > MITAD_DE_CANCHA_EN_X) && (x < AREA_GRANDE_LINEA_DERECHA) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 50;
	else if ((x > AREA_GRANDE_LINEA_DERECHA) && (x < AREA_CHICA_LINEA_DERECHA) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 51;
	else if ((x > AREA_CHICA_LINEA_DERECHA) && (x < LIMITE_DERECHO_CAMPO) && 
		(y > AREA_GRANDE_LINEA_SUPERIOR) && (y < LIMITE_SUPERIOR_CAMPO))
			return 52;
	else
		return 0;
}

// Falta entender que hace
double Angulo_2Pts(double Distancia, double Op){
	fabs(Op);
	double Angulo = asin(fabs(Op / Distancia));	
	return Angulo;
}

//Falta entender que hace
double Angulo_girar(double Angulo, double Op, double Ady, double rotation){
	if ((Ady > 0) && (Op > 0)){
		Angulo = Angulo;
	}
	else if ((Ady > 0) && (Op < 0)){
		Angulo = 0 - Angulo;
	}
	else if ((Ady < 0) && (Op > 0)){
		Angulo = 180 - Angulo;
	}
	else if ((Ady < 0) && (Op < 0)){
		Angulo = -180 + Angulo;
	}
	Angulo = Angulo - rotation;
	if(Angulo > 180)
	{
	    Angulo = Angulo - 360; 
	}
	if(Angulo < -180)
	{
		Angulo = 360 + Angulo;
	}
	return Angulo;
}

// Falta entender que hace
double NormalizarAngulo(double angulo)
{
	while (angulo >  360) angulo -= 360;
	while (angulo < -360) angulo += 360;
	if (angulo < 0) angulo += 360;
	return angulo;
}

// Falta entender que hace
int Velocidad(double Distancia){
	int Velocidad;
	if (Distancia > 13) {
			Velocidad = 100; // 100;
	}
	else if (Distancia > 10) {
		Velocidad = 80; // 80;
	}
	else if (Distancia > 7) {
		Velocidad = 70; // 70;
	}
	else if (Distancia > 6) {
		Velocidad = 50; // 50
	}		
	else if (Distancia > 1) {
		Velocidad = 30; //30;
	}/*
	else if (Distancia > 1) {
		Velocidad = 8;
	}
	else if (Distancia > 0.5) {
		Velocidad = 4;
	}*/
	else  {
		Velocidad = 5; // 0
	}
	return Velocidad;
}