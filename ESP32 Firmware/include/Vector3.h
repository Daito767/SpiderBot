#ifndef VECTOR_H
#define VECTOR_H

#include <Arduino.h>

class Vector3 {
public:
	Vector3();
	Vector3(float x, float y, float z);
	
	float x() const;
	float y() const;
	float z() const;

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float length() const;
	Vector3 normalized() const;
	bool areAdjacent(const Vector3& other, float tolerance) const;
	
	float dot(const Vector3& other) const;
	Vector3 cross(const Vector3& other) const;

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(const Vector3& other) const;
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	Vector3 operator*(float scalar) const;
	Vector3 operator/(float scalar) const;

	void printToSerial();

private:
	float _x, _y, _z;
};

#endif // VECTOR_H
