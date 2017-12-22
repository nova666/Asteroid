/*
* ////////////////////////////////////////////
*/
#include "include\freeglut.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

#pragma region colors for density
GLfloat lightColor = 0.0;
GLfloat darkColor = 0.0;
GLfloat colorDensity0 = 0.5;
GLfloat colorDensity1 = 0.2;
#pragma endregion

#pragma region costants
GLdouble PI = 3.14159;	    //Mathematical constant used for cos and sin functions
GLfloat angle = 2.0 * PI;
GLfloat angle_z = 0.0;
GLfloat angle_x = 0.0;
#pragma endregion

#pragma region primitive shapes
void drawTriangle(GLfloat X, GLfloat Y);
void drawStarAsteroid(GLfloat radius, GLfloat x, GLfloat y, double LineWidth);
void drawPolygonAsteroid(GLfloat radius, GLfloat x, GLfloat y, int points);
void drawCircle(GLfloat radius, GLfloat x, GLfloat y);
void setGridStipple(void);
void drawRocket(GLfloat radius, GLfloat x, GLfloat y);
#pragma endregion

#pragma region spaceShip
void drawShip(GLfloat X, GLfloat Y);
GLfloat spaceShipX = 0.0, spaceShipY = 0;
GLfloat rotation = 0.0;
#pragma endregion

#pragma region Asteroids Functions
void spinAsteroid(GLfloat x_Axis, GLfloat y_axis, GLfloat z_axis, GLfloat rotation, GLfloat radius, GLfloat xpos, GLfloat ypos, bool multiplyMatrix, GLint type);
void drawAsteroidType1(GLfloat radius, GLfloat x, GLfloat y);
void drawAsteroidType2(GLfloat radius, GLfloat x, GLfloat y);
void setShootingPoint(GLfloat radius, GLfloat x, GLfloat y, GLfloat angle);
void resetRocketPropertires(void);
GLfloat asteroidRotation = 10;
GLint number_MaxEnemies = 5;
GLint active_Enemies = 0;
#pragma endregion

#pragma region Asteroids Position
GLfloat positionAsteroidX[5] =
{
	0.0, 0.0, 0.0, 0.0, 0.0
};
GLfloat positionAsteroidY[5] =
{
	0.0, 0.0, 0.0, 0.0, 0.0
};

#pragma endregion

#pragma region Missle Logic
GLfloat movementBulletX = 1.0;
GLfloat movementBulletY = 1.0;

bool saveMissleOrigin = false; // used to save instance of rotation point
GLfloat missleRotation = 0.0;
GLfloat missleX = 0;     // orins of missle/rocket
GLfloat missleY = 0;
GLfloat missleRadius = 20.0;
bool attackON = false;

#pragma endregion

#pragma region Display score
GLint score_num = 0;
void setScoreBoard(void);
#pragma endregion

#pragma region Generate Number For Enemies
GLint points_polygon = 0.0;
GLint gen_NumX = 0.0;
GLint gen_NumY = 0.0;
GLint type_of_Enemy = 0;
bool is_gen_Num = false;
void generateEnemies(GLint option);
GLint type_Enemy[5] =
{
	0,0,0,0,0
};
#pragma endregion

#pragma region Collision Detection

bool collisionDetection(GLfloat Radius, GLfloat X, GLfloat Y);
bool collisionAsteroid[5] =
{
	false, false, false, false, false
};

#pragma endregion

#pragma region options For background
void optionDisplayBackground();
bool fly_Active = false;
bool grid_Active = false;
bool grid2_Active = false;
bool space_Active = true;
#pragma endregion

#pragma region patterns for background

