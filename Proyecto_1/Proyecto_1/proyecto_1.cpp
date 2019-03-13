//Semestre 2019 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//
#include <stdlib.h>
#include <stdio.h>
#include "Main.h"
#include <GL/glui.h>

int ventana_d;
double x0;
double vent_y0;
double x1; 
double vent_y1;
double x2;
double y2;
double x3;
double y3;
double dimension_x_pos;
double dimension_y_pos;
double dimension_x_neg;
double dimension_y_neg;

double l_x0;
double l_y0;
double l_x1;
double l_y1;

int code0[3];
int code1[3];


void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo
	
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpiamos pantalla y Depth Buffer	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();									// Reinicializamos la actual matriz Modelview

	//Poner aqui codigo ha dibujar

	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(x0, vent_y0);
		glVertex2f(x1, vent_y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(l_x0, l_y0);
		glVertex2f(l_x1, l_y1);

	glEnd();


											

	glFlush();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
	if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Ortogonal

	glOrtho(dimension_x_neg, dimension_x_pos, dimension_y_neg, dimension_y_pos,-0.1,2);
	

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();									
}

// Termina la ejecucion del programa cuando se presiona ESC
void keyboard(unsigned char key, int x, int y)
{
	 switch (key) 
	 {
		case 27: exit(0);
				 break;
	 }
	  glutPostRedisplay();
}    

int ventana_dibujo(int argc, char** argv)
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE); // Display Mode (Clores RGB y alpha | Buffer Sencillo )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 2"); // Nombre de la Ventana
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutMainLoop();          // 

	return 0;
}


void generar_vert_ventana(float x_ventana_izq, float y_ventana_izq,	float l_ventana, float h_ventana, float lx0, float lx1, float ly0, float ly1)
{
	x0 = x_ventana_izq;
	vent_y0 = y_ventana_izq;
	x1 = x0;
	vent_y1 = y_ventana_izq + h_ventana;
	x2 = x_ventana_izq + l_ventana;
	y2 = vent_y1;
	x3 = x2;
	y3 = vent_y0;

	l_x0 = lx0;
	l_x1 = lx1;
	l_y0 = ly0;
	l_y1 = ly1;

}

void dimensionar()
{   
	if (l_x0 >= l_x1)	dimension_x_pos = l_x0;
	else  dimension_x_pos = l_x1;
	if (x2 >= dimension_x_pos) dimension_x_pos = x2;
	dimension_x_pos = dimension_x_pos + 10;

	if (l_x0 <= l_x1)	dimension_x_neg = l_x0;
	else  dimension_x_neg = l_x1;
	if (x0 <= dimension_x_neg) dimension_x_neg = x0;
	dimension_x_neg = dimension_x_neg - 10;

	if (l_y0 >= l_y1)	dimension_y_pos = l_y0;
	else  dimension_y_pos = l_y1;
	if (y2 >= dimension_y_pos) dimension_y_pos = y2;
	dimension_y_pos = dimension_y_pos + 10;

	if (l_y0 <= l_y1)	dimension_y_neg = l_y0;
	else  dimension_y_neg = l_y1;
	if (vent_y0 <= dimension_y_neg) dimension_y_neg = vent_y0;
	dimension_y_neg = dimension_y_neg - 10;
		
}

void dar_codigo() 
{
	if (l_x0 < x0)
		code0[2] = 1;
	else code0[2] = 0;
	if (l_x0 > x2)
		code0[3] = 1;
	else code0[3] = 0;

	if (l_y0 < vent_y0)
		code0[0] = 1;
	else code0[0] = 0;
	if (l_y0 > vent_y1)
		code0[1] = 1;
	else code0[1] = 0;

	if (l_x1 < x0)
		code1[2] = 1;
	else code1[2] = 0;
	if (l_x1 > x2)
		code1[3] = 1;
	else code1[3] = 0;

	if (l_y1 < vent_y0)
		code1[0] = 1;
	else code1[0] = 0;
	if (l_y1 > vent_y1)
		code1[1] = 1;
	else code1[1] = 0;

}

