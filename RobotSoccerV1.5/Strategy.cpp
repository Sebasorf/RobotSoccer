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


//********************** Global Variables **********************
//==============================================================
char myMessage[200]; 

//********************** User Function Prototypes **********************
//======================================================================
void FreeNormalPlay(Environment *env);
bool PelotaEnZonaDeDelanteros(Ball *currentBall);
bool PelotaEnZonaDeDefensores(Ball *currentBall);
void Despejar(Robot *jugador, Ball *currentBall);
bool PelotaEnPosicionYriesgosa(double posicionJugador, Ball *currentBall);

void PredictBall ( Environment *env );
void Goalie1 ( Robot *robot, Environment *env );
void NearBound2 ( Robot *robot, double vl, double vr, Environment *env );
void Attack2 ( Robot *robot, Environment *env );
void Defend ( Robot *robot, Environment *env, double low, double high );
void MoonAttack (Robot *robot, Environment *env );
void MoonFollowOpponent (  Robot *robot, OpponentRobot *opponent );
void Velocity ( Robot *robot, int vl, int vr );
void Angle ( Robot *robot, int desired_angle);
void Position( Robot *robot, double x, double y );
void PlayNormal(Environment *env );;
void Arquero( Robot *robot, Environment *env );
void Jugador( Robot *robot, Environment *env, bool masCerca );
double Vel_Ball(Environment *env);
double ObtenerAngulo(double x0, double y0, double xf, double yf);

//********************** Strategies Actions ****************************
//======================================================================
extern "C" STRATEGY_API void Create ( Environment *env )
{
}

extern "C" STRATEGY_API void Destroy ( Environment *env )
{
}

extern "C" STRATEGY_API void Strategy ( Environment *env )
{
	PredictBall(env);
	int testInt = 100;
	switch (env->gameState)
	{
		case 0: // default
			FreeNormalPlay(env);
			//Goalie1 ( &env->home [0], env );
			break;
		case FREE_BALL:
			FreeNormalPlay(env);
			//Goalie1 ( &env->home [0], env );
			break;
		case PLACE_KICK:
			FreeNormalPlay(env);
			break;			
		case PENALTY_KICK:
			switch (env->whosBall)
			{
			case ANYONES_BALL:
				FreeNormalPlay(env);;
				break;
			case BLUE_BALL:
				FreeNormalPlay(env);
				break;
			case YELLOW_BALL:
				FreeNormalPlay(env);
				break;
			}
			break;
		case FREE_KICK:
			FreeNormalPlay(env);
			/*FILE * debugfile; 
			int k = 100;
			debugfile = fopen("debugfile.txt","a"); 
			for (k=0;k<=4;k++) 
				fprintf(debugfile, "robot: %d x: %f y: %f z: %f \n",
					k, env->opponent[k].pos.x, env->opponent[k].pos.y, 
					env->opponent[k].pos.z); 
			
			fclose(debugfile); */
			break;
		case GOAL_KICK:
			FreeNormalPlay(env);
			break;
  }
}

//********************** User Functions Definitions **********************
//========================================================================
void FreeNormalPlay(Environment *env)
{
	double vl, vr;
	vl = MaxVel;
    vr = MaxVel;
	Ball *pelotaActual = &env->currentBall;
	Ball *pelotaFutura = &env->predictedBall;
	Robot *arquero = &env->home[0];
	Robot *defensorIzquierdo = &env->home[1];
	Robot *defensorDerecho = &env->home[2];
	Robot *delanteroDerecho= &env->home[3];
	Robot *delanteroIzquierdo = &env->home[4];
	Goalie1 (arquero, env);

	if( PelotaEnZonaDeDelanteros(pelotaFutura) )
	{
		Despejar(delanteroIzquierdo, pelotaFutura);
		Despejar(delanteroDerecho, pelotaFutura);
		if( pelotaFutura->pos.x < 40)
		{
			Position(defensorIzquierdo, 72, 27);
			Position(defensorDerecho, 72, 55);
		}
	}
	if( PelotaEnZonaDeDefensores(pelotaFutura) )
	{
		Despejar(defensorIzquierdo, pelotaFutura);
		Despejar(defensorDerecho, pelotaFutura);
		if( pelotaFutura->pos.x > 65)
		{
			Position(delanteroIzquierdo, 35, 27);
			Position(delanteroDerecho, 35, 55);
		}
	}
}