GLubyte fly[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

GLubyte fly2[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1f, 0x80, 0x1f, 0xc0, 0x0f, 0xc0, 0x3f, 0x80,
	0x03, 0xf5, 0xff, 0x00, 0x07, 0xfd, 0xff, 0xf8,
	0x1f, 0xfc, 0xff, 0x08, 0xff, 0x03, 0xbf, 0x70,
	0x03, 0x10, 0x40, 0x40, 0x08, 0x88, 0x8c, 0x20,
	0x05, 0x05, 0x04, 0x40, 0x02, 0x82, 0x14, 0x40,
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
};

#pragma endregion

#pragma region Screen
GLsizei  wW = 640, wH = 480;
#pragma endregion

void reshape(GLsizei w, GLsizei h)
{
	// Prevent a divide by zero
	if (h == 0)
		h = 1;
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	// Reset coordinate system
	glLoadIdentity();
	// Establish clipping volume (left, right, bottom, top, near, far)
	// Set the aspect ratio of the clipping area to match the viewport
	if (w <= h)
		glOrtho(-wW, wW, -wW * w / w, wW, 1.0, -1.0);
	else
		glOrtho(-wW, wW * h / h, -wW, wW, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void writeBitmapString(void *font, char *string)
{
	char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void optionDisplayBackground()
{
	if (fly_Active)
	{
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonStipple(fly);
		glRectf(-1920.0, -1080.0, 1920.0, 1080.0);
		glDisable(GL_POLYGON_STIPPLE);
	}
	else if (grid_Active)
	{
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonStipple(fly2);
		glRectf(-1920.0, -1080.0, 1920.0, 1080.0);
		glDisable(GL_POLYGON_STIPPLE);
	}
	else if (grid2_Active)
	{

		setGridStipple();
	}


}

void setGridStipple(void)
{
	glEnable(GL_LINE_STIPPLE);
	glColor3f(1, 1, 1);
	glLineStipple(2, 0xbdbd);
	glLineWidth(1.5);
	glBegin(GL_LINES);
	for (int i = 0; i < 8; i++)
	{
		glVertex2f(-640 * 1, 80 * i);
		glVertex2f(640 * 1, 80 * i);
		glVertex2f(-640 * 1, -80 * i);
		glVertex2f(640 * 1, -80 * i);

		glVertex2f(80 * i, -640 * 1);
		glVertex2f(80 * i, 640 * 1);
		glVertex2f(-80 * i, -640 * 1);
		glVertex2f(-80 * i, 640 * 1);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);       

	optionDisplayBackground();

	glLoadIdentity();

	glPushMatrix();
	glRotatef(rotation, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.4, darkColor);
	drawShip(spaceShipX, spaceShipY);
	drawCircle(50.0, spaceShipX, spaceShipY);
	glPopMatrix();

	glLoadIdentity();

	glPushMatrix();

	glColor3f(1.0, 1.0, 0.0);


	for (int i = 0; i < number_MaxEnemies; i++)
	{
		if (active_Enemies == 0)
		{
			for (int J = 0; J < number_MaxEnemies; J++)
			{

				generateEnemies(1);
				positionAsteroidX[J] = (float)gen_NumX;
				positionAsteroidY[J] = (float)gen_NumY;
				collisionAsteroid[J] = false;
				active_Enemies += 1;
			}

			for (int K = 0; K < 5; K++)
			{
				generateEnemies(2);
				type_Enemy[K] = type_of_Enemy;
			}
			generateEnemies(3);
		}

		if (collisionAsteroid[i] == false)
		{
			spinAsteroid(false, false, true, asteroidRotation, 50.00, positionAsteroidX[i], positionAsteroidY[i], false, type_Enemy[i]);
			collisionAsteroid[i] = collisionDetection(50.0, positionAsteroidX[i], positionAsteroidY[i]);
		}

	}

	glPopMatrix();

	glLoadIdentity();

	if (saveMissleOrigin == true) 
	{
		setShootingPoint(1.0, missleX, missleY, missleRotation);
		drawCircle(missleRadius, missleX, missleY);
	}

	glLoadIdentity();

	setScoreBoard();
	glutSwapBuffers();

}
void setScoreBoard(void)
{
	glColor3f(darkColor, 0.4, 0.0);
	glRasterPos2f(-600, 500);
	writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Score");

	char score[10] = { '\0' };
	sprintf_s(score, "%d", score_num);
	glColor3f(darkColor, 0.4, 0.0);
	glRasterPos2f(-450, 500);
	writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, score);
}


void drawStarAsteroid(GLfloat radius, GLfloat x, GLfloat y, double LineWidth)
{
	GLfloat x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;

	x1 = x + cos(72 * PI / 180) * radius;
	y1 = y + sin(72 * PI / 180) * radius;
	x2 = x + cos(144 * PI / 180) * radius;
	y2 = y + sin(144 * PI / 180) * radius;
	x3 = x + cos(216 * PI / 180) * radius;
	y3 = y + sin(216 * PI / 180) * radius;
	x4 = x + cos(288 * PI / 180) * radius;
	y4 = y + sin(288 * PI / 180) * radius;
	x5 = x + radius;
	y5 = y;

	glLineWidth(LineWidth);

	// generate number if true do this
	glColor3f(darkColor, 0.0, 0.0);
	drawCircle(20, x1, y1);
	drawCircle(20, x2, y2);
	drawCircle(20, x3, y3);
	drawCircle(20, x4, y4);
	drawCircle(20, x5, y5);

	glColor3f(0.0, darkColor, lightColor);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x3, y3);
	glVertex2f(x1, y1);
	glVertex2f(x4, y4);
	glVertex2f(x2, y2);
	glVertex2f(x4, y4);
	glVertex2f(x2, y2);
	glVertex2f(x5, y5);
	glVertex2f(x3, y3);
	glVertex2f(x5, y5);
	glEnd();

	
	glFlush();
}

/////// generating random position of enemies, random type of enemies and number of points for polygons for asteroids///

void generateEnemies(GLint option)
{
	GLint option_chosen = option;
	if (option_chosen == 1)
	{
		GLint randomPosX = rand() % 1000 - 500;
		GLint randomPosY = rand() % 1000 - 500;
		do
		{
			randomPosX = rand() % 1000 - 500;
			randomPosY = rand() % 1000 - 500;
		} while (randomPosX >= -50 && randomPosX < 55 || randomPosY >= -50 && randomPosY < 55);

		gen_NumX = randomPosX;
		gen_NumY = randomPosY;
	}

	else if (option_chosen == 2)
	{
		GLint randomEnemy = rand() % 5;

		type_of_Enemy = randomEnemy;
	}
	else if (option_chosen == 3)
	{
		GLint randomPoints = rand() % 12;

		do
		{
			randomPoints = rand() % 8;
		} while (randomPoints > 12 || randomPoints < 4);

		points_polygon = randomPoints;
	}

	else
	{
		GLint randomPosX = rand() % 1000 - 500;
		GLint randomPosY = rand() % 1000 - 500;

		gen_NumX = randomPosX;
		gen_NumY = randomPosY;
	}


}

///////////// second attempt drawing spaceship // successful 
////////////// this function creates a shooting point for the ship using the rotation of its axis
void setShootingPoint(GLfloat radius, GLfloat x, GLfloat y, GLfloat angle)
{
	glColor3f(0.0, darkColor, darkColor);
	GLfloat x1, y1;

	x1 = x + cos(angle * PI / 180) * radius;
	y1 = y + sin(angle * PI / 180) * radius; // centre of the point

	if (attackON == false && saveMissleOrigin == false)
	{
		movementBulletX = 0;
		movementBulletY = 0;
	}
	else
	{
		movementBulletX = x1;
		movementBulletY = y1;
	}

	glPushMatrix();
	glTranslatef(x1, y1, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(-x1, -y1, 0.0);
	drawRocket(2.0, x1, y1);
	glPopMatrix();
}

////////////// having the shooting point set creates a missle towards the direction the point is pointing using the result trigonemtry sin cos
void drawRocket(GLfloat radius, GLfloat x, GLfloat y)
{
	glPointSize(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y + 20.0);
	glVertex2f(x, y - 20.0);
	glVertex2f(x + 20, y);
	glEnd();
}   /// should  be renamed Rockets

bool collisionDetection(GLfloat Radius, GLfloat X, GLfloat Y)
{
	GLfloat distX = X - missleX;
	GLfloat distY = Y - missleY;

	GLfloat distance = sqrt(distX * distX + distY * distY);
	if (distance <= (Radius + missleRadius))
	{

		score_num += 10;
		active_Enemies -= 1;
		resetRocketPropertires();
		return true;

	}
	else
	{
		return false;
	}

}

void drawCircle(GLfloat radius, GLfloat x, GLfloat y) {

	GLint i;
	GLint angle = 360;
	GLint points = 18;
	glLineWidth(2.0);
	//glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);

	for (i = 0; i < points; i++)
	{
		glVertex2f(x + radius* cos((angle / points * (PI / 180)) * i), y + radius* sin((angle / points * (PI / 180)) * i));
	}
	glEnd();
}
///creates asteroids of random shapes
void drawPolygonAsteroid(GLfloat radius, GLfloat x, GLfloat y, int points) {

	GLint i;
	GLint angle = 360;
	glLineWidth(2.0);
	glBegin(GL_POLYGON);

	for (i = 0; i < points; i++)
	{
		glVertex2f(x + radius* cos((angle / points * (PI / 180)) * i), y + radius* sin((angle / points * (PI / 180)) * i));

	}
	glEnd();
}

void spinAsteroid(GLfloat x_Axis, GLfloat y_Axis, GLfloat z_Axis,
	GLfloat rotation, GLfloat radius, GLfloat centreX, GLfloat centreY, bool multiplyMatrix, GLint type)
{
	GLfloat basic_Rotation = rotation;
	GLfloat x, y, z;

	x = 0;
	y = 0;
	z = 0;

	if (x_Axis) x = 1.0;
	if (y_Axis) y = 1.0;
	if (z_Axis) z = 1.0;

	if (!multiplyMatrix)
	{
		glLoadIdentity();
	}

	if (type == 0)
	{
		glColor3f(lightColor, 0.0, darkColor);
		for (int i = 0; i < 5; i++)
		{

			glTranslatef(centreX, centreY, 0.0);
			glRotatef(rotation, x, y, z);
			glTranslatef(-centreX, -centreY, 0.0);
			drawAsteroidType1(radius, centreX, centreY);
			rotation = 20.0;

		}
		glColor3f(0.0, darkColor, lightColor);
		drawCircle(10, centreX, centreY);
		drawCircle(20, centreX, centreY);
		drawCircle(30, centreX, centreY);

	}
	else if (type == 1)
	{
		glColor3f(lightColor, lightColor, darkColor);
		for (int i = 0; i < 2; i++)
		{
			glTranslatef(centreX, centreY, 0.0);
			glRotatef(rotation, x, y, z);
			glTranslatef(-centreX, -centreY, 0.0);
			drawAsteroidType1(radius, centreX, centreY);
			rotation = 45.0;

		}

			rotation = 10;
			glColor3f(0.0, darkColor, lightColor);
			glTranslatef(centreX, centreY, 0.0);
			glRotatef(rotation, x, y, 1.0);
			glTranslatef(-centreX, -centreY, 0.0);
			drawCircle(10, centreX, centreY);

	}
	else if (type == 2)
	{
		glColor3f(0.0, lightColor, darkColor);
		for (int j = 0; j < 3; j++)
		{
			glTranslatef(centreX, centreY, 0.0);
			glRotatef(rotation, x, y, z);
			glTranslatef(-centreX, -centreY, 0.0);
			drawAsteroidType1(radius * 2, centreX, centreY);
			rotation = 30;
			
		}

		glColor3f(darkColor, lightColor, 0.0);
		for (int i = 0; i < 5; i++)
		{
			glTranslatef(centreX, centreY, 0.0);
			glRotatef(rotation, x, y, z);
			glTranslatef(-centreX, -centreY, 0.0);
			drawStarAsteroid(radius, centreX, centreY, 2.0);
			rotation = 20;
		}


	}
	else if (type == 3)
	{
		glColor3f(0.0, lightColor, lightColor);
		for (int i = 0; i < 3; i++)
		{
			glTranslatef(centreX, centreY, 0.0);
			glRotatef(rotation, x, y, z);
			glTranslatef(-centreX, -centreY, 0.0);
			drawPolygonAsteroid(radius, centreX, centreY, points_polygon);
			rotation = 20;
		}
		glColor3f(darkColor, 0.0, 0.0);
		drawCircle(45, centreX, centreY);
		glColor3f(darkColor, lightColor, 0.0);
		drawCircle(40, centreX, centreY);
		glColor3f(darkColor, 0.0, lightColor);
		drawCircle(30, centreX, centreY);
		drawCircle(20, centreX, centreY);
		drawCircle(10, centreX, centreY);


	}
	else if (type == 4)
	{
		glColor3f(lightColor, lightColor, darkColor);
		for (int i = 0; i < 8; i++)
		{
			glTranslatef(centreX, centreY, 0.0);
			glRotatef(rotation, x, y, z);
			glTranslatef(-centreX, -centreY, 0.0);
			drawStarAsteroid(radius, centreX, centreY, 2.0);
			rotation = 20;
		}
	}

}

void drawAsteroidType1(GLfloat radius, GLfloat x, GLfloat y)
{
	glColor3f(darkColor, lightColor, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x - radius / 2, y - radius / 2);
	glColor3f(lightColor, lightColor, 0.0);
	glVertex2f(x - radius / 2, y + radius / 2);
	glColor3f(0.3 + darkColor, darkColor, 0.0);
	glVertex2f(x + radius / 2, y + radius / 2);
	glColor3f(0.3 + darkColor, 0.0, 0.0);
	glVertex2f(x + radius / 2, y - radius / 2);
	glEnd();

	glColor3f(darkColor, 0.3, lightColor);
	drawCircle(20, x - radius / 2, y - radius / 2);
	drawCircle(20, x - radius / 2, y + radius / 2);
	drawCircle(20, x + radius / 2, y + radius / 2);
	drawCircle(20, x + radius / 2, y - radius / 2);

	glFlush();
}

void drawAsteroidType2(GLfloat radius, GLfloat x, GLfloat y) /// triangular
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x - radius / 2, y);
	glVertex2f(x, y - radius / 2);
	glVertex2f(x + radius / 2, y);
	glEnd();
}

void drawShip(GLfloat X, GLfloat Y)
{
	///// Drawing a Complex Airship Uisng Differernt Polygons

	drawTriangle(X, Y);

	glColor3f(0.0, lightColor, darkColor);
	glRectf(X - (40.0 + 20), Y + 30, X + ((40 / 4) * 3), Y + 30 + 15);
	glRectf(X - (40.0 + 20), Y - 30, X + ((40 / 4) * 3), Y - (30 + 15));

	glColor3f(0.0, darkColor, lightColor);

	glBegin(GL_LINE_STRIP);
	glVertex2f(X - 40.0, Y + (30.0 / 2));
	glVertex2f(X - (40.0 + 20), Y + (30.0 / 2));
	glVertex2f(X - (40.0 + 40), Y + (30.0 / 4));
	glVertex2f(X - (40.0 + 40), Y - (30.0 / 4));
	glVertex2f(X - (40.0 + 20), Y - (30.0 / 2));
	glVertex2f(X - (40.0 + 20), Y - (30.0 / 2));
	glVertex2f(X - 40.0, Y - (30.0 / 2));
	glEnd();

	glColor3f(0.5 + darkColor, 0.0, 0.0);
	glRectf(X - (40.0 / 2), Y - (30 / 2), X + (40 / 4), Y + (30 / 2));

	// Left Wing
	glColor3f(0.3 + darkColor, lightColor, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(X + (40 / 4), Y + (30 / 3));
	glVertex2f(X - 35.0, Y + (30.0 * 2.0)); // 1st vertex
	glColor3f(darkColor, lightColor, 0.0);
	glVertex2f(X - (40.0 + 40), Y + (30.0 * 1.5)); // 2nd vertex
	glColor3f(darkColor, lightColor, 0.0);
	glVertex2f(X - 40.0, Y + 20.0);   // 3rd vertex
	glEnd();

	glColor3f(0.3 + darkColor, lightColor, 0.0);
	// Right Wing
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(X + (40 / 4), Y - (30 / 3));
	glVertex2f(X - 35.0, Y - (30.0 * 2.0)); // 1st vertex
	glColor3f(darkColor, lightColor, 0.0);
	glVertex2f(X - (40.0 + 40), Y - (30.0 * 1.5)); // 2nd vertex
	glColor3f(darkColor, lightColor, 0.0);
	glVertex2f(X - 40.0, Y - 20.0);  // 3rd vertex
	glEnd();

	glColor3f(0.0, darkColor, lightColor);
	drawCircle(20.0, X - 40, Y);
	drawCircle(20.0, X - 35.0, Y + (30.0 * 2.0));
	drawCircle(10.0, X - 35.0, Y + (30.0 * 2.0));
	drawCircle(20.0, X - 35.0, Y - (30.0 * 2.0));
	drawCircle(10.0, X - 35.0, Y - (30.0 * 2.0));

	glFlush();
}

//// is only called triangle nut is the basic body of the ship and it a shape of a triangle
void drawTriangle(GLfloat X, GLfloat Y)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(X - 40.0, Y + 30.0);
	glVertex2f(X - 40.0, Y - 30.0);
	glVertex2f(X + 40.0, Y + 0.0);
	glEnd();
}

void keyInput(unsigned char key, int x, int y)
{
	if (rotation > 360)
	{
		rotation = 0;
	}

	if (rotation < 0)
	{
		rotation = 360;
	}

	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case 'd':
		rotation -= 10.0;
		break;
	case 'a':
		rotation += 10.0;
		break;
		
	case 32: /// ASCII for SPACEBAR used to fire 


		if (attackON == false && saveMissleOrigin == false)
		{
			missleRotation = rotation;
			if (saveMissleOrigin == false)
			{
				attackON = true;
				saveMissleOrigin = true;
			}
		}
		break;
	}
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	glClear(GL_COLOR_BUFFER_BIT);

	asteroidRotation += 0.5;
	if (angle > 360) angle = 0;

	glutPostRedisplay();
	glutTimerFunc(5, TimerFunction, 0);
}