void recortar()
{
	double vsup;
	double vinf;
	double vder;
	double vizq;

	double xsup;
	double ysup;

	double yinf;
	double xinf;

	double xder;
	double yder;

	double xizq;
	double yizq;


	vsup = (vent_y1 - l_y0) / (l_y1 - l_y0);
	if ((vsup >= 0) && (vsup <= 1))
	{
		xsup = l_x0 + vsup * (l_x1 - l_x0);
		printf("\n \n Recorte de punto superior ( %f, %f) \n ", xsup, vent_y1);
	}
	else { printf("\n \n No se obtiene punto en la parte superior\n "); }

	vinf = (vent_y0 - l_y0) / (l_y1 - l_y0);
	if ((vinf >= 0) && (vinf <= 1))
	{
		xinf = l_x0 + vinf * (l_x1 - l_x0);
		printf("\n \n Recorte de punto inferior ( %f, %f) \n ", xinf, vent_y0);
	}
	else { printf("\n \n No se obtiene punto en la parte inferior\n "); }

	vder = (x0 - l_x0) / (l_x1 - l_x0);
	if ((vder >= 0) && (vder <= 1))
	{
		yder = l_y0 + vder * (l_y1 - l_y0);
		printf("\n \n Recorte de punto izquierdo ( %f, %f) \n ", x0, yder);
	}
	else { printf("\n \n No se obtiene punto en la parte izquierdo\n "); }

	vizq = (x2 - l_x0) / (l_x1 - l_x0);
	if ((vizq >= 0) && (vizq <= 1))
	{
		yizq = l_y0 + vizq * (l_y1 - l_y0);
		printf("\n \n Recorte de punto derecho ( %f, %f) \n ", x2, yizq);
	}
	else { printf("\n \n No se obtiene punto en la parte derecho\n "); }
}


int desicion()
{	
	int result = 0;
	int result2 = 0;
	int cuenta = 0;
	dar_codigo();

	for (int n = 0; n < 4; n++)
	{
		result = code0[n] + code1[n];
		result2 =  code0[n] * code1[n];
		
		if (result != 0) 
		{
			
			if (result2 == 0)
			{
				cuenta += 1;
				if (cuenta == 3)
				{
					recortar();
					return 0;
				}
			}
			else 
			{ 
				printf("Se descarta la linea");
				return 0;
			}
		}
		else { cuenta += 1; }
	}

	printf("Se dibuja completa la linea");
	return 0;
}




int main ( int argc, char** argv )   // Main Function
{
	int logro = 0;
	float x_ventana_izq,
		  y_ventana_izq,
		l_ventana,
		h_ventana,
		lx0,
		lx1,
		ly0,
		ly1;
	
	printf("Ingresa el valor x0 de la ventana \n");
	scanf("%f", &x_ventana_izq );
	
	printf("Ingresa el valor y0 de la ventana \n");
	scanf("%f", &y_ventana_izq);
	
	
	printf("Ingresa el valor de l de la ventana \n");
	scanf("%f", &l_ventana);
	
	
	printf("Ingresa el valor de h de la ventana \n");
	scanf("%f", &h_ventana);
	

	printf("Ingresa el valor de x0 de la linea \n");
	scanf("%f", &lx0);
	

	printf("Ingresa el valor de y0 de la lina \n");
	scanf("%f", &ly0);
	

	printf("Ingresa el valor de x1 de la linea \n");
	scanf("%f", &lx1);
	

	printf("Ingresa el valor de y1 de la lina \n");
	scanf("%f", &ly1);
	

	generar_vert_ventana( x_ventana_izq,  y_ventana_izq,  l_ventana,  h_ventana, lx0, lx1, ly0, ly1);

	dimensionar();

	int fin = desicion();

	
	
	logro =	ventana_dibujo( argc, argv);

  return 0;
}

