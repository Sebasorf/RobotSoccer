#ifndef Strategy_H
#define Strategy_H

#ifdef STRATEGY_EXPORTS
#define STRATEGY_API __declspec(dllexport)
#else
#define STRATEGY_API __declspec(dllimport)
#endif

#include <string.h>
#include <stdio.h>
#include "Const.h"
#include "Util.h"

#define ATENUAR 0.5
#define MaxVel	125

//********************** Global Variables **********************
//==============================================================
const long PLAYERS_PER_SIDE = 5;
// global variables -- Useful field positions ... maybe???
const double FTOP = 77.2392;
const double FBOT = 6.3730;
const double GTOPY = 49.6801;
const double GBOTY = 33.9320;
const double GRIGHT = 97.3632;
const double GLEFT = 2.8748;
const double FRIGHTX = 93.4259;
const double FLEFTX = 6.8118;

//********************** Structs Definition **********************
//================================================================
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
	Robot home[PLAYERS_PER_SIDE];
	OpponentRobot opponent[PLAYERS_PER_SIDE];
	Ball currentBall, lastBall, predictedBall;
	Bounds fieldBounds, goalBounds;
	long gameState;
	long whosBall;
	void *userData;
} Environment;

//********************** User Function Prototypes **********************
//======================================================================
typedef void (*MyStrategyProc)(Environment*);
extern "C" STRATEGY_API void Create ( Environment *env ); // implement this function to allocate user data and assign to Environment->userData
extern "C" STRATEGY_API void Strategy ( Environment *env );
extern "C" STRATEGY_API void Destroy ( Environment *env ); // implement this function to free user data created in  Create (Environment*)

#endif // Strategy_H