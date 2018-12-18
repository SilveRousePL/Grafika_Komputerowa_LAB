/*
 * Point3.hpp
 *
 *  Created on: 30 paź 2018
 *      Author: darek
 */
#pragma once

class Point3 {
public:
	float x;
	float y;
	float z;

	float nx;
	float ny;
	float nz;

	float u;
	float v;

	float r;
	float g;
	float b;

	Point3(float x = 0, float y = 0, float z = 0) :
			x(x), y(y), z(z), nx(0), ny(0), nz(0),
			//xu(0), xv(0), yu(0), yv(0), zu(0), zv(0), 
			r(1), g(1), b(1) {
	}

	void setPoint(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void setNormalVector(float x, float y, float z) {
		this->nx = x;
		this->ny = y;
		this->nz = z;
	}

	void setParamCoord(float u, float v) {
		this->u = u;
		this->v = v;
	}

	void setColor(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	float operator[](const int index) {
		if (index == 0)
			return this->x;
		if (index == 1)
			return this->y;
		if (index == 2)
			return this->z;
		return 0;
	}

	Point3 operator=(const Point3& obj) {
		return Point3(obj.x, obj.y, obj.z);
	}

	Point3 operator=(const float* obj) {
		return Point3(obj[0], obj[1], obj[2]);
	}
};