bool PelotaEnZonaDeDelanteros(Ball *currentBall)
{
	// Para el equipo azul: el limite de delanteros va de 65 hasta 0. Siendo 0 el limite de la pared del amarillo, y 65 el limite para no chocar con la defensa azul. Es decir 65 limite derecho de zona, 0 limite izquierdo de zona
	double limite_delanteros_x = 65;
	return (currentBall->pos.x<=limite_delanteros_x) ? true:false;
}

bool PelotaEnZonaDeDefensores(Ball *currentBall)
{
	// Para el equipo azul: el limite de defensores va de 40 en x hasta el valor infinito, siendo 40 el limite yendo para el equipo amarillo. Es decir, 40 limite izquierdo de zona, infinito limite derecho de zona
	double limite_defensores_x = 40;
	return (currentBall->pos.x>=limite_defensores_x) ? true:false;
}

void Despejar(Robot *jugador, Ball *currentBall)
{
	//Si, la posicion de los jugadores apunta a su propio arco (para gol en contra)
	if(currentBall->pos.x > jugador->pos.x)
	{
		//Si la pelota se encuentra a una distancia Y respecto al jugador, riesgosa por gol en contra
		if( PelotaEnPosicionYriesgosa( jugador->pos.y, currentBall ) )
		{
			//Si el jugador se encuentra en una posicion mayor en Y, voy por arriba
			if( jugador->pos.y > currentBall->pos.y)
			{
				Position(jugador, currentBall->pos.x + 5, currentBall->pos.y + 5);
			}
			else
			{
				Position(jugador, currentBall->pos.x + 5, currentBall->pos.y);
			}
		}
		else
		{
			//Se podría sacar esta condicion con IF y else
			if( jugador->pos.y > currentBall->pos.y)
			{
				Position(jugador, currentBall->pos.x + 5, currentBall->pos.y + 5);
			}
			else
			{
				Position(jugador, currentBall->pos.x + 5, currentBall->pos.y);
			}
		}
	}
	else
	{
		// Quiere decir que los jugadores apuntan la pelota hacia el arco enemigo
		Position(jugador, currentBall->pos.x, currentBall->pos.y);
	}	

}

bool PelotaEnPosicionYriesgosa(double posicionJugador, Ball *currentBall)
{
	//Define si el robot esta en la misma posicion Y para no hacer gol en contra
	double posicionYaceptable_min = currentBall->pos.y - 6;
	double posicionYaceptable_max = currentBall->pos.y + 6;
	return (posicionJugador > posicionYaceptable_min && posicionJugador < posicionYaceptable_max) ? true:false;
}


//****************************************************************************************
//************************ Funciones que vienen de caja **********************************
//****************************************************************************************
void MoonAttack ( Robot *robot, Environment *env )
{
	//Velocity (robot, 127, 127);
	//Angle (robot, 45);
	Position(robot, env->predictedBall.pos.x, env->predictedBall.pos.y);
	// Position(robot, 0.0, 0.0);
}

void MoonFollowOpponent ( Robot *robot, OpponentRobot *opponent )
{
	Position(robot, opponent->pos.x, opponent->pos.y);
}

void Velocity ( Robot *robot, int vl, int vr )
{
	robot->velocityLeft = vl;
	robot->velocityRight = vr;
}

