README.TXT del equipo básico provisto para CAFR2003, CAFR2004 y CAFR2005

CONTENIDO

  1.- Generalidades.
  2.- Características.
  3.- Notas aclaratorias.
  4.- Funciones principales de la DLL.
  5.- Contenido del archivo ReadMe.txt provisto por el paquete de instalación del simulador.

-------------------------------------------------------------------------------

1.- Generalidades.

 - El equipo básico de fútbol simulado es provisto en código para Visual C++. Fue desarrollado con la versión 6.0 del ambiente del Visual Studio.

 - El desarrollo fue realizado a partir de los programas fuentes provistos con el paquete de instalación del software de simulación en su versión 7 (1.4)

 - El proyecto genera el archivo BASICO.DLL al ser compilado. Este nombre puede ser modificado en las opciones del proyecto.

-------------------------------------------------------------------------------------------------
 
2.- Características.

El equipo desarrollado posee las siguientes características:

 - Define una estructura para definir la jugada en base al estado de juego. En todos los casos invoca al proceso de juego normal.
 
 - Envía al jugador más cercano a la pelota hacia ella. El resto, salvo el arquero, permanece inmóvil.
 
 - Tiene definidos dos roles: arquero y jugador. Cada uno esta implementado en un procedimiento con nombre análogo.
 
 - Arquero: se desplaza sobre su eje X en el rango Y definido por los límites del área (constantes GTOPY y GBOTY). Ajusta su orientación para mantenerse a +-90 grados, es decir apuntando hacia arriba o abajo.
 
 - Jugador: implementa laacción de ir a la pelota si su orientación coincide aproximadamente con la orientación de la pelota. En caso contrario, gira para quedar bien orientado.
 
 - Utiliza predicción a un ciclo de simulación para la posición de la pelota.
 
-------------------------------------------------------------------------------------------------

3.- Notas aclaratorias.

 - No se recomienda utilizar las variables fieldBounds y goalBounds de la estructura Environment. Estas variables no tienen los valores correctos. Para esto se definen constantes con las dimensiones del campo de juego y sus partes (FTOP, FBOT, GTOPY, GBOTY, GRIGHT, GLEFT, FRIGHTX, FLEFTX).
 
 - El estado de juego se mantiene hasta tanto sea modificado por el menú o se produzca un gol. Es decir, si se selecciona FREE BALL, este estado permanecerá aún despues de que la pelota se ponga en movimiento. El estado PLAY (0) fue agregado para contemplar los casos en que el simulador no establece ningún estado de juego.

 - En el proyecto que provee el paquete de instalación del simulador hay un error en la estructura Environment que establece la interfase con el simulador. El error consiste en la posición, dentro de la estructura, del vector 'opponent', el cual ha sido corregido en esta versión. 
 
-------------------------------------------------------------------------------------------------
 
4.- Funciones principales de la DLL.

El simulador interactúa con la dll mediante 3 funciones:

 - Create: esta función se invoca cuando se carga la dll en el simulador.
 
 - Strategy: Esta función es invocada por el simulador 60 veces por segundo mientras se desarrolla el juego. Cuando se está operando el simulador (utilizando los menúes) la dll no es invocada.
 
 - Destroy: Invocada al descargar la dll.
   
-------------------------------------------------------------------------------------------------
   
5.- Contenido del archivo ReadMe.txt provisto por el paquete de instalación del simulador.

 - The Strategy project is based on the Win32 DLL wizard option in VC++.

 - It contains a sample strategy and can be compiled down and placed in the Director folder to be used.

 - Developers can use this project as a starting point for developing a DLL-based strategy. 

 - The project creates a Strategy.dll file, however, any file name should be acceptable as long as the Director program allows users to select their own strategy DLLs.

 - The Strategy.h file contains the function prototypes which will be exported from the DLL: Create, Strategy, and Destroy. And also the Environment structure.

 - The Environment structure is passed into the Strategy function and is used to access information about the robots, ball and field. It can also be used to set the velocities of the robots.

 - Global data is not possible in the DLL as both robot teams may wish to use the same DLL file. So a user structure can be allocated and assigned to the userData field in Environment.h.

 - Because user data only needs to be allocated once it can be done in the Create function which is called once when the Xtra is loaded.

 - The user data can be freed in the Destroy function which is called when the Xtra is unloaded.

-------------------------------------------------------------------------------------------------
 