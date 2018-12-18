/*
 * Axes.hpp
 *
 *  Created on: 30 paź 2018
 *      Author: darek
 */

class Axes {
	float length;

public:
	Axes(float length = 5.0) :
			length(length) {

	}

	void draw() {
		glColor3f(1.0, 0.0, 0.0);  // kolor rysowania osi - czerwony
		glBegin(GL_LINES); // rysowanie osi x
		glVertex3f(-length, 0.0, 0.0);
		glVertex3f(length, 0.0, 0.0);
		glEnd();

		glColor3f(0.0, 1.0, 0.0);  // kolor rysowania - zielony
		glBegin(GL_LINES);  // rysowanie osi y
		glVertex3f(0.0, -length, 0.0);
		glVertex3f(0.0, length, 0.0);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
		glBegin(GL_LINES); // rysowanie osi z
		glVertex3f(0.0, 0.0, -length);
		glVertex3f(0.0, 0.0, length);
		glEnd();
	}

	void setSize(float size) {
		length = size;
	}
};
