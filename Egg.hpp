/*
 * Egg.hpp
 *
 *  Created on: 30 paź 2018
 *      Author: darek
 */

#include "gl/glut.h"
#include "Point3.hpp"
#include <cmath>
#include <ctime>

float pi = 3.14159265359;

class Egg {
	Point3** matrix;
	int n;
	int model;

public:
	Egg(int n = 50) :
			matrix(new Point3*[n]), n(n), model(1) {
		for (int i = 0; i < n; i++)
			matrix[i] = new Point3[n];
		generateMatrix();
	}
	~Egg() {
		for (int i = 0; i < this->n; i++)
			delete[] matrix[i];
	}

	void setModel(int model) {
		this->model = model;
	}

	void draw() {
		glColor3f(1.0f, 1.0f, 1.0f);
		if (model == 4) //Białe z wektorami normalnymi
		{
			for (int u = 0; u < n; u++) {
				int next_u = u == n - 1 ? 0 : u + 1;
				if (next_u == 0) continue;
				for (int v = 0; v < n; v++) {
					int next_v = v == n - 1 ? 0 : v + 1;
					if (next_v == 0) continue;

					glBegin(GL_TRIANGLES);
					if (u < n / 2) {
						glNormal3f(matrix[u][v].nx, matrix[u][v].ny, matrix[u][v].nz);
						glTexCoord2f(matrix[u][v].u, matrix[u][v].v);
						glVertex3f(matrix[u][v].x, matrix[u][v].y, matrix[u][v].z);

						glNormal3f(matrix[next_u][v].nx, matrix[next_u][v].ny, matrix[next_u][v].nz);
						glTexCoord2f(matrix[next_u][v].u, matrix[next_u][v].v);
						glVertex3f(matrix[next_u][v].x, matrix[next_u][v].y,
							matrix[next_u][v].z);

						glNormal3f(matrix[next_u][next_v].nx, matrix[next_u][next_v].ny, matrix[next_u][next_v].nz);
						glTexCoord2f(matrix[next_u][next_v].u, matrix[next_u][next_v].v);
						glVertex3f(matrix[next_u][next_v].x,
							matrix[next_u][next_v].y, matrix[next_u][next_v].z);

						glNormal3f(matrix[next_u][next_v].nx, matrix[next_u][next_v].ny, matrix[next_u][next_v].nz);
						glTexCoord2f(matrix[next_u][next_v].u, matrix[next_u][next_v].v);
						glVertex3f(matrix[next_u][next_v].x,
							matrix[next_u][next_v].y, matrix[next_u][next_v].z);

						glNormal3f(matrix[u][next_v].nx, matrix[u][next_v].ny, matrix[u][next_v].nz);
						glTexCoord2f(matrix[u][next_v].u, matrix[u][next_v].v);
						glVertex3f(matrix[u][next_v].x, matrix[u][next_v].y,
							matrix[u][next_v].z);

						glNormal3f(matrix[u][v].nx, matrix[u][v].ny, matrix[u][v].nz);
						glTexCoord2f(matrix[u][v].u, matrix[u][v].v);
						glVertex3f(matrix[u][v].x, matrix[u][v].y, matrix[u][v].z);
					}
					else
					{
						glNormal3f(matrix[next_u][next_v].nx, matrix[next_u][next_v].ny, matrix[next_u][next_v].nz);
						glTexCoord2f(matrix[next_u][next_v].u, matrix[next_u][next_v].v);
						glVertex3f(matrix[next_u][next_v].x,
							matrix[next_u][next_v].y, matrix[next_u][next_v].z);

						glNormal3f(matrix[next_u][v].nx, matrix[next_u][v].ny, matrix[next_u][v].nz);
						glTexCoord2f(matrix[next_u][v].u, matrix[next_u][v].v);
						glVertex3f(matrix[next_u][v].x, matrix[next_u][v].y,
							matrix[next_u][v].z);

						glNormal3f(matrix[u][v].nx, matrix[u][v].ny, matrix[u][v].nz);
						glTexCoord2f(matrix[u][v].u, matrix[u][v].v);
						glVertex3f(matrix[u][v].x, matrix[u][v].y, matrix[u][v].z);

						glNormal3f(matrix[u][v].nx, matrix[u][v].ny, matrix[u][v].nz);
						glTexCoord2f(matrix[u][v].u, matrix[u][v].v);
						glVertex3f(matrix[u][v].x, matrix[u][v].y, matrix[u][v].z);

						glNormal3f(matrix[u][next_v].nx, matrix[u][next_v].ny, matrix[u][next_v].nz);
						glTexCoord2f(matrix[u][next_v].u, matrix[u][next_v].v);
						glVertex3f(matrix[u][next_v].x, matrix[u][next_v].y,
							matrix[u][next_v].z);

						glNormal3f(matrix[next_u][next_v].nx, matrix[next_u][next_v].ny, matrix[next_u][next_v].nz);
						glTexCoord2f(matrix[next_u][next_v].u, matrix[next_u][next_v].v);
						glVertex3f(matrix[next_u][next_v].x,
							matrix[next_u][next_v].y, matrix[next_u][next_v].z);
					}
					glEnd();
				}
			}
		}
		else if (model == 3) //Trójkąty
				{
			for (int u = 0; u < n; u++) {
				int next_u = u == n - 1 ? 0 : u + 1;
				if (next_u == 0) continue;
				for (int v = 0; v < n; v++) {
					int next_v = v == n - 1 ? 0 : v + 1;
					if (next_v == 0) continue;

					glBegin(GL_TRIANGLES);

					glColor3f(matrix[u][v].r, matrix[u][v].g, matrix[u][v].b);
					glVertex3f(matrix[u][v].x, matrix[u][v].y, matrix[u][v].z);

					glColor3f(matrix[u][next_v].r, matrix[u][next_v].g,
							matrix[u][next_v].b);
					glVertex3f(matrix[u][next_v].x, matrix[u][next_v].y,
							matrix[u][next_v].z);

					glColor3f(matrix[next_u][next_v].r,
							matrix[next_u][next_v].g, matrix[next_u][next_v].b);
					glVertex3f(matrix[next_u][next_v].x,
							matrix[next_u][next_v].y, matrix[next_u][next_v].z);

					glColor3f(matrix[u][v].r, matrix[u][v].g, matrix[u][v].b);
					glVertex3f(matrix[u][v].x, matrix[u][v].y, matrix[u][v].z);

					glColor3f(matrix[next_u][v].r, matrix[next_u][v].g,
							matrix[next_u][v].b);
					glVertex3f(matrix[next_u][v].x, matrix[next_u][v].y,
							matrix[next_u][v].z);

					glColor3f(matrix[next_u][next_v].r,
							matrix[next_u][next_v].g, matrix[next_u][next_v].b);
					glVertex3f(matrix[next_u][next_v].x,
							matrix[next_u][next_v].y, matrix[next_u][next_v].z);

					glEnd();
				}
			}
		} else if (model == 2) //Linie
				{
			for (int u = 0; u < n; u++) {
				int next_u = u == n - 1 ? 0 : u + 1;
				if (next_u == 0) continue;
				for (int v = 0; v < n; v++) {
					int next_v = v == n - 1 ? 0 : v + 1;
					if (next_v == 0) continue;
					/*if (v != n - 1) {
						next_v = u + 1;
					}
					else {
						next_v = 0;
					}*/

					glBegin(GL_LINES);
					glVertex3f(matrix[u][v].x, matrix[u][v].y, matrix[u][v].z);
					glVertex3f(matrix[u][next_v].x, matrix[u][next_v].y,
							matrix[u][next_v].z);

					glVertex3f(matrix[u][next_v].x, matrix[u][next_v].y,
							matrix[u][next_v].z);
					glVertex3f(matrix[next_u][next_v].x,
							matrix[next_u][next_v].y, matrix[next_u][next_v].z);

					glVertex3f(matrix[next_u][next_v].x,
							matrix[next_u][next_v].y, matrix[next_u][next_v].z);
					glVertex3f(matrix[next_u][v].x, matrix[next_u][v].y,
							matrix[next_u][v].z);

					glVertex3f(matrix[u][v].x, matrix[u][v].y, matrix[u][v].z);
					glVertex3f(matrix[next_u][next_v].x,
							matrix[next_u][next_v].y, matrix[next_u][next_v].z);
					glEnd();
				}
			}
		} else //Punkty
		{
			for (int u = 0; u < n; u++) {
				for (int v = 0; v < n; v++) {
					glBegin(GL_POINTS);
					glVertex3f(matrix[u][v].x, matrix[u][v].y, matrix[u][v].z);
					glEnd();
				}
			}
		}
	}

private:
	float randFloat() {
		return (float) rand() / (float) RAND_MAX;
	}

