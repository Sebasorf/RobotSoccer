#ifndef Strategy_H
#define Strategy_H

#include <stdio.h>
#include <time.h>
#include "Const.h"
#include "Util.h"

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STRATEGY_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STRATEGY_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef STRATEGY_EXPORTS
#define STRATEGY_API __declspec(dllexport)
#else
#define STRATEGY_API __declspec(dllimport)
#endif

const long PLAYERS_PER_SIDE = 5;

#define Distancia(x,y,xf,yf) ( sqrt((xf-x)*(xf-x) + (yf-y)*(yf-y)) )
//const double PI = 3.1415923;
#define RAD2DEG (180.0/PI)
#define DEG2RAD (PI/180.0)
#define Rad2Deg(a) ((double)a * RAD2DEG)
#define Deg2Rad(a) ((double)a * DEG2RAD)


typedef struct
{
	double x, y, z;
} Vector3D;

typedef struct
{
	long left, right, top, bottom;
} Bounds;

typedef struct
{
	Vector3D pos;
	double rotation;
	double velocityLeft, velocityRight;
} Robot;

typedef struct
{
	Vector3D pos;
	double rotation;
} OpponentRobot;

typedef struct
{
	Vector3D pos;
} Ball;

typedef struct
{
	Vector3D mid, sup, inf, tope;
} Goal;

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

} Environment;

double Vel_Ball(Environment *env);

typedef void (*MyStrategyProc)(Environment*);

char myMessage[200]; //big enough???

extern "C" STRATEGY_API void Create ( Environment *env ); // implement this function to allocate user data and assign to Environment->userData
extern "C" STRATEGY_API void Strategy ( Environment *env );
extern "C" STRATEGY_API void Destroy ( Environment *env ); // implement this function to free user data created in  Create (Environment*)


#endif // Strategy_H


