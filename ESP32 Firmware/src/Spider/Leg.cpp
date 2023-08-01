#include "Spider/Leg.h"

Leg::Leg(double coxaLength, double femurLength, double tibiaLength)
	: coxaLength(coxaLength), femurLength(femurLength), tibiaLength(tibiaLength) {
}

void Leg::setInversions(bool invertCoxa, bool invertFemur, bool invertTiba){
	this->invertCoxa = invertCoxa;
	this->invertFemur = invertFemur;
	this->invertTiba = invertTiba;
}

void Leg::attach(int coxaPin, int femurPin, int tibiaPin) {
	this->coxaPin = coxaPin;
	this->femurPin = femurPin;
	this->tibiaPin = tibiaPin;
	
	coxaServo.attach(coxaPin);
	femurServo.attach(femurPin);
	tibiaServo.attach(tibiaPin);
}

void Leg::detach() {
	coxaServo.detach();
	femurServo.detach();
	tibiaServo.detach();
}

void Leg::setAngles(int coxaAngle, int femurAngle, int tibiaAngle) {
	//Serial.print("[-^-]Leg angles: ");

	//Serial.print(coxaAngle);
	//Serial.print(" ");

	//Serial.print(femurAngle);
	//Serial.print(" ");

	//Serial.print(tibiaAngle);
	//Serial.println("");

	coxaServo.write(coxaAngle);
	femurServo.write(femurAngle);
	tibiaServo.write(tibiaAngle);
}

void Leg::getAngles(int& coxaAngle, int& femurAngle, int& tibiaAngle) {
	coxaAngle = coxaServo.read();
	femurAngle = femurServo.read();
	tibiaAngle = tibiaServo.read();
}

void Leg::setDefaultPosition(const Vector3& pos) {
	//Serial.print("[-+-] Old defaultPosition: ");
	//defaultPosition.printToSerial();

	defaultPosition = pos;

	//Serial.print("[-+-] New defaultPosition: ");
	//defaultPosition.printToSerial();
}

Vector3 Leg::getDefaultPosition() const {
	return defaultPosition;
}

void Leg::setPosition(const Vector3& pos) {
	//Serial.print("[---] Old position: ");
	//position.printToSerial();

	position = pos;

	//Serial.print("[---] New position: ");
	//position.printToSerial();

	updateAngles();
}

Vector3 Leg::getPosition() const {
	return position;
}

void Leg::setTargetPosition(const Vector3& pososition) {
	// Serial.print("[->-] Old targetPosition: ");
	// targetPosition.printToSerial();

	targetPosition = pososition;
	std::tie(targetCoxaAngle, targetFemurAngle, targetTibiaAngle) = calculateAngles(targetPosition);

	// Serial.print("[->-] New targetPosition: ");
	// targetPosition.printToSerial();
}

void Leg::setRelativeTargetPosition(const Vector3& direction, bool relativeToDefaultPosition) {
	Vector3 referencePosition = relativeToDefaultPosition ? defaultPosition : position;
	setTargetPosition(referencePosition + direction);
}

void Leg::setRelativeTargetPositionByDirection(float stepSize, const Vector3& direction, bool relativeToDefaultPosition) {
	Vector3 referencePosition = relativeToDefaultPosition ? defaultPosition : position;
	setTargetPosition(referencePosition + direction * stepSize);
}

float Leg::getDistanceToTarget() const {
	return (targetPosition - position).length();
}

Vector3 Leg::getTargetPosition() const {
	return targetPosition;
}

bool Leg::isAtTargetPosition(float tolerance) const {
	return position.areAdjacent(targetPosition, tolerance);
}

bool Leg::isAtDefaultPosition(float tolerance) const {
	return position.areAdjacent(defaultPosition, tolerance);
}

void Leg::moveTo(const Vector3& target) {
	setTargetPosition(target);
	setPosition(targetPosition);
}

void Leg::moveToTarget() {
	setPosition(targetPosition);
}