	void generateMatrix() {
		for (int i = 0; i < n; i++) {
			float u = (float)i / ((float)n - 1);
			for (int j = 0; j < n; j++) {
				float v = (float)j / ((float)n - 1);

				float x = (-90 * pow(u, 5) + 225 * pow(u, 4)
					- 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u)
					* cos(pi * v);
				float y = (160 * pow(u, 4) - 320 * pow(u, 3)
					+ 160 * pow(u, 2)) - 5;
				float z = (-90 * pow(u, 5) + 225 * pow(u, 4)
					- 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u)
					* sin(pi * v);
				
				matrix[i][j].x = x;
				matrix[i][j].y = y;
				matrix[i][j].z = z;

				float xu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * cos(pi*v);
				float xv = pi * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * sin(pi*v);
				float yu = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * u;
				float yv = 0;
				float zu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45)*sin(pi*v);
				float zv = -pi * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * cos(pi*v);

				float nx = yu * zv - zu * yv;
				float ny = zu * xv - xu * zv;
				float nz = xu * yv - yu * xv;

				float length = vectorLength(nx, ny, nz);
				nx /= length;
				ny /= length;
				nz /= length;
				if (i >= n / 2) {
					nx *= -1;
					ny *= -1;
					nz *= -1;
				}
				matrix[i][j].setNormalVector(nx, ny, nz);
				matrix[i][j].setParamCoord(u, v);
				matrix[i][j].setColor(randFloat(), randFloat(), randFloat());
			}
		}
	}

	float vectorLength(float x, float y, float z) {
		return sqrt(x*x + y*y + z*z);
	}
};