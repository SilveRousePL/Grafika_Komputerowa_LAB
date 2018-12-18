#pragma once

#include "gl/glut.h"
#include "Point3.hpp"

class Pyramid {
	Point3 point[5];
	bool side[5];
	int n;

public:
	Pyramid(int n = 5) : n(n) {
		bool side[5] = { 1,1,1,1,1 };
		setSide(side);

		point[0].setPoint(0.0, (float)n, 0.0);
		point[1].setPoint(-(float)n, -(float)n, (float)n);
		point[2].setPoint((float)n, -(float)n, (float)n);
		point[3].setPoint((float)n, -(float)n, -(float)n);
		point[4].setPoint(-(float)n, -(float)n, -(float)n);
	}

	void draw() {
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_TRIANGLES);
		// Trójk¹t z przodu
		if (side[0]) {
			glNormal3f(point[0].x, point[0].y, point[0].z);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(point[0].x, point[0].y, point[0].z);
			glNormal3f(point[1].x, point[1].y, point[1].z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(point[1].x, point[1].y, point[1].z);
			glNormal3f(point[2].x, point[2].y, point[2].z);
			glTexCoord2f(0.5f, 1.0f);
			glVertex3f(point[2].x, point[2].y, point[2].z);
		}
		if (side[1]) {
			// Trójk¹t prawy
			glNormal3f(point[0].x, point[0].y, point[0].z);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(point[0].x, point[0].y, point[0].z);
			glNormal3f(point[2].x, point[2].y, point[2].z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(point[2].x, point[2].y, point[2].z);
			glNormal3f(point[3].x, point[3].y, point[3].z);
			glTexCoord2f(0.5f, 1.0f);
			glVertex3f(point[3].x, point[3].y, point[3].z);
		}
		if (side[2]) {
			// Trójk¹t z ty³u
			glNormal3f(point[0].x, point[0].y, point[0].z);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(point[0].x, point[0].y, point[0].z);
			glNormal3f(point[3].x, point[3].y, point[3].z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(point[3].x, point[3].y, point[3].z);
			glNormal3f(point[4].x, point[4].y, point[4].z);
			glTexCoord2f(0.5f, 1.0f);
			glVertex3f(point[4].x, point[4].y, point[4].z);
		}
		if (side[3]) {
			// Trójk¹t lewy
			glNormal3f(point[0].x, point[0].y, point[0].z);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(point[0].x, point[0].y, point[0].z);
			glNormal3f(point[4].x, point[4].y, point[4].z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(point[4].x, point[4].y, point[4].z);
			glNormal3f(point[1].x, point[1].y, point[1].z);
			glTexCoord2f(0.5f, 1.0f);
			glVertex3f(point[1].x, point[1].y, point[1].z);
		}
		glEnd();
		if (side[4]) {
			glBegin(GL_QUADS);
			glNormal3f(point[4].x, -point[4].y, point[4].z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(point[4].x, point[4].y, point[4].z);
			glNormal3f(point[3].x, -point[3].y, point[3].z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(point[3].x, point[3].y, point[3].z);
			glNormal3f(point[2].x, -point[2].y, point[2].z);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(point[2].x, point[2].y, point[2].z);
			glNormal3f(point[1].x, -point[1].y, point[1].z);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(point[1].x, point[1].y, point[1].z);
			glEnd();
		}
	}

	void setSide(bool side[5]) {
		this->side[0] = side[0];
		this->side[1] = side[1];
		this->side[2] = side[2];
		this->side[3] = side[3];
		this->side[4] = side[4];
	}

	void toggleSide(int side) {
		if (this->side[side] == false) {
			this->side[side] = true;
		}
		else {
			this->side[side] = false;
		}
	}
};