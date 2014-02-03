#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <stdlib.h>
#include <math.h>   //to use sin and cos

#include "vec3f.cpp"
#include "imageloader.cpp"

		

#define GL_PI 3.1415f

#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif

using namespace std;

GLuint textureID;

GLfloat xRot = 0.0f , yRot = -0.0f , zoom_out = -400.0f;
bool* keySpecialStates = new bool[256];

GLboolean pan =0 , rot = 1;

GLint modifier;

bool* keyNormalStates = new bool[256];

GLfloat xInitial=0 , yInitial=0 , xFinal=0 , yFinal=0 , x_trans=0.0f , y_trans=0.0f , light_y = 50.0f;

GLfloat angle = 0.0f , x = 450.0f , y = 0.0f  , z = 0.0f , lx = 0.0f , lz = -1.0f , ly=0;  
GLfloat region = 1 , check2 = 1 , check1 = 1, check3 = 1 , check4 = 1 , yCheck = 1.0f ;
GLfloat xRandom = 200.0f , yRandom = 1.0f , zRandom = 200.0f  ; 
GLfloat speed = 1.0f;
GLint t = 0.0;

GLuint texture1 , texture2 , texture3 , texture4 , texture5;
GLfloat red = 0.98 , blue = 0.5 , green = 0.0f;

GLfloat height = 0.0f;


void keyOperations(void)
{
	if(keySpecialStates[GLUT_KEY_LEFT] == 1)
	{
		printf("left \n");
		angle = angle - 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
	}
	if(keySpecialStates[GLUT_KEY_RIGHT] ==1)
	{
		printf("right \n");
		angle = angle + 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
	}
	if(keySpecialStates[GLUT_KEY_UP] ==1)
	{
		printf("up \n");
		
		y=y+75;

		if( y >=75 )
		{
			y = 75;
		}
	}
	if(keySpecialStates[GLUT_KEY_DOWN] ==1)
	{
		printf("down \n");
		
		y=y-75;

		if( y <=-75 )
		{
			y = -75;
		}
	}
	
	if(keyNormalStates['o'] == 1)
	{
		printf("o \n");
		light_y = light_y + 10;
	}

	if(keyNormalStates['l'] == 1)
	{
		printf("l \n");
		light_y = light_y - 10;
	}
}


GLuint loadTexture(Image *image)
{
	GLuint textureId;
	glGenTextures(1 , &textureId);

	glBindTexture(GL_TEXTURE_2D , textureId);
	glTexImage2D(GL_TEXTURE_2D , 0 , GL_RGB , image->width , image->height , 0 , GL_RGB , GL_UNSIGNED_BYTE , image->pixels);

	return textureId;
}



void movePlayer( void )
{
	
	//defining motion in the two wings
	
	if( z <= 400 && z >=-400 )
	{
		if(x > 0)
		{
			x = 450;
			z = z-20*speed;
			lx=0.0f;
			lz=-1.0f;
			region =1;
		}


		if(x < 0)
		{
			x = -450;	
			z = z+20*speed;
			lx=0.0f;
			lz=1.0f;
			region = 3;
		}
	}

	if( x <=400 && x >= -400 )
	{
		if(z > 0)
		{
			z = 450;
			x=x+20*speed;			
			lx = 1.0f;
			lz = 0.0f;
			region  = 4;
		}

		if(z < 0 )
		{
			z=-450;
			x=x-20*speed;			
			lx = -1.0f;
			lz = 0.0f;
			printf("turn complete \t");
			region = 2;
		}
		
	}

	//defining turns
	

	if ( x ==450 && z < -400 )
	{
			x = 400;
			z = -450;
			lx = -1;
			lz = 0;
			
	}

	if ( z == -450 && x < -400 )
	{
			x = -450;
			z = -400;
			lx = 0;
			lz = 1;
			
	

	}

	if ( x == -450 && z > 400 )
	{
			x = -400;
			z = 450;
			lx = 1;
			lz = 0;
			
	

	}

	if ( z == 450 && x > 400 )
	{
			x = 450;
			z = 400;
			lx = 0;
			lz = -1;
			
	

	}
}

void drawObstacleRegion2( GLfloat x1 , GLfloat y1 , GLfloat z1 )
{
	GLfloat yObs ;


	if ( y1 == 0)
		yObs = -40;
	if(y1 == 1)
		yObs = 30;
	if(y1 ==2)
		yObs = 100;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D , texture5);	
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	glBegin(GL_QUADS);
		glTexCoord2f(0 , 1);
		glVertex3f( x1 , yObs , z1);	
		
		glTexCoord2f(0 , 0 );
		glVertex3f( x1 , yObs - 60 , z1);
		
		glTexCoord2f(1 , 0);
		glVertex3f( x1 , yObs - 60 , z1-100);
		
		glTexCoord2f(1 , 1);
		glVertex3f( x1 , yObs , z1-100);
	glEnd();
}