void Angle ( Robot *robot, int desired_angle)
{
	int theta_e, vl, vr;
	theta_e = desired_angle - (int)robot->rotation;
	while (theta_e > 180) theta_e -= 360;
	while (theta_e < -180) theta_e += 360;
	if (theta_e < -90) theta_e += 180;
	else if (theta_e > 90) theta_e -= 180;
	if (abs(theta_e) > 50) 
	{
		vl = (int)(-9./90.0 * (double) theta_e);
		vr = (int)(9./90.0 * (double)theta_e);
	}
	else if (abs(theta_e) > 20)
	{
		vl = (int)(-11.0/90.0 * (double)theta_e);
		vr = (int)(11.0/90.0 * (double)theta_e);
	}
	Velocity (robot, vl, vr);
}

void Position( Robot *robot, double x, double y )
{
	int desired_angle = 0, theta_e = 0, d_angle = 0, vl, vr, vc = 70;
	double dx, dy, d_e, Ka = 10.0/90.0;
	dx = x - robot->pos.x;
	dy = y - robot->pos.y;
	d_e = sqrt(dx * dx + dy * dy);
	if (dx == 0 && dy == 0)
		desired_angle = 90;
	else
		desired_angle = (int)(180. / PI * atan2((double)(dy), (double)(dx)));
	theta_e = desired_angle - (int)robot->rotation;
	while (theta_e > 180) theta_e -= 360;
	while (theta_e < -180) theta_e += 360;
	if (d_e > 100.) 
		Ka = 17. / 90.;
	else if (d_e > 50)
		Ka = 19. / 90.;
	else if (d_e > 30)
		Ka = 21. / 90.;
	else if (d_e > 20)
		Ka = 23. / 90.;
	else 
		Ka = 25. / 90.;
	if (theta_e > 95 || theta_e < -95)
	{
		theta_e += 180;	
		if (theta_e > 180) 
			theta_e -= 360;
		if (theta_e > 80)
			theta_e = 80;
		if (theta_e < -80)
			theta_e = -80;
		if (d_e < 5.0 && abs(theta_e) < 40)
			Ka = 0.1;
		vr = (int)(-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);
		vl = (int)(-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);
	}
	else if (theta_e < 85 && theta_e > -85)
	{
		if (d_e < 5.0 && abs(theta_e) < 40)
			Ka = 0.1;
		vr = (int)( vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);
		vl = (int)( vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);
	}
	else
	{
		vr = (int)(+.17 * theta_e);
		vl = (int)(-.17 * theta_e);
	}
	Velocity(robot, vl, vr);
}

void PredictBall ( Environment *env )
{
	double dx = env->currentBall.pos.x - env->lastBall.pos.x;
	double dy = env->currentBall.pos.y - env->lastBall.pos.y;
	env->predictedBall.pos.x = env->currentBall.pos.x + dx;
	env->predictedBall.pos.y = env->currentBall.pos.y + dy;
}

void Goalie1 ( Robot *robot, Environment *env )
{
	double velocityLeft = 0, velocityRight = 0;
	double Tx = env->goalBounds.right - env->currentBall.pos.x;
	double Ty = env->fieldBounds.top - env->currentBall.pos.y;
	double Ax = env->goalBounds.right - robot->pos.x;
	double Ay = env->fieldBounds.top - robot->pos.y;
	if ( Ay > Ty + 0.9 && Ay > 27 )
	{
		velocityLeft = -100;
		velocityRight = -100;
	}
	if ( Ay > Ty - 0.9 && Ay < 43 )
	{
		velocityLeft = 100;
		velocityRight = 100;
	}
	if ( Ay < 27 )
	{
		velocityLeft = 100;
		velocityRight = 100;
	}
	if ( Ay > 43 )
	{
		velocityLeft = -100;
		velocityRight = -100;
	}
	double Tr = robot->rotation;
	if ( Tr < 0.001 )
		Tr = Tr + 360;
	if ( Tr > 360.001 )
		Tr = Tr - 360;
	if ( Tr > 270.5 )
		velocityRight = velocityRight + fabs ( Tr - 270 );
	else if ( Tr < 269.5 )
		velocityLeft = velocityLeft + fabs ( Tr - 270 );
	robot->velocityLeft = velocityLeft;
	robot->velocityRight = velocityRight;
}

