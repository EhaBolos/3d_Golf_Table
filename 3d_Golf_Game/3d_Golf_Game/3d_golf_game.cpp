#include <GL/glut.h>
#include <String.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
void delay(float secs)
{
	float end = clock() / CLOCKS_PER_SEC + secs;
	while ((clock() / CLOCKS_PER_SEC) < end);
}
char  string[300];
int flag = 0, f = 0, scoreFlag = 0, ballsC = 0;
int rot = 0, rot2 = 0, rot3 = 0, rot4 = 0, j = 0, score = 0, ourStartFlag = 0;
int CounterArr[5] = { 0,0,0,0,0 };
float r = 1, b = 1, g = 1, rotM = 0;
float kx[6] = { -1, -2.8,2.8,2,0,-2 }, kz[6] = { 1,-0.5,1.5,-0.9,-2.5,-0.8 };
float x1 = 0, yy1 = 0, z1 = 0, flagset = 0, distance, longball = 0.4, down = 1.5, up = -1.5;
float xx1 = 0, yyy1 = 0, zz1 = 0, rightmax = 6.5, leftmax = -5.5, upmax = -3.6, downmax = 3.6, holeX1 = -4.7, holesX2 = -3.7, holey1 = 1.5, holeY2 = 2.5, holeY3 = -1.5, holeY4 = -2.5;
GLfloat lx = -2.5, ly = 1.0, lz = 0.0;
GLfloat xT = 0;
struct  Stick
{
	float x1 = 4.5;
	float y1 = 2.5;
	float y2 = 2.9;
	float z1 = 1.2;
	float z2 = -1.2;
};
struct Stick st;
////////////////////////////////////
struct ball {
	float x;
	float y;
	float z;
	int flagpint;
	int flagupdown;
	int flagleftright;
};
struct ball Ball[5];
////////////////////////////////////
void output(float x, float y, char* string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
	}
}
////////////////////////////////////
void StickDraw()
{
	glColor3f(0, 0, 0);
	glRotatef(rotM, 0, 1, 0);
	glVertex3f(st.x1, st.y1, (st.z1 + rotM));
	glVertex3f(st.x1, st.y2, (st.z1 + rotM));
	glVertex3f(st.x1, st.y2, (st.z2 + rotM));
	glVertex3f(st.x1, st.y1, (st.z2 + rotM));
}
void ball()
{
	for (int i = 0; i < 5; i++)
	{
		Ball[i].x = kx[i];
		Ball[i].y = 2.8;
		Ball[i].z = kz[i];
		if (CounterArr[i] == 0)
		{
			Ball[i].flagleftright = flagset;
			Ball[i].flagupdown = flagset;
			Ball[i].flagpint = flagset;
			CounterArr[i]++;
		}
	}
}
////////////////////////////////////
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q') exit(1);
	if (key == 'h')
	{
		if (flag == 0)
			flag++;
		else
			flag = 0;
	}
	if (key == 'k')
	{
		rot2 += 5;
		rot2 %= 360;
	}
	if (key == 'l')
	{
		rot2 -= 5;
		rot2 %= 360;
	}
	if (key == ' ')
	{
		ourStartFlag = 1;
		f++;
	}
	if (key == 'a' && (st.z1 + rotM <= 2.9))
	{
		rotM += 0.6;
	}
	if (key == 'd' && (st.z2 + rotM >= -2.9))
		rotM -= 0.6;

	if (key == 'w' && f == 0) {
		rot4 += 5;
		rot4 %= 90;
	}
	if (key == 's' && f == 0)
	{
		rot4 -= 5;
		rot4 %= 180;
	}
	if (key == 'r' && f == 0)
	{
		rot3 += 5;
		rot3 %= 360;
	}
	if (key == 't' && f == 0)
	{
		rot3 -= 5;
		rot3 %= 360;
	}
	//lightning
	if (key == '1') lz -= 0.5;
	if (key == '2') lz += 0.5;
	glutPostRedisplay();
}
////////////////////////////////////
void draw2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, -3, -12);
	glClearColor(0.5f, 0.5f, 0.5f, 1);
	glRotatef(rot4, 1, 0, 0);
	glRotatef(rot3, 0, 1, 0);
	//calling_Ball_Function
	ball();
	r = 9;
	g = 6;
	b = 6;
	//Drawing_Balls_Randomally
	for (int i = 0; i < 5; i++)
	{
		glTranslatef(Ball[i].x, Ball[i].y, Ball[i].z);
		glColor3f(r, g, b);
		if (Ball[i].flagpint == 0)
			glutSolidSphere(0.3, 10, 10);
		glTranslatef(-Ball[i].x, -Ball[i].y, -Ball[i].z);
		b -= 3;
		r -= 3;
		g -= 9;
	}
	//FLoOR
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.1f, 0.1f);
	glNormal3f(0, 1, 0);
	glVertex3f(-5, 0, -5);
	glVertex3f(5, 0, -5);
	glVertex3f(5, 0, 5);
	glVertex3f(-5, 0, 5);
	glEnd();
	glBegin(GL_QUADS);
	// Front
	glColor3f(0.5f, 0.33f, 0.05f);
	glNormal3f(1, 0, 1);
	glVertex3f(-5, 1.5, 3);
	glVertex3f(-5, 2.5, 3);
	glVertex3f(5, 2.5, 3);
	glVertex3f(5, 1.5, 3);
	//leftKunt
	glVertex3f(-5, 2.5, 3);
	glVertex3f(-5, 3.5, 3);
	glVertex3f(4, 3.5, 3);
	glVertex3f(4, 2.5, 3);
	///
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(-1, 0, 1);
	glVertex3f(3, 0, 3);
	glVertex3f(3, 2, 3);
	glVertex3f(3.5, 2, 3);
	glVertex3f(3.5, 0, 3);
	glNormal3f(-1, 0, 1);
	glVertex3f(3, 0, 2.5);
	glVertex3f(3, 2, 2.5);
	glVertex3f(3.5, 2, 2.5);
	glVertex3f(3.5, 0, 2.5);
	glVertex3f(3.5, 0, 3);
	glVertex3f(3.5, 2, 3);
	glVertex3f(3.5, 2, 2.5);
	glVertex3f(3.5, 0, 2.5);
	glNormal3f(-1, 0, 1);
	glVertex3f(3, 0, 3);
	glVertex3f(3, 2, 3);
	glVertex3f(3, 2, 2.5);
	glVertex3f(3, 0, 2.5);
	//back
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(1, 0, -1);
	glVertex3f(-5, 1.5, -3);
	glVertex3f(-5, 2.5, -3);
	glVertex3f(5, 2.5, -3);
	glVertex3f(5, 1.5, -3);
	//rightKunt
	glNormal3f(1, 0, -1);
	glVertex3f(-5, 2.5, -3);
	glVertex3f(-5, 3.5, -3);
	glVertex3f(4, 3.5, -3);
	glVertex3f(4, 2.5, -3);
	/////////////
	glVertex3f(-3.5, 2, -3);
	glVertex3f(-3.5, 0, -3);
	glVertex3f(-3, 0, -3);
	glVertex3f(-3, 2, -3);
	glVertex3f(-3.5, 2, -2.5);
	glVertex3f(-3.5, 0, -2.5);
	glVertex3f(-3, 0, -2.5);
	glVertex3f(-3, 2, -2.5);
	glVertex3f(-3.5, 2, -3);
	glVertex3f(-3.5, 0, -3);
	glVertex3f(-3.5, 0, -2.5);
	glVertex3f(-3.5, 2, -2.5);
	glVertex3f(-3, 2, -3);
	glVertex3f(-3, 0, -3);
	glVertex3f(-3, 0, -2.5);
	glVertex3f(-3, 2, -2.5);
	//left 
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(1, 0, 0);
	glVertex3f(-5, 1.5, 3);
	glVertex3f(-5, 2.5, 3);
	glVertex3f(-5, 2.5, -3);
	glVertex3f(-5, 1.5, -3);
	//UpperKunt
	glVertex3f(-5, 2.5, 3);
	glVertex3f(-5, 3.5, 3);
	glVertex3f(-5, 3.5, -3);
	glVertex3f(-5, 2.5, -3);
	////
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(1, 0, 0);
	glVertex3f(-3.5, 2, 3);
	glVertex3f(-3.5, 0, 3);
	glVertex3f(-3, 0, 3);
	glVertex3f(-3, 2, 3);
	glNormal3f(1, 0, 0);
	glVertex3f(-3.5, 2, 2.5);
	glVertex3f(-3.5, 0, 2.5);
	glVertex3f(-3, 0, 2.5);
	glVertex3f(-3, 2, 2.5);
	glNormal3f(1, 0, 0);
	glVertex3f(-3.5, 2, 3);
	glVertex3f(-3.5, 0, 3);
	glVertex3f(-3.5, 0, 2.5);
	glVertex3f(-3.5, 2, 2.5);
	glNormal3f(1, 0, 0);
	glVertex3f(-3, 2, 3);
	glVertex3f(-3, 0, 3);
	glVertex3f(-3, 0, 2.5);
	glVertex3f(-3, 2, 2.5);
	//right
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(1, 0, 3);
	glVertex3f(5, 1.5, 3);
	glVertex3f(5, 2.5, 3);
	glVertex3f(5, 2.5, -3);
	glVertex3f(5, 1.5, -3);
	////
	glNormal3f(1, 0, 1);
	glVertex3f(3.5, 0, -3);
	glVertex3f(3.5, 2, -3);
	glVertex3f(3, 2, -3);
	glVertex3f(3, 0, -3);
	glNormal3f(1, 0, 1);
	glVertex3f(3.5, 0, -2.5);
	glVertex3f(3.5, 2, -2.5);
	glVertex3f(3, 2, -2.5);
	glVertex3f(3, 0, -2.5);
	glNormal3f(1, 0, 1);
	glVertex3f(3.5, 0, -3);
	glVertex3f(3.5, 2, -3);
	glVertex3f(3.5, 2, -2.5);
	glVertex3f(3.5, 0, -2.5);
	glNormal3f(1, 0, 1);
	glVertex3f(3, 0, -3);
	glVertex3f(3, 2, -3);
	glVertex3f(3, 2, -2.5);
	glVertex3f(3, 0, -2.5);
	///UP
	glColor3f(0.0, 0.5, 0.0);
	glNormal3f(1, 0, 1);
	glVertex3f(-5, 2.5, 3);
	glVertex3f(5, 2.5, 3);
	glVertex3f(5, 2.5, -3);
	glVertex3f(-5, 2.5, -3);
	//holeOne
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-4.7, 2.51, 2.5);
	glVertex3f(-3.7, 2.51, 2.5);
	glVertex3f(-3.7, 2.51, 1.5);
	glVertex3f(-4.7, 2.51, 1.5);
	//holeTwo
	glVertex3f(-4.7, 2.51, -2.5);
	glVertex3f(-3.7, 2.51, -2.5);
	glVertex3f(-3.7, 2.51, -1.5);
	glVertex3f(-4.7, 2.51, -1.5);
	//stick
	StickDraw();
	glEnd();
	glRotatef(-rot3, 0, 1, 0);
	glTranslatef(x1, yy1, z1);
	glRotatef(rot4, 0, 1, 0);
	//instructions
	sprintf_s(string, "[ R/T ] to move the table Left/Right");
	glColor3f(0, 0, 0);
	output(-4, 8.2, string);
	sprintf_s(string, "[ W/S ] to move the table Up/Down");
	glColor3f(0, 0, 0);
	output(-4, 7.8, string);
	sprintf_s(string, "[ A/D ] to move the Stick L/R");
	glColor3f(0, 0, 0);
	output(-4, 7.4, string);
	sprintf_s(string, "[ Space ] to lock the table position and starts the game");
	glColor3f(0, 0, 0);
	output(-4, 7, string);
	sprintf_s(string, "[ Q ] to Quit the game");
	glColor3f(0, 0, 0);
	output(-4, 6.6, string);
	sprintf_s(string, "[ Score ] : %d", score);
	glColor3f(0, 0, 1);
	output(-1.5, 5.8, string);
	glutSwapBuffers();			// display the output
}
///////////////////////////////////
float two_dis(float x1, float y1, float x2, float y2)
{
	/*Distance_Between_2_Balls*/
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

}
//////////////////////////////////
void Idle(void) {
	if (flag == 1) {
		if (ourStartFlag == 1) {
			for (int i = 0; i < 5; i++)
			{
				if (i != j)
				{
					for (j = 0; j < 5; j++)
					{
						distance = two_dis(Ball[i].x, Ball[i].z, Ball[j].x, Ball[j].z);
						///////////////////////////////////////////
						if (Ball[i].x <= rightmax && Ball[i].flagleftright == 0)
						{
							if (Ball[i].flagpint == 0)
							{
								kx[i] += 0.0006;
							}
							if (Ball[i].x >= rightmax - 1)
							{
								Ball[i].flagleftright = 1;
							}
						}
						///////////////////////////////////////////
						if (Ball[i].x >= leftmax && Ball[i].flagleftright == 1)
						{
							if (Ball[i].flagpint == 0)
							{
								kx[i] -= 0.0006;
							}
							if (Ball[i].x <= leftmax + 1)
							{
								Ball[i].flagleftright = 0;
							}
						}
						///////////////////////////////////////////
						if (Ball[i].z >= upmax && Ball[i].flagupdown == 0)
						{
							if (Ball[i].flagpint == 0)
							{
								kz[i] -= 0.0006;
							}
							if (Ball[i].z <= upmax + 1)
							{
								Ball[i].flagupdown = 1;

							}
						}
						///////////////////////////////////////////
						if (Ball[i].z <= downmax && Ball[i].flagupdown == 1)
						{
							if (Ball[i].flagpint == 0)
							{
								kz[i] += 0.0006;
							}
							if (Ball[i].z >= downmax - 1)
							{
								Ball[i].flagupdown = 0;
							}
						}
						///////////////////////////////////////////
						if (distance <= longball)
						{
							if (i != j)
							{
								if (Ball[i].flagleftright == 1 && Ball[j].flagleftright == 0)
								{
									Ball[i].flagleftright = 0;
									Ball[j].flagleftright = 1;
								}
								if (Ball[i].flagupdown == 1 && Ball[j].flagupdown == 0)
								{
									Ball[i].flagupdown = 0;
									Ball[j].flagupdown = 1;
								}
							}
						}
						//if the ball gets into 1 of the holes
						if (Ball[i].x >= holeX1 && Ball[i].x <= holesX2) {
							if ((Ball[i].z <= 2.5 && Ball[i].z >= 1.5) || (Ball[i].z >= -2.5 && Ball[i].z <= -1.5))
							{
								Ball[i].flagpint = 1;
								scoreFlag += 30;
								score = scoreFlag;
								kx[i] = NULL;

							}
						}
						//if the ball get out of the table
						if (Ball[i].x > 4.5) {
							Ball[i].flagpint = 1;
							scoreFlag -= 15;
							score = scoreFlag;
							kx[i] = NULL;
						}
						//Ball_Stick
						if (Ball[i].x > 4.2 && Ball[i].x <= 4.5)
						{
							if (Ball[i].z >= st.z2 + rotM && Ball[i].z <= st.z1 + rotM)
							{
								kx[i] -= 0.0005;
								Ball[i].flagleftright = 1;
							}
						}
					}
				}

			}
		}
		draw2();
	}
}
void cube()/*The_Table*/
{
	glBegin(GL_QUADS);
	//Front_Side
	glColor3f(0.5f, 0.33f, 0.05f);
	glNormal3f(1, 0, 1);
	glVertex3f(-4.5, 1.5, 3);
	glVertex3f(-4.5, 2.5, 3);
	glVertex3f(4.5, 2.5, 3);
	glVertex3f(4.5, 1.5, 3);
	///////////////////////////////////////////
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(-1, 0, 1);
	glVertex3f(2.5, 0, 3);
	glVertex3f(2.5, 2, 3);
	glVertex3f(3, 2, 3);
	glVertex3f(3, 0, 3);
	///////////////////////////////////////////
	glNormal3f(-1, 0, 1);
	glVertex3f(2.5, 0, 2.5);
	glVertex3f(2.5, 2, 2.5);
	glVertex3f(3, 2, 2.5);
	glVertex3f(3, 0, 2.5);
	///////////////////////////////////////////
	glVertex3f(3, 0, 3);
	glVertex3f(3, 2, 3);
	glVertex3f(3, 2, 2.5);
	glVertex3f(3, 0, 2.5);
	///////////////////////////////////////////
	glNormal3f(-1, 0, 1);
	glVertex3f(2.5, 0, 3);
	glVertex3f(2.5, 2, 3);
	glVertex3f(2.5, 2, 2.5);
	glVertex3f(2.5, 0, 2.5);
	//back
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(1, 0, -1);
	glVertex3f(-4.5, 1.5, -3);
	glVertex3f(-4.5, 2.5, -3);
	glVertex3f(4.5, 2.5, -3);
	glVertex3f(4.5, 1.5, -3);
	///////////////////////////////////////////
	glNormal3f(1, 0, 1);
	glVertex3f(-3, 2, -3);
	glVertex3f(-3, 0, -3);
	glVertex3f(-2.5, 0, -3);
	glVertex3f(-2.5, 2, -3);
	///////////////////////////////////////////
	glNormal3f(1, 0, 1);
	glVertex3f(-3, 2, -2.5);
	glVertex3f(-3, 0, -2.5);
	glVertex3f(-2.5, 0, -2.5);
	glVertex3f(-2.5, 2, -2.5);
	///////////////////////////////////////////
	glNormal3f(1, 0, 1);
	glVertex3f(-3, 2, -3);
	glVertex3f(-3, 0, -3);
	glVertex3f(-3, 0, -2.5);
	glVertex3f(-3, 2, -2.5);
	///////////////////////////////////////////
	glNormal3f(1, 0, 1);
	glVertex3f(-2.5, 2, -3);
	glVertex3f(-2.5, 0, -3);
	glVertex3f(-2.5, 0, -2.5);
	glVertex3f(-2.5, 2, -2.5);
	//left 
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(1, 0, 0);
	glVertex3f(-4.5, 1.5, 3);
	glVertex3f(-4.5, 2.5, 3);
	glVertex3f(-4.5, 2.5, -3);
	glVertex3f(-4.5, 1.5, -3);
	///////////////////////////////////////////
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(1, 0, 0);
	glVertex3f(-3, 2, 3);
	glVertex3f(-3, 0, 3);
	glVertex3f(-2.5, 0, 3);
	glVertex3f(-2.5, 2, 3);
	///////////////////////////////////////////
	glNormal3f(1, 0, 0);
	glVertex3f(-3, 2, 2.5);
	glVertex3f(-3, 0, 2.5);
	glVertex3f(-2.5, 0, 2.5);
	glVertex3f(-2.5, 2, 2.5);
	///////////////////////////////////////////
	glNormal3f(1, 0, 0);
	glVertex3f(-3, 2, 3);
	glVertex3f(-3, 0, 3);
	glVertex3f(-3, 0, 2.5);
	glVertex3f(-3, 2, 2.5);
	///////////////////////////////////////////
	glNormal3f(1, 0, 0);
	glVertex3f(-2.5, 2, 3);
	glVertex3f(-2.5, 0, 3);
	glVertex3f(-2.5, 0, 2.5);
	glVertex3f(-2.5, 2, 2.5);
	//right
	glColor3f(0.5f, 0.35f, 0.05f);
	glNormal3f(1, 0, 3);
	glVertex3f(4.5, 1.5, 3);
	glVertex3f(4.5, 2.5, 3);
	glVertex3f(4.5, 2.5, -3);
	glVertex3f(4.5, 1.5, -3);
	///////////////////////////////////////////
	glNormal3f(1, 0, 1);
	glVertex3f(3, 0, -3);
	glVertex3f(3, 2, -3);
	glVertex3f(2.5, 2, -3);
	glVertex3f(2.5, 0, -3);
	///////////////////////////////////////////
	glNormal3f(1, 0, 1);
	glVertex3f(3, 0, -2.5);
	glVertex3f(3, 2, -2.5);
	glVertex3f(2.5, 2, -2.5);
	glVertex3f(2.5, 0, -2.5);
	///////////////////////////////////////////
	glNormal3f(1, 0, 1);
	glVertex3f(3, 0, -3);
	glVertex3f(3, 2, -3);
	glVertex3f(3, 2, -2.5);
	glVertex3f(3, 0, -2.5);
	///////////////////////////////////////////
	glNormal3f(1, 0, 1);
	glVertex3f(2.5, 0, -3);
	glVertex3f(2.5, 2, -3);
	glVertex3f(2.5, 2, -2.5);
	glVertex3f(2.5, 0, -2.5);
	/*UP*/
	glColor3f(0.0, 0.5, 0.0);
	glNormal3f(1, 0, 1);
	glVertex3f(-4.5, 2.5, 3);
	glVertex3f(4.5, 2.5, 3);
	glVertex3f(4.5, 2.5, -3);
	glVertex3f(-4.5, 2.5, -3);
	glEnd();
}
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
	if (flag == 0) {
		glLoadIdentity();
		glTranslatef(0, -3, -12);
		glRotatef(rot, 0, 1, 0);
		/************************************************************/
		/************************************************************/
		/************************************************************/
		GLfloat ambientLight[] = { 0.0, 0.0, 0.0, 1.0f };
		GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
		GLfloat specularLight[] = { 0.5, 0.5, 0.5, 1.0f };
		GLfloat mat_shininess[] = { 128.0 };
		//x,y,z,light
		GLfloat position[] = { lx, ly, lz, 1.0f };
		// Assign created components to GL_LIGHT0
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
		glMaterialfv(GL_MAX_LIGHTS, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		/************************************************************/
		/************************************************************/
		GLfloat ambientLight1[] = { 0.2, 0.2, 0.2, 1.0f };
		GLfloat diffuseLight1[] = { 0.8f, 0.8f, 0.8, 1.0f };
		GLfloat specularLight1[] = { 0.5, 0.5, 0.5, 1.0f };
		//x,y,z,light
		GLfloat position1[] = { 2.5, ly, lz, 1.0f };
		// Assign created components to GL_LIGHT0
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
		/************************************************************/
		// Floor
		glColor3f(0.5f, 0.5f, 0.4f);
		glBegin(GL_QUADS);
		glColor3f(0.5f, 0.5f, 0.4f);
		glNormal3f(0, 1, 1);	// normal straight up
		glVertex3f(-6, 0, -6);
		glVertex3f(6, 0, -6);
		glVertex3f(6, 0, 6);
		glVertex3f(-6, 0, 6);
		glEnd();
		//sojade
		glBegin(GL_QUADS);
		glColor3f(0.5f, 0.1f, 0.1f);
		glNormal3f(0, 1, 1);
		glVertex3f(-4.3, 0.1, -4.3);
		glVertex3f(4.3, 0.1, -4.3);
		glVertex3f(4.3, 0.1, 4.3);
		glVertex3f(-4.3, 0.1, 4.3);
		glEnd();
		//roof
		glColor3f(0.5f, 0.5f, 0.4f);
		glBegin(GL_QUADS);
		glVertex3f(-6, 9.5, -6);
		glVertex3f(6, 9.5, -6);
		glVertex3f(6, 9.5, 6);
		glVertex3f(-6, 9.5, 6);
		glEnd();
		//lightning
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_QUADS);
		glVertex3f(-0.5, 7.5, 2);
		glVertex3f(-0.5, 8, 2);
		glVertex3f(0.5, 8, 2);
		glVertex3f(0.5, 7.5, 2);
		glBegin(GL_QUADS);
		glVertex3f(0.1, 6.5, 2);
		glVertex3f(0.1, 7.5, 2);
		glVertex3f(-0.1, 7.5, 2);
		glVertex3f(-0.1, 6.5, 2);
		//////////////////////////////////////////
		glVertex3f(0.1, 6.5, 2);
		glVertex3f(0.1, 7.5, 2);
		glVertex3f(-0.1, 7.5, 2);
		glVertex3f(-0.1, 6.5, 2);
		///////////////////////////////////////////
		glVertex3f(0.1, 6.5, 2);
		glVertex3f(0.1, 7.5, 2);
		glVertex3f(0.1, 7.5, 2);
		glVertex3f(0.1, 6.5, 2);
		///////////////////////////////////////////
		glVertex3f(-0.1, 6.5, 2);
		glVertex3f(-0.1, 7.5, 2);
		glVertex3f(-0.1, 7.5, 2);
		glVertex3f(-0.1, 6.5, 2);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(-2, 6, 2);
		glVertex3f(-2, 6.5, 2);
		glVertex3f(2, 6.5, 2);
		glVertex3f(2, 6, 2);
		glEnd();
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(1.5f, 6.0f, 2.0f);
		glutSolidSphere(0.3, 32, 32);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-1.5f, 6.0f, 2.0f);
		glutSolidSphere(0.3, 32, 32);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0f, 6.0f, 2.0f);
		glutSolidSphere(0.3, 32, 32);
		glPopMatrix();
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_QUADS);
		glVertex3f(-2, 5.9, 2.5);
		glVertex3f(-2, 6.5, 2.5);
		glVertex3f(2, 6.5, 2.5);
		glVertex3f(2, 5.9, 2.5);
		glEnd();
		///////////////////////////////////////////
				//wall1
		glBegin(GL_QUADS);
		glColor3f(0.5f, 0.7f, 0.5f);
		glNormal3f(0, 1, 0);
		glVertex3f(-6, 15, -6);
		glVertex3f(6, 15, -6);
		glVertex3f(6, 0, -6);
		glVertex3f(-6, 0, -6);
		glEnd();
		///////////////////////////////////////////
				//wall2
		glColor3f(0.5f, 0.6f, 0.5f);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glVertex3f(6, 0, -6);
		glVertex3f(6, 15, -6);
		glVertex3f(6, 15, 6);
		glVertex3f(6, 0, 6);
		///////////////////////////////////////////
				//wall3
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glVertex3f(-6, 0, -6);
		glVertex3f(-6, 15, -6);
		glVertex3f(-6, 15, 6);
		glVertex3f(-6, 0, 6);
		glEnd();
		///////////////////////////////////////////
				//instructions
		sprintf_s(string, "Press [ L ] to move the table to left side ");
		glColor3f(0, 0, 0);
		output(-3.2, 5.5, string);
		sprintf_s(string, "Press [ K ] to move the table to right side ");
		glColor3f(0, 0, 0);
		output(-3.2, 5.1, string);
		sprintf_s(string, "Press [ 1/2 ] to control lightning");
		glColor3f(0, 0, 0);
		output(-3.2, 4.7, string);
		sprintf_s(string, "Press [ H ] to start the game ");
		glColor3f(0, 0, 0);
		output(-3.2, 4.3, string);
		sprintf_s(string, "Press [ Q ] to quit the game ");
		glColor3f(0, 0, 0);
		output(-3.2, 3.9, string);
		glRotatef(-rot, 0, 1, 0);
		glTranslatef(xx1, yyy1, zz1);
		glRotatef(rot2, 0, 1, 0);
		cube();//cube_Is_Table_Drawing_Func.
		glRotatef(-rot2, 0, 0, 1);
		glutSwapBuffers();			// display the output
	}
}

// Set OpenGL parameters
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 1.0, 100);
	glMatrixMode(GL_MODELVIEW);
	// Create light components
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	// RGB display, double-buffered, with Z-Buffer
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(350, 70); // posation in screen
	glutCreateWindow("Game Salon");
	glutDisplayFunc(draw);						// Set the display function
	glutKeyboardFunc(keyboard);					// Set the keyboard function
	glutIdleFunc(Idle); // Set the idle function
	init();
	glutMainLoop();							// Start the main event loop
}

