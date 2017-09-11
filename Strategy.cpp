// Strategy.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Strategy.h"

#include <math.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

#define ATENUAR 0.5

// gameState
const long PLAY = 0;	// Partido
const long FREE_BALL = 1;
const long PLACE_KICK = 2;
const long PENALTY_KICK = 3;
const long FREE_KICK = 4;
const long GOAL_KICK = 5;

// whosBall
const long ANYONES_BALL = 0;
const long BLUE_BALL = 1;
const long YELLOW_BALL = 2;

// global variables -- Useful field positions ... maybe???
const double FTOP = 77.2392;
const double FBOT = 6.3730;
const double GTOPY = 49.6801;
const double GBOTY = 33.9320;
const double GRIGHT = 97.3632;
const double GLEFT = 2.8748;
const double FRIGHTX = 93.4259;
const double FLEFTX = 6.8118;

#define MaxVel	125

void PredictBall ( Environment *env );
void PlayNormal(Environment *env );
void Arquero( Robot *robot, Environment *env );
void Jugador( Robot *robot, Environment *env, bool masCerca );


extern "C" STRATEGY_API void Create ( Environment *env )
{	
	// allocate user data and assign to env->userData
	// eg. env->userData = ( void * ) new MyVariables ();
}

// --------------------------------------------------------------------------------------------

extern "C" STRATEGY_API void Destroy ( Environment *env )

{
	// free any user data created in Create ( Environment * )

	// eg. if ( env->userData != NULL ) delete ( MyVariables * ) env->userData;
}

// --------------------------------------------------------------------------------------------

extern "C" STRATEGY_API void Strategy ( Environment *env )
{
	PredictBall ( env );

	switch (env->gameState)
	{
	case PLAY:
		PlayNormal(env);
		break;
	case FREE_BALL:
		PlayNormal(env);
		break;
	case PLACE_KICK:
		PlayNormal(env);
		break;
	case PENALTY_KICK:
		switch (env->whosBall)
		{
		case ANYONES_BALL:
			PlayNormal(env);
			break;
		case BLUE_BALL:
			PlayNormal(env);
			break;
		case YELLOW_BALL:
			PlayNormal(env);
			break;
		}
		break;
	case FREE_KICK:
		switch (env->whosBall)
		{
		case ANYONES_BALL:
			PlayNormal(env);
			break;
		case BLUE_BALL:
			PlayNormal(env);
			break;
		case YELLOW_BALL:
			PlayNormal(env);
			break;
		}
		break;
	case GOAL_KICK:
		switch (env->whosBall)
		{
		case ANYONES_BALL:
			PlayNormal(env);
			break;
		case BLUE_BALL:
			PlayNormal(env);
			break;
		case YELLOW_BALL:
			PlayNormal(env);
			break;
		}
		break;
	}
	
	sprintf(myMessage, " ");
	env->display = myMessage; 

}



//------------------------------------------------------------------------------------------------

void PredictBall ( Environment *env )
{
	double dx = env->currentBall.pos.x - env->lastBall.pos.x;
	double dy = env->currentBall.pos.y - env->lastBall.pos.y;
	env->predictedBall.pos.x = env->currentBall.pos.x + dx;
	env->predictedBall.pos.y = env->currentBall.pos.y + dy;

}

//------------------------------------------------------------------------------------------------

double ObtenerAngulo( double x0, double y0, double xf, double yf )
{
	double dx, dy, r, alfa;

	dx = xf-x0;
	dy = yf-y0;

	if (dx == 0 && dy == 0)
		alfa = 0;
	else
	{
		if (dx == 0)
		{
			if (dy > 0)
				alfa = 90;
			else
				alfa = -90;
		}
		else
			if (dy == 0)
			{
				if (dx > 0)
					alfa = 0;
				else
					alfa = 180;
			}
			else
			{
				// dx y dy != 0
				if (dx > 0)
					r = atan(fabs(dy) / fabs(dx));
				else
					r = atan(fabs(dx) / fabs(dy));
				alfa = Rad2Deg(r);
				if(dx < 0)
					alfa += 90;
				if (dy < 0)
					alfa *= -1;
			}
	}

	return alfa;
}


// =====================================================================
// J U G A D A S   E S P E C I A L E S		//K27
// =====================================================================