void Attack2 ( Robot *robot, Environment *env )
{
	Vector3D t = env->currentBall.pos;
	double r = robot->rotation;
	if ( r < 0 ) r += 360;
	if ( r > 360 ) r -= 360;
	double vl = 0, vr = 0;
	if ( t.y > env->fieldBounds.top - 2.5 ) t.y = env->fieldBounds.top - 2.5;
	if ( t.y < env->fieldBounds.bottom + 2.5 ) t.y = env->fieldBounds.bottom + 2.5;
	if ( t.x > env->fieldBounds.right - 3 ) t.x = env->fieldBounds.right - 3;
	if ( t.x < env->fieldBounds.left + 3 ) t.x = env->fieldBounds.left + 3;
	double dx = robot->pos.x - t.x;
	double dy = robot->pos.y - t.y;
	double dxAdjusted = dx;
	double angleToPoint = 0;
	if ( fabs ( robot->pos.y - t.y ) > 7 || t.x > robot->pos.x )
		dxAdjusted -= 5;

	if ( dxAdjusted == 0 )
	{
		if ( dy > 0 )
			angleToPoint = 270;
		else
			angleToPoint = 90;
	}
	else if ( dy == 0 )
	{
		if ( dxAdjusted > 0 )
			angleToPoint = 360;
		else
			angleToPoint = 180;	
	}
	else
		angleToPoint = atan ( fabs ( dy / dx ) ) * 180.0 / PI;

	if ( dxAdjusted > 0 )
	{
		if ( dy > 0 )
			angleToPoint -= 180;
		else if ( dy < 0 )
			angleToPoint = 180 - angleToPoint;
	}
	if ( dxAdjusted < 0 )
	{
		if ( dy > 0 )
			angleToPoint = - angleToPoint;
		else if ( dy < 0 )
			angleToPoint = 90 - angleToPoint;
	}
	if ( angleToPoint < 0 ) angleToPoint = angleToPoint + 360;
	if ( angleToPoint > 360 ) angleToPoint = angleToPoint - 360;
	if ( angleToPoint > 360 ) angleToPoint = angleToPoint - 360;
	double c = r;
	double angleDiff = fabs ( r - angleToPoint );
	if ( angleDiff < 40 )
	{
		vl = 100;
		vr = 100;
		if ( c > angleToPoint )
			vl -= 10;
		if ( c < angleToPoint )
			vr -= 10;
	}
	else
	{
		if ( r > angleToPoint )
		{
			if ( angleDiff > 180 )
				vl += 360 - angleDiff;
			else
				vr += angleDiff;
		}
		if ( r < angleToPoint )
		{
			if ( angleDiff > 180 )
				vr += 360 - angleDiff;
			else
				vl += angleDiff;
		}
	}
	NearBound2 ( robot, vl, vr, env );
}

void NearBound2 ( Robot *robot, double vl, double vr, Environment *env )
{
	//Vector3D t = env->currentBall.pos;
	Vector3D a = robot->pos;
	double r = robot->rotation;
	if ( a.y > env->fieldBounds.top - 15 && r > 45 && r < 130 )
	{
		if ( vl > 0 )
			vl /= 3;
		if ( vr > 0 )
			vr /= 3;
	}
	if ( a.y < env->fieldBounds.bottom + 15 && r < -45 && r > -130 )
	{
		if ( vl > 0 ) vl /= 3;
		if ( vr > 0 ) vr /= 3;
	}
	if ( a.x > env->fieldBounds.right - 10 )
	{
		if ( vl > 0 )
			vl /= 2;
		if ( vr > 0 )
			vr /= 2;
	}
	if ( a.x < env->fieldBounds.left + 10 )
	{
		if ( vl > 0 )
			vl /= 2;
		if ( vr > 0 )
			vr /= 2;
	}
	robot->velocityLeft = vl;
	robot->velocityRight = vr;
}