void controlMissles(int value)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (attackON == true)
	{
		missleX += movementBulletX / 10;
		missleY += movementBulletY / 10;

		if (missleX >= 640 || missleX <= -640 || missleY >= 640 || missleY <= -640)  // for now works fine the last bug doesn't appaer as test 2
		{
			resetRocketPropertires();
		}

	}
	
	glutPostRedisplay();
	glutTimerFunc(25, controlMissles, 0);
}

void TimerForColors(int value)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (lightColor >= 1.0)
	{
		colorDensity0 = -0.05;
	}
	if (lightColor <= 0.0)
	{
		colorDensity0 = 0.05;
	}
	lightColor += colorDensity0;

	if (darkColor >= 1.0)
	{
		colorDensity1 = -0.01;
	}
	if (darkColor <= 0.1)
	{
		colorDensity1 = 0.01;
	}
	darkColor += colorDensity1;
	glutPostRedisplay();
	glutTimerFunc(100, TimerForColors, 0);
}
void resetRocketPropertires(void)
{
	attackON = false;
	saveMissleOrigin = false;
	missleX = 0;
	missleY = 0;
	movementBulletX = 0;
	movementBulletY = 0;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);     /* window will be cleared to red */
}
void createMenu(GLint id)
{
	if (id == 1)
	{
		fly_Active = true;
		grid_Active = false;
		grid2_Active = false;
		space_Active = false;
	}
	else if (id == 2)
	{
		fly_Active = false;
		grid_Active = true;
		grid2_Active = false;
		space_Active = false;
	}
	else if (id == 3)
	{
		fly_Active = false;
		grid_Active = false;
		grid2_Active = true;
		space_Active = false;
	}
	else
	{
		fly_Active = false;
		grid_Active = false;
		grid2_Active = false;
		space_Active = true;
	}
	glutPostRedisplay();
}
void printInteraction(void)
{
	cout << "======================= " << endl;
	cout << "= WELCOME TO ASTEROID = " << endl
		<< "======================= " << endl
		<< "" << endl
		<< "" << endl;
	cout << " - Instruction Of The Game: - " << endl;
	cout << " " << endl;
	cout << " " << endl;
	cout << " 1) Press A to rotate the ship left or D to rotate right " << endl;
	cout << " " << endl;
	cout << " 2) Press the space bar to shoot rockets " << endl;
	cout << " " << endl;
	cout << " 3) right Click For Menu Options " << endl;
}
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	/* window width = 640 pixels, height = 480 pixels for a 4:3 ascpect ratio */
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Asteroid Remix");

	init();

	//Create Menu
	glutCreateMenu(createMenu);
	glutAddMenuEntry("Grid ON", 1);
	glutAddMenuEntry("Pattern ON", 2);
	glutAddMenuEntry("Grid 2 ON", 3);
	glutAddMenuEntry("Space ON", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutKeyboardFunc(keyInput);
	glutDisplayFunc(display);

	glutReshapeFunc(reshape);
	glutTimerFunc(5, TimerFunction, 0);
	glutTimerFunc(1, controlMissles, 0);
	glutTimerFunc(10, TimerForColors, 0);
	glutMainLoop();
	return 0;
}