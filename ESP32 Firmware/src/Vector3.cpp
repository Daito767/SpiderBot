#include "Vector3.h"
#include <cmath>

Vector3::Vector3() : _x(0), _y(0), _z(0) {}

Vector3::Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}

float Vector3::x() const { return _x; }
float Vector3::y() const { return _y; }
float Vector3::z() const { return _z; }

void Vector3::setX(float x) { _x = x; }
void Vector3::setY(float y) { _y = y; }
void Vector3::setZ(float z) { _z = z; }

float Vector3::length() const {
	return std::sqrt(_x * _x + _y * _y + _z * _z);
}

Vector3 Vector3::normalized() const {
	float len = length();
	return Vector3(_x / len, _y / len, _z / len);
}

float Vector3::dot(const Vector3& other) const {
	return _x * other.x() + _y * other.y() + _z * other.z();
}

Vector3 Vector3::cross(const Vector3& other) const {
	float cx = _y * other.z() - _z * other.y();
	float cy = _z * other.x() - _x * other.z();
	float cz = _x * other.y() - _y * other.x();
	return Vector3(cx, cy, cz);
}

bool Vector3::areAdjacent(const Vector3& other, float tolerance) const{
	float distance = (*this - other).length();

	// If the distance is less than or equal to the tolerance, return true
	if(distance <= tolerance) {
		return true;
	}

	// Otherwise, return false
	return false;
}

void Vector3::printToSerial(){
	Serial.print(_x);
	Serial.print(" ");
	Serial.print(_y);
	Serial.print(" ");
	Serial.println(_z);
}

Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(_x + other.x(), _y + other.y(), _z + other.z());
}

Vector3 Vector3::operator-(const Vector3& other) const {
	return Vector3(_x - other.x(), _y - other.y(), _z - other.z());
}

Vector3 Vector3::operator*(const Vector3& other) const {
	return Vector3(_x * other.x(), _y * other.y(), _z * other.z());
}

bool Vector3::operator==(const Vector3& other) const {
	return _x == other.x() && _y == other.y() && _z == other.z();
}

bool Vector3::operator!=(const Vector3& other) const {
	return !(*this == other);
}

Vector3 Vector3::operator*(float scalar) const {
	return Vector3(_x * scalar, _y * scalar, _z * scalar);
}

Vector3 Vector3::operator/(float scalar) const {
	assert(scalar != 0);  // Prevent division by zero
	return Vector3(_x / scalar, _y / scalar, _z / scalar);
}