void PlayNormal( Environment *env )
{
	int masCerca,i;
	double distMin,dist;

	masCerca = 1;
	distMin = Distancia(env->home[1].pos.x,env->home[1].pos.y,env->predictedBall.pos.x,env->predictedBall.pos.y);
	for(i=2; i<5; i++)
	{
		dist = Distancia(env->home[i].pos.x,env->home[i].pos.y,env->predictedBall.pos.x,env->predictedBall.pos.y);
		if (dist < distMin)
		{
			masCerca = i;
			distMin = dist;
		}
	}

	Arquero( &env->home[0], env );
	Jugador( &env->home[1], env, (masCerca == 1) );
	Jugador( &env->home[2], env, (masCerca == 2) );
	Jugador( &env->home[3], env, (masCerca == 3) );
	Jugador( &env->home[4], env, (masCerca == 4) );
}



void Arquero( Robot *robot, Environment *env )
// Funcion principal de los movimientos del arquero
{
	double yball = env->predictedBall.pos.y;
	double r = robot->rotation;
	while (r > 180)
		r -= 360;
	while (r < -180)
		r += 360;
	

	if (fabs(fabs(r)-90) < 5)
	{
		// Estoy apuntando mas o menos hacia arriba o abajo => avanzo o retrocedo
		if (fabs(robot->pos.y - yball) < 1)
		{
			robot->velocityLeft = 0;
			robot->velocityRight = 0;
		}
		else
		{
			if (robot->pos.y < yball)
			{
				if (robot->pos.y > GTOPY)
				{
					robot->velocityLeft = 0;
					robot->velocityRight = 0;
				}
				else
				{
					if (r > 0)		// Mira hacia arriba
					{
						robot->velocityLeft = MaxVel;
						robot->velocityRight = MaxVel;
					}
					else
					{
						robot->velocityLeft = -MaxVel;
						robot->velocityRight = -MaxVel;
					}
				}
			}
			else
			{
				if (robot->pos.y < GBOTY)
				{
					robot->velocityLeft = 0;
					robot->velocityRight = 0;
				}
				else
				{
					if (r > 0)		// Mira hacia arriba
					{
						robot->velocityLeft = -MaxVel;
						robot->velocityRight = -MaxVel;
					}
					else
					{
						robot->velocityLeft = MaxVel;
						robot->velocityRight = MaxVel;
					}
				}
			}
		}
	}
	else
	{
		// Ajusto orientacion
		if (r > 0)   // Miro para arriba
		{
			robot->velocityLeft = -(90-r) * ATENUAR;
			robot->velocityRight = (90-r) * ATENUAR;
		}
		else
		{
			robot->velocityLeft = (r+90) * ATENUAR;
			robot->velocityRight = -(r+90) * ATENUAR;
		}
	}

}


void Jugador( Robot *robot, Environment *env, bool masCerca )
{
	double x, y;
	double vl, vr;
	double xo,yo;

	if (masCerca)
	{
		x = env->predictedBall.pos.x;
		y = env->predictedBall.pos.y;
		if ( y > FTOP - 2.5 ) 
			 y = FTOP - 2.5;
		if ( y < FBOT + 2.5 ) 
			 y = FBOT + 2.5;
		if ( x > FRIGHTX - 3 ) 
			 x = FRIGHTX - 3;
		if ( x < FLEFTX + 3 ) 
			 x = FLEFTX + 3;

		xo = robot->pos.x;
		yo = robot->pos.y;
		double r = robot->rotation;
		while (r > 180)
			r -= 360;
		while (r < -180)
			r += 360;

		double ang, angleDiff;

		ang = ObtenerAngulo(xo,yo,x,y);

		angleDiff = ang - r;
		// Normalizo a -180 a 180
		if (angleDiff > 180)
			angleDiff -= 360;
		if (angleDiff < -180)
			angleDiff += 360;

		if (fabs(angleDiff) < 15)
		{
			// Estoy apuntando mas o menos hacia la pelota => voy hacia adelante
			vl = MaxVel;
			vr = MaxVel;
		}
		else
		{
			// Ajusto orientacion
			vl = -angleDiff * ATENUAR;
			vr = angleDiff * ATENUAR;
		}
	}
	else
	{
		// Si no es el mas cercano se queda quieto
		vl = 0;
		vr = 0;
	}

	robot->velocityLeft = vl;
	robot->velocityRight = vr;

}
