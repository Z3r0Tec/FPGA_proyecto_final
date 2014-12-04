Proyecto Final de Prototipado con FPGAs

Alumnos:
	Luis Guillermo Marin Blanco
	Daniel Vargas Campos
	Josue Garro Nunez

Estructura de directorios:
	System: contiene el codigo necesario para generar el sistema en quartus.
		Software: contiene los archivos fuente de la aplicacion Pong.
			  main.c: archivo principal de la aplicacion.
			  nios_gfx_api.c: implementacion de las funciones graficas y de teclado.
			  nios_gfx_api.h: declaracion de las funciones graficas.

Known issues:
Efecto de "flickering" en la pantalla ya que por limitacion de memoria no fue posible utilizar doble buffering.