void drawObstacleRegion4( GLfloat x1 , GLfloat y1 , GLfloat z1 )
{
	GLfloat yObs = 30.0f;
	
	if ( y1 == 0)
		yObs = -40;
	if(y1 == 1)
		yObs = 30;
	if(y1 ==2)
		yObs = 100;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D , texture5);	
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	glBegin(GL_QUADS);

		glTexCoord2f(0 , 1);
		glVertex3f( x1 , yObs , z1);	
		glTexCoord2f(0 , 0);
		glVertex3f( x1 , yObs - 60 , z1);
		glTexCoord2f(1 , 0);
		glVertex3f( x1 , yObs - 60 , z1+100);
		glTexCoord2f(1 , 1);
		glVertex3f( x1 , yObs , z1+100);
	glEnd();
}

void drawObstacleRegion3( GLfloat x1 , GLfloat y1 , GLfloat z1 )
{
	GLfloat yObs = 30.0f;
	
	if ( y1 == 0)
		yObs = -40;
	if(y1 == 1)
		yObs = 30;
	if(y1 ==2)
		yObs = 100;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D , texture5);	
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	glBegin(GL_QUADS);
		glTexCoord2f(0 , 1);
		glVertex3f( x1 , yObs , z1);	
		glTexCoord2f(0 , 0);
		glVertex3f( x1 , yObs - 60 , z1);
		glTexCoord2f(1 , 0);
		glVertex3f( x1-100 , yObs - 60 , z1);
		glTexCoord2f(1 , 1);
		glVertex3f( x1-100 , yObs , z1);
	glEnd();
}

void drawObstacleRegion1( GLfloat x1 , GLfloat y1 , GLfloat z1 )
{
	GLfloat yObs = 30.0f;
	
	if ( y1 == 0)
		yObs = -40;
	if(y1 == 1)
		yObs = 30;
	if(y1 ==2)
		yObs = 100;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D , texture5);	
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	glBegin(GL_QUADS);
		glTexCoord2f(0 ,1);
		glVertex3f( x1 , yObs , z1);	
		glTexCoord2f(0 , 0);
		glVertex3f( x1 , yObs - 60 , z1);
		glTexCoord2f(1 , 0);
		glVertex3f( x1+100 , yObs - 60 , z1);
		glTexCoord2f(1 , 1);
		glVertex3f( x1+100 , yObs , z1);
	glEnd();
}
void generateObstacle ( float region )
{
	if ( region == 2 )
	{
		
		if( check2 ==1 )
		{
		xRandom = 400 - ( rand() % 500 + 200 );
		yRandom = rand() % 3; 
		
		}
		
		drawObstacleRegion2( xRandom , yRandom , -400);
		check2 = 0 ;
		check1 = 1 ; 
		check3 = 1;
		check4 = 1;
	}

	if ( region == 4 )
	{
		
		if( check4 ==1 )
		{
		xRandom = 400 - ( rand() % 500 + 200 );
		yRandom = rand() % 3; 
		
		}
		
		drawObstacleRegion4( xRandom , yRandom , 400);
		check2 = 1 ;
		check1 = 1 ; 
		check3 = 1;
		check4 = 0;
	}

	if ( region == 3 )
	{
		
		if( check3 ==1 )
		{
		zRandom = 400 - ( rand() % 500 + 200 );
		yRandom = rand() % 3; 
		
		}
		
		drawObstacleRegion3( -400 , yRandom , zRandom);
		check2 = 1 ;
		check1 = 1 ; 
		check3 = 0;
		check4 = 1;
	}

	if ( region == 1 )
	{
		
		if( check1 ==1 )
		{
		xRandom = 400 - ( rand() % 500 + 200 );
		yRandom = rand() % 3; 
		
		}
		
		drawObstacleRegion1( 400 , yRandom , zRandom);
		check2 = 1 ;
		check1 = 0 ; 
		check3 = 1;
		check4 = 1;
	}
}
/*
void gameOver( void )
{
	x = 0.0f;
	y = 0.0f;
	z= 0.0f;
	lx = 0.0f;
	ly = 0.0f;
	lz = -1.0f;
}
*/
void collisionDetector( float region)
{
	
	if ( y == 0 )
	{
		yCheck = 1.0f;
	}

	if ( y == 75 )
	{
		yCheck = 2.0f;
	}

	if ( y == -75 )
	{
		yCheck = 0.0f;
	}
	
	if ( region == 1)
	{
		if ( z == zRandom && yCheck == yRandom )
		{
			//gameOver();	
			printf(" \n game over \n");
		}
	}

	if ( region == 2)
	{
		if ( x == xRandom && yCheck == yRandom )
		{
			//gameOver();	
			printf(" \n game over \n");
		}
	}

	if ( region == 3)
	{
		if ( z == zRandom && yCheck == yRandom )
		{
			//gameOver();
			printf(" \n game over \n");
		}
	}

	if ( region == 4)
	{
		if ( x == xRandom && yCheck == yRandom )
		{
			//gameOver();
			printf(" \n game over \n");
		}
	}



}



void SetupRC(void)
{
	glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
	//glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	//glPolygonMode(GL_FRONT , GL_FILL);
	//glPolygonMode(GL_BACK , GL_LINE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

	Image* image1 = loadBMP("outer_wall.BMP");
	Image* image2 = loadBMP("inner_wall.BMP");
	Image* image3 = loadBMP("floor_long.BMP");
	Image* image4 = loadBMP("floor_short.BMP");
	Image* image5 = loadBMP("obstacle.BMP");

	texture1 = loadTexture(image1);
	texture2 = loadTexture(image2);
	texture3 = loadTexture(image3);
	texture4 = loadTexture(image4);
	texture5 = loadTexture(image5);

	delete image1 , image2 , image3 , image4 , image5;
}

void drawOuterShell()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D , texture1);	
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	glBegin(GL_QUADS);
		
	//region 1
		glTexCoord2f(0 , 0);
		glVertex3f(500 , -100 , -500);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(500 , -100 , 500);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(500 , 100 , 500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(500 , 100 , -500);
	//region 2
		glTexCoord2f(0 , 0);
		glVertex3f(-500 , -100 , -500);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(500 , -100 , -500);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(500 , 100 , -500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(-500 , 100 , -500);

	//region 3
		glTexCoord2f(0 , 0);
		glVertex3f(-500 , -100 , 500);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(-500 , -100 , -500);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(-500 , 100 , -500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(-500 , 100 , 500);

	//region 4
		glTexCoord2f(0 , 0);
		glVertex3f(500 , -100 , 500);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(-500 , -100 , 500);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(-500 , 100 , 500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(500 , 100 , 500);

	
	glEnd();

	glBindTexture(GL_TEXTURE_2D , texture2);	
	
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	glBegin(GL_QUADS);
		
	//region 1
		glTexCoord2f(0 , 0);
		glVertex3f(400 , -100 , -400);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(400 , -100 , 400);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(400 , 100 , 400);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(400 , 100 , -400);
	//region 2
		glTexCoord2f(0 , 0);
		glVertex3f(-400 , -100 , -400);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(400 , -100 , -400);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(400 , 100 , -400);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(-400 , 100 , -400);

	//region 3
		glTexCoord2f(0 , 0);
		glVertex3f(-400 , -100 , 400);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(-400 , -100 , -400);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(-400 , 100 , -400);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(-400 , 100 , 400);

	//region 4
		glTexCoord2f(0 , 0);
		glVertex3f(400 , -100 , 400);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(-400 , -100 , 400);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(-400 , 100 , 400);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(400 , 100 , 400);

	
	glEnd();

	glBindTexture(GL_TEXTURE_2D , texture3);	
	
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	glBegin(GL_QUADS);
		
	//long floor region 1
		glTexCoord2f(0 , 0);
		glVertex3f(400 , -100 , -500);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(400 , -100 , 500);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(500 , -100 , 500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(500 , -100 , -500);
	//long floor region 3
		glTexCoord2f(0 , 0);
		glVertex3f(-400 , -100 , 500);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(-400 , -100 , -500);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(-500 , -100 , -500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(-500 , -100 , 500);

	//long roof region 1
		glTexCoord2f(0 , 0);
		glVertex3f(400 , 100 , -500);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(400 , 100 , 500);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(500 , 100 , 500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(500 , 100 , -500);

	//long roof region 3
		glTexCoord2f(0 , 0);
		glVertex3f(-400 , 100 , 500);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(-400 , 100 , -500);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(-500 , 100 , -500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(-500 , 100 , 500);

	
	glEnd();

	glBindTexture(GL_TEXTURE_2D , texture4);	
	
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	glBegin(GL_QUADS);
		
	//short floor region 2
		glTexCoord2f(0 , 0);
		glVertex3f(-400 , -100 , -400);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(400 , -100 , -400);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(400 , -100 , -500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(-400 , -100 , -500);
	//short floor region 4
		glTexCoord2f(0 , 0);
		glVertex3f(400 , -100 , 400);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(-400 , -100 , 400);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(-400 , -100 , 500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(400 , -100 , 500);

	//short roof region 2
		glTexCoord2f(0 , 0);
		glVertex3f(-400 , 100 , -400);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(400 , 100 , -400);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(400 , 100 , -500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(-400 , 100 , -500);

	//short roof region 4
		glTexCoord2f(0 , 0);
		glVertex3f(400 , 100 , 400);
		
		glTexCoord2f( 1 , 0);
		glVertex3f(-400 , 100 , 400);
		
		glTexCoord2f( 1 , 1);
		glVertex3f(-400 , 100 , 500);
		
		glTexCoord2f( 0 , 1);
		glVertex3f(400 , 100 , 500);

	
	glEnd();
	
}


void RenderScene( void )
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();	
	
	//glTranslatef(x_trans, y_trans , zoom_out);	
	//glRotatef(xRot , 1.0f , 0.0f , 0.0f);
	//glRotatef(yRot , 0.0f , 1.0f , 0.0f);
	
	gluLookAt( x , y , z , x+lx , y+ly , z+lz , 0.0f , 1.0f , 0.0f);

	glColor3f(1.0f , 1.0f , 1.0f);
	drawOuterShell();
	generateObstacle(region);
	collisionDetector(region);
	
	printf("Render scene working \n");
	
	glPopMatrix();
	glutSwapBuffers();

}


void Timer (int value)
{
	t = t+1;

	if ( t > 2000 && t < 5000)
	{
		speed = 1.5;
	}

	if ( t > 5000)
	{
		speed = 2;
	}
	
	movePlayer();
	printf(" region is \t %f \t check2 is \t %f \t t is \t %f \t speed is \t %f \n" , region , check2 , t , speed);
	printf(" x is \t : %f and Z is \t : %f \t and Zrandom is %f \n" , x, z , zRandom);
	
	glutPostRedisplay();
	glutTimerFunc(33 , Timer , 1);
	
}


void ChangeSize(GLsizei w , GLsizei h)
{
	GLfloat aspectRatio;

	if(h==0)
	{
		h=1;
	}

	glViewport(0,0,w,h);


	height = h;

	//Resetting coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat) w / (GLfloat) h ;

	gluPerspective(60.0f , aspectRatio , 1.0f , 1000.0f );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void processSpecialKeys( int key , int x , int y)
{
	keySpecialStates[key] = true;
	printf("Special Keys DOWN registered \n");	
	printf("%d \t %d \n",x,y);
	keyOperations();
	glutPostRedisplay();
}

void processSpecialKeysUp( int key , int x , int y)
{
	keySpecialStates[key] = false;
	printf("Special Keys UP registered \n");	
	printf("%d \t %d \n",x,y);
	//glutPostRedisplay();
}

void processKeyboardKeys( unsigned char key , int x , int y)
{
	keyNormalStates[key] = true;
	printf("Normal Keys DOWN registered \n");	
	printf(" %f \t %f \t %f \n" , xRot , yRot , zoom_out);
	keyOperations();
	glutPostRedisplay();
}

void processKeyboardKeysUP( unsigned char key , int x , int y)
{
	keyNormalStates[key] = false;
	printf("Normal Keys UP registered \n");	
	printf(" %f \t %f \t %f \n" , xRot , yRot , zoom_out);
	keyOperations();
	glutPostRedisplay();
}

void processMouse(int button , int state , int x , int y)
{
	if ( state == GLUT_DOWN)
	{
		printf("mouse DOWN captured \n");
		xInitial = x;
		yInitial = y;
	}

	if(keyNormalStates['c'] == 1 && state == GLUT_DOWN)
	{
		pan = 1;
		rot = 0;
	}
	
	if( state == GLUT_UP )
	{
		pan = 0;
		rot = 1;
	}
	
}

void processPassiveMotion( int x1 , int y1)
{
	GLfloat heightFactor = height/3;

	if ( y1 >= 2*heightFactor )
	{
		y = y-1;

		if ( y <=-75 )
		{
			y = -75;
		}
	}


	if ( y1 < heightFactor )
	{

		y = y + 1;

		if ( y >=75 )
		{
			y = 75;
		}
	}
	
}

int main( int argc , char* argv[])
{
	glutInit(&argc , argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutCreateWindow("GAME");
	glutInitWindowSize(1000 , 800);
	
	glutKeyboardFunc(processKeyboardKeys);
	glutKeyboardUpFunc(processKeyboardKeysUP);
	
	glutSpecialFunc(processSpecialKeys);
	glutSpecialUpFunc(processSpecialKeysUp);
	
	//glutMouseFunc(processMouse);
	//glutPassiveMotionFunc(processPassiveMotion);

	glutDisplayFunc(RenderScene);
	//glutIdleFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(66 , Timer , 1 );
	

	SetupRC();
	
	glutMainLoop();
	return 0;

}