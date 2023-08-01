// Body.cpp
#include "Spider/Body.h"

Body::Body(double coxaLength, double femurLength, double tibiaLength, double stepLength, double stepHight)
	: coxaLength(coxaLength), femurLength(femurLength), tibiaLength(tibiaLength), stepLength(stepLength), stepHight(stepHight) {
}

Body::~Body() {
	for (auto& leg : legs) {
		delete leg;
	}
}

void Body::addLeg(int coxaPin, int femurPin, int tibiaPin, bool invertCoxa, bool invertFemur, bool invertTiba, const Vector3& initialPosition) {
	Leg* newLeg = new Leg(coxaLength, femurLength, tibiaLength);

	newLeg->attach(coxaPin, femurPin, tibiaPin);
	newLeg->setDefaultPosition(initialPosition);
	newLeg->setInversions(invertCoxa, invertFemur, invertTiba);
	newLeg->setPosition(initialPosition);

	legs.push_back(newLeg);
}

void Body::moveLeg(Leg& leg, const Vector3& relativeTarget, float speed, bool relativeToDefaultPosition) {	
	leg.setRelativeTargetPosition(relativeTarget, relativeToDefaultPosition);

	while (!leg.isAtTargetPosition()){
		leg.moveTowardsTargetSmoothly(getMaxDistancePerCall(speed));
		delay(delayTime);
	}
}

void Body::makeStep(Leg& leg, const Vector3& target, bool relativeToDefaultPosition){
	Vector3 tragetPosition = relativeToDefaultPosition? target + leg.getDefaultPosition() : target;

	if (!tragetPosition.areAdjacent(leg.getPosition(), 1))
	{
		riseLeg(leg, speed);
		moveLeg(leg, target - Vector3(0, 0, stepHight), speed, relativeToDefaultPosition);
		lowerLeg(leg, speed);
	}
}

void Body::setTargetForAllLegs(const Vector3& relativeTarget) {	
	for (auto& leg : legs) {
		leg->setRelativeTargetPosition(relativeTarget, false);
	}
}

void Body::moveAllLegs(float speed) {	
	bool allLegsAtTarget;

	do {
		allLegsAtTarget = true;

		for (auto& leg : legs) {
			if (!leg->isAtTargetPosition(1)) {
				leg->moveTowardsTargetSmoothly(getMaxDistancePerCall(speed));
				allLegsAtTarget = false;
			}
		}

		delay(delayTime);
	} while (!allLegsAtTarget);
}

void Body::riseLeg(Leg& leg, float speed){
	moveLeg(leg, Vector3(0, 0, -stepHight), speed);
}

void Body::lowerLeg(Leg& leg, float speed){
	moveLeg(leg, Vector3(0, 0, stepHight), speed);
}

float Body::getMaxDistancePerCall(float speed) const{
	return speed / 1000 * delayTime;
}

std::vector<Leg*>& Body::getLegs() {
	return legs;
}

void Body::stepForward() {
	Leg& frontLeftLeg = *legs[0];
	Leg& frontRightLeg = *legs[1];

	Leg& backLeftLeg = *legs[2];
	Leg& backRightLeg = *legs[3];

	Vector3 position(0, stepLength, 0);

	if (frontLeftLeg.isAtDefaultPosition(5)){
		Serial.println("[Move forward] Right side");

		makeStep(backRightLeg, position, true);
		makeStep(frontRightLeg, position, true);

		setTargetForAllLegs(position * -1);
		moveAllLegs(speed);
	}
	else{
		Serial.println("[Move forward] Left side");

		makeStep(backLeftLeg, position, true);
		makeStep(frontLeftLeg, position, true);

		setTargetForAllLegs(position * -1);
		moveAllLegs(speed);
	}
}

void Body::stepBackward() {
	Leg& frontLeftLeg = *legs[0];
	Leg& frontRightLeg = *legs[1];

	Leg& backLeftLeg = *legs[2];
	Leg& backRightLeg = *legs[3];

	Vector3 position(0, -stepLength, 0);

	if (backRightLeg.isAtDefaultPosition(5)){
		Serial.println("[Move forward] Left side");

		makeStep(frontLeftLeg, position, true);
		makeStep(backLeftLeg, position, true);

		setTargetForAllLegs(position * -1);
		moveAllLegs(speed);
	}
	else{
		Serial.println("[Move forward] Right side");

		makeStep(frontRightLeg, position, true);
		makeStep(backRightLeg, position, true);

		setTargetForAllLegs(position * -1);
		moveAllLegs(speed);
	}
}

void Body::stepRight() {
}

void Body::stepLeft() {
}

void Body::turnRight(){
	Leg& frontLeftLeg = *legs[0];
	Leg& frontRightLeg = *legs[1];

	Leg& backLeftLeg = *legs[2];
	Leg& backRightLeg = *legs[3];

	Vector3 position(sin(60) * 60, cos(60) * 60, 0);

	makeStep(frontRightLeg, position, true);
	makeStep(backRightLeg, position, true);

	makeStep(backLeftLeg, position * -1, true);
	makeStep(frontLeftLeg, position * -1, true);

	backRightLeg.setRelativeTargetPosition(position * -1);
	frontRightLeg.setRelativeTargetPosition(position * -1);
	backLeftLeg.setRelativeTargetPosition(position);
	frontLeftLeg.setRelativeTargetPosition(position);

	moveAllLegs(speed);
}

void Body::turnLeft(){
	Leg& frontLeftLeg = *legs[0];
	Leg& frontRightLeg = *legs[1];

	Leg& backLeftLeg = *legs[2];
	Leg& backRightLeg = *legs[3];

	Vector3 position(sin(60) * 60, cos(60) * 60, 0);

	makeStep(frontLeftLeg, position, true);
	makeStep(backLeftLeg, position, true);

	makeStep(backRightLeg, position * -1, true);
	makeStep(frontRightLeg, position * -1, true);


	backRightLeg.setRelativeTargetPosition(position);
	frontRightLeg.setRelativeTargetPosition(position);
	backLeftLeg.setRelativeTargetPosition(position * -1);
	frontLeftLeg.setRelativeTargetPosition(position * -1);

	moveAllLegs(speed);
}