void Leg::moveTowardsTarget(float distance) {
	// This method will move the foot towards the target position by a certain distance
	Vector3 direction = (targetPosition - position).normalized();
	Vector3 newPosition = position + direction * distance;
	setPosition(newPosition);
}

void Leg::moveTowardsTargetSmoothly(float maxDistancePerCall) {
	// Calculate the direction to the target
	Vector3 direction = (targetPosition - position).normalized();

	// Calculate the total distance to the target
	float totalDistance = getDistanceToTarget();

	// Calculate the distance to move in this call. If the total distance
	// to the target is less than the maximum distance per call, move the
	// whole way. Otherwise, move by the maximum distance.
	float distanceToMove = totalDistance < maxDistancePerCall ? totalDistance : maxDistancePerCall;

	// Calculate the new position
	Vector3 newPosition = position + direction * distanceToMove;

	// Set the new position
	setPosition(newPosition);
}

std::tuple<int, int, int> Leg::calculateAngles(const Vector3& pos) {
	double x = position.x();
	double y = position.y();
	double z = position.z();

	// Calculate the coxa angle (degree)
	int coxaAngle = static_cast<int>(atan2(y, x) * (180 / M_PI));
	//Serial.print("[*] coxaAngle: ");
	//Serial.println(coxaAngle);

	// Calculate the distance from the coxa to the foot in the horizontal plane
	double horizontalDistance = std::sqrt(x * x + y * y);
	//Serial.print("[*] horizontalDistance: ");
	//Serial.println(horizontalDistance);

	double horizontalFemurTibaDistance = horizontalDistance - coxaLength;

	// Calculate the distance from the coxa to the foot
	double coxaToFootDistance = std::sqrt(horizontalFemurTibaDistance * horizontalFemurTibaDistance + z * z);
	//Serial.print("[*] coxaToFootDistance: ");
	//Serial.println(coxaToFootDistance);

	// Calculate the angle between the femur and tibia (radian)
	double femurTibiaAngle = acos((femurLength * femurLength + tibiaLength * tibiaLength - coxaToFootDistance * coxaToFootDistance) / (2 * femurLength * tibiaLength));
	//Serial.print("[*] femurTibiaAngle: ");
	//Serial.println(femurTibiaAngle);

	// Calculate the tibia angle (degree)
	int tibiaAngle = static_cast<int>(femurTibiaAngle * (180 / M_PI));
	//Serial.print("[*] tibiaAngle: ");
	//Serial.println(tibiaAngle);

	// Calculate the angle between the horizontal plane and the line between the coxa and the foot (radian)
	double footAngle = atan2(horizontalFemurTibaDistance, z);
	//Serial.print("[*] footAngle: ");
	//Serial.println(footAngle);

	// Calculate the angle between the femur and the line between the coxa and the foot (radian)
	double femurFootAngle = acos((femurLength * femurLength - tibiaLength * tibiaLength + coxaToFootDistance * coxaToFootDistance) / (2 * femurLength * coxaToFootDistance));
	//Serial.print("[*] femurFootAngle: ");
	//Serial.println(femurFootAngle);

	// Calculate the femur angle (degree)
	int femurAngle = static_cast<int>((footAngle + femurFootAngle) * (180 / M_PI));
	//Serial.print("[*] femurAngle: ");
	//Serial.println(femurAngle);

	return std::make_tuple(coxaAngle, femurAngle, tibiaAngle);
}

void Leg::updateAngles() {
	// Call the new calculateAngles function and store the angles in variables
	int coxaAngle, femurAngle, tibiaAngle;
	std::tie(coxaAngle, femurAngle, tibiaAngle) = calculateAngles(position);

	if (invertCoxa)
	{
		coxaAngle = 90 - coxaAngle;
	}
	else{
		coxaAngle = 90 + coxaAngle;
	}

	if (invertFemur)
	{
		femurAngle = 180 - femurAngle;
	}

	if (invertTiba)
	{
		tibiaAngle = 180 - tibiaAngle;
	}

	// Set the servo angles
	setAngles(coxaAngle, femurAngle, tibiaAngle);
}

