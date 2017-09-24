#ifndef Strategy_H
#define Strategy_H

//********************** Libraries / Includes **********************
//==================================================================
#include <stdio.h>
#include <time.h>
#include "Const.h"
#include "Util.h"
#include <math.h>

//********************** Macros **********************
//====================================================
#ifdef STRATEGY_EXPORTS
#define STRATEGY_API __declspec(dllexport)
#else
#define STRATEGY_API __declspec(dllimport)
#endif
#define Distancia(x,y,xf,yf) ( sqrt((xf-x)*(xf-x) + (yf-y)*(yf-y)) )
#define RAD2DEG (180.0/PI)
#define DEG2RAD (PI/180.0)
#define Rad2Deg(a) ((double)a * RAD2DEG)
#define Deg2Rad(a) ((double)a * DEG2RAD)
#define ATENUAR 0.5
#define MaxVel	125

//********************** Global Variables **********************
//==============================================================
const long PLAYERS_PER_SIDE = 5;
char myMessage[200];

//********************** Structs Definition **********************
//================================================================
typedef struct
{
	double x, y, z;
} Vector3D; //Defino una estructura Vector 3D

typedef struct
{
	long left, right, top, bottom;
} Bounds; //Defino una estructura Limites con los 4 puntos de un rectangulo

typedef struct
{
	Vector3D pos;
	double rotation;
	double velocityLeft, velocityRight;
} Robot; //Defino una estructura Robot, que tiene un Vector de posicion, un angulo Rotacion que dice a donde esta apuntando el
         //robot en radianes, y la velocidad de ambas ruedas.

typedef struct
{
	Vector3D pos;
	double rotation;
} OpponentRobot; //Defino una estructura RobotOponente en donde defino la posicion y hacia a donde esta mirando en radianes

typedef struct
{
	Vector3D pos;
} Ball; //Defino una estructura Pelota que solo tiene un Vector de la posicion actual

typedef struct
{
	Vector3D mid, sup, inf, tope;
} Goal; //Defino una estructura Arco, que tiene los límites del arco.

typedef struct
{
	Robot home[PLAYERS_PER_SIDE];
	Ball currentBall, lastBall, predictedBall;
	Bounds fieldBounds, goalBounds;
	long gameState;
	long whosBall;
	OpponentRobot opponent[PLAYERS_PER_SIDE];
	void *userData;
	char *display;
} Environment; //Defino una estructura Ambiente, que tiene un vector de 5 Robots, tiene 3 Pelotas (con ultima posicion,
               //posicion actual, y posicion predicha), tipo del juego, quién tiene la pelota, un vector de 5 RobotOponentes,
               //datos del usuario y datos de la pantalla

typedef void (*MyStrategyProc)(Environment*);

//********************** User Function Prototypes **********************
//======================================================================
extern "C" STRATEGY_API void Create ( Environment *env );
extern "C" STRATEGY_API void Destroy ( Environment *env );
extern "C" STRATEGY_API void Strategy ( Environment *env ); 
void PredictBall ( Environment *env );
void PlayNormal(Environment *env );
void MoverJugadorHaciaPelota(Robot *robot, Environment *env);
void Arquero( Robot *robot, Environment *env );
void Jugador( Robot *robot, Environment *env, bool masCerca );
double Vel_Ball(Environment *env);
double ObtenerAngulo(double x0, double y0, double xf, double yf);

#endif // Strategy_H