void Defend ( Robot *robot, Environment *env, double low, double high )
{
	double vl = 0, vr = 0;
	Vector3D z = env->currentBall.pos;
	double Tx = env->goalBounds.right - z.x;
	double Ty = env->fieldBounds.top - z.y;
	Vector3D a = robot->pos;
	a.x = env->goalBounds.right - a.x;
	a.y = env->fieldBounds.top - a.y;

	if ( a.y > Ty + 0.9 && a.y > low )
	{
		vl = -100;
		vr = -100;
	}
	if ( a.y < Ty - 0.9 && a.y < high )
	{
		vl = 100;
		vr = 100;
	}
	if ( a.y < low )
	{
		vl = 100;
		vr = 100;
	}
	if ( a.y > high )
	{
		vl = -100;
		vr = -100;
	}
	double Tr = robot->rotation;
	if ( Tr < 0.001 )
		Tr += 360;
	if ( Tr > 360.001 )
		Tr -= 360;
	if ( Tr > 270.5 )
		vr += fabs ( Tr - 270 );
	else if ( Tr < 269.5 )
		vl += fabs ( Tr - 270 );
	NearBound2 ( robot, vl ,vr, env );
}

void PlayNormal(Environment *env)
{
	double vl, vr;
	double limite_delanteros_x = 60;
	vl = MaxVel;
    vr = MaxVel;
	Ball *pelota = &env->lastBall;
	Robot *arquero = &env->home[0];
	Robot *defensorIzquierdo = &env->home[1];
	Robot *defensorDerecho = &env->home[2];
	Robot *delanteroDerecho= &env->home[3];
	Robot *delanteroIzquierdo = &env->home[4];
	//Dado el robot delanteroDerecho, quieror ir a limite_delanteros_x
	if(pelota->pos.x >= limite_delanteros_x)
	{
		delanteroDerecho->velocityLeft=vl;
		delanteroDerecho->velocityRight=vr;
	}
	else
	{
		delanteroDerecho->velocityLeft=-127;
		delanteroDerecho->velocityRight=-127;
	}
}

// Funcion principal de los movimientos del arquero
void Arquero( Robot *robot, Environment *env )
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
				if (robot->pos.y > ARCO_LINEA_SUPERIOR)
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
				if (robot->pos.y < ARCO_LINEA_INFERIOR)
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

void MoverJugadorHaciaPelota(Robot *robot, Environment *env)
{

}

// Funcion principal que define el movimiento de un jugador
void Jugador( Robot *robot, Environment *env, bool masCerca )
{
	double x, y;
	double vl, vr;
	double xo,yo;
	if (masCerca)
	{
		x = env->predictedBall.pos.x;
		y = env->predictedBall.pos.y;
		if ( y > LIMITE_SUPERIOR_CAMPO - 2.5 ) 
			 y = LIMITE_SUPERIOR_CAMPO - 2.5;
		if ( y < LIMITE_INFERIOR_CAMPO + 2.5 ) 
			 y = LIMITE_INFERIOR_CAMPO + 2.5;
		if ( x > LIMITE_DERECHO_CAMPO - 3 ) 
			 x = LIMITE_DERECHO_CAMPO - 3;
		if ( x < LIMITE_IZQUIERDO_CAMPO + 3 ) 
			 x = LIMITE_IZQUIERDO_CAMPO + 3;
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

// Velocidad de la pelota
double Vel_Ball(Environment *env){
	double Y2 = env->currentBall.pos.y;
	double X2 = env->currentBall.pos.x;
	double X1 = env->lastBall.pos.x;
	double Y1 = env->lastBall.pos.y;
	double Distancia = Distancia_2Pts(X1 ,X2, Y1, Y2);
	double Vel_Pel = fabs(Distancia / 0.01); //Fabs()= returns absolute value;
	return Vel_Pel;
}

// Devuelve el angulo de un punto inicial a un punto final
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
