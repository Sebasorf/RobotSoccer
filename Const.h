// Const.h
// Constantes utilizadas en el equipo.

#ifndef CONST_H
#define CONST_H


// Color del equipo.
const int CE_AZUL = 1;
const int CE_AMARILLO = 2;
const int COLOR_EQUIPO = CE_AZUL;


// Número PI.
const double PI = 3.1415;


// Estado del juego. Campo gameState.
const long PLAY = 0;	
const long FREE_BALL = 1;
const long PLACE_KICK = 2;
const long PENALTY_KICK = 3;
const long FREE_KICK = 4;
const long GOAL_KICK = 5;

// A quien pertenece la pelota. Campo whosBall.
const long ANYONES_BALL = 0;
const long BLUE_BALL = 1;
const long YELLOW_BALL = 2;


// ---------------------------------------------------------------
// Campo de juego.
const double LIMITE_SUPERIOR_CAMPO = 77.2392;
const double LIMITE_INFERIOR_CAMPO = 6.3730;
const double LIMITE_IZQUIERDO_CAMPO = 7.6;
const double LIMITE_DERECHO_CAMPO = 93.6959;
const double MITAD_DE_CANCHA_EN_X = 50.0801;
const double MITAD_DE_CANCHA_EN_Y = 41.6435;
const double ARCO_LINEA_DE_ATRAS_IZQUIERDA = 2.8748;
const double ARCO_LINEA_DE_ATRAS_DERECHA = 97.3632;
const double ARCO_LINEA_SUPERIOR = 49.6801;
const double ARCO_LINEA_INFERIOR = 33.9320;
const double AREA_GRANDE_LINEA_SUPERIOR = 57.1861;
const double AREA_GRANDE_LINEA_INFERIOR = 26.2866;
const double AREA_GRANDE_LINEA_IZQUIERDA = 20.5913;
const double AREA_GRANDE_LINEA_DERECHA = 79.6464;
const double AREA_CHICA_LINEA_SUPERIOR = 51.1918;
const double AREA_CHICA_LINEA_INFERIOR = 32.2420;
const double AREA_CHICA_LINEA_IZQUIERDA = 13.4368;
const double AREA_CHICA_LINEA_DERECHA = 86.7426;
const double MITAD_DE_CANCHA_DERECHA_EN_X = 64.8633; 
const double MITAD_DE_CANCHA_IZQUIERDA_EN_X = 35.3357; 
const double LATERAL_LINEA_SUPERIOR = 68.3317;
const double LATERAL_LINEA_INFERIOR = 15.2805;


//-----------------------------------------------------------------
// Lineas de Juego.
const double LINEA_ARQUERO_AMARILLO = 9.7448;
const double LINEA_DEFENSA_AMARILLO = 9.7448;
const double LINEA_DEFENSOR1_AMARILLO = 29.4172;
const double LINEA_DEFENSOR2_AMARILLO = 40.5994;
const double LINEA_ARQUERO_AZUL = 92.48;
const double LINEA_DEFENSA_AZUL = 90.7663;
const double LINEA_DEFENSOR1_AZUL = 71.5443;
const double LINEA_DEFENSOR2_AZUL = 62.3739;

const double LINEA_ATAQUE_AZUL = 14.7448;

//-----------------------------------------------------------------
// Puntos de penal.
const double PUNTO_PENAL_AZUL_EN_X = 78.6464;
const double PUNTO_PENAL_AZUL_EN_Y = 41.6435;
const double PUNTO_PENAL_AMARILLO_EN_X = 21.5913;
const double PUNTO_PENAL_AMARILLO_EN_Y = 41.6435;


//-----------------------------------------------------------------
// Distancias.

// Distancia de la línea de la zona de riesgo a la línea de juego del arco.
const double DISTANCIA_PARA_LINEA_ZONA_RIESGO = 1.0;

// Distancia que determina si un juegador esta lejos de la pelota.
const double DISTANCIA_LEJOS_PELOTA = 25.0;

// Distancia para saber si un robot esta cerca de un punto.
const double DISTANCIA_CERCA = 5.0;

// Distancia para saber si la pelota esta quieta o no.
const double DISTANCIA_QUIETA = 3.0;

// Distancia para saber si la pelota esta en contacto.
const double DISTANCIA_A_PELOTA = 5.0 ;

// Distancia máxima en el eje y para considerarse que se esta detrás de un punto.
const double DISTANCIA_Y_ATRAS_PELOTA = 2.5;

// Distancia para saber si el robot esta más o menos a la altura de la pelota.
const double DISTANCIA_MEDIO_ROBOT = 1.0;

// Distancia a partir de la cual se considera que un robot esta sobre una línea
// de juego.
const double DISTANCIA_LINEAS_JUEGO = 1.4;

const double DISTANCIA_LINEAS_JUEGO2 = 3.5;

// Distancia para saber si un robot esta marcado o no.
const double DISTANCIA_MARCA = 8.0;


//-------------------------------------------------------------------
// Angulos.

// Indica cuando puede un jugador estar desviado de su objetivo para que
// se considere que aún sigue mirándolo.
const double DESVIO_ORIENTACION = 5.0;


//---------------------------------------------------------------------
// Defensor.

const double LINEA_ZONA_PELIGRO_DEF_AZUL_X = 57.71;
const double LINEA_ZONA_PELIGRO_DEF_AZUL_Y_SUP = 60.01;
const double LINEA_ZONA_PELIGRO_DEF_AZUL_Y_INF = 25.29;

const double LINEA_ZONA_PELIGRO_DEF_AZUL_X2 = 85.71;
//----------------------------------------------------------------------
// Pesquero.

const double PUNTO_PENAL_AMARILLO_X = 22.45;
const double PUNTO_PENAL_AMARILLO_Y = 41.91;

const double LINEA_GIRO_DERECHA = 15;
const double LINEA_GIRO_IZQUIERDA = 7;
const double LINEA_GIRO_SUPERIOR = 51;
const double LINEA_GIRO_INFERIOR = 32;

//-----------------------------------------------------------------------
// Para acomodar al arquero más cerca de los palos.
const double PUNTO_SUPERIOR_ARQUERO = 47.86;
const double PUNTO_INFERIOR_ARQUERO = 35.65; 
const double LINEA_X_ARQUERO = 92.75;


//-----------------------------------------------------------------------
// Para el defensor atacante.

const double LINEA_DEFENSOR_ATACANTE_AZUL = 18.43;

#endif // CONST_H