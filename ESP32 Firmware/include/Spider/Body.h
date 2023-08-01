// Body.h
#ifndef BODY_H
#define BODY_H

#include <vector>
#include "Leg.h"
#include "Vector3.h"
#include "Servo.h"

class Body {
public:
	// Constructor, initializes body with lengths of the leg sections
	Body(double coxaLength, double femurLength, double tibiaLength, double stepLength, double stepHight);

	~Body();

	// Adds a leg to the body at the specified pins and initial position
	void addLeg(int coxaPin, int femurPin, int tibiaPin, bool invertCoxa, bool invertFemur, bool invertTiba, const Vector3& initialPosition);

	// Returns a reference to the vector containing the legs
	std::vector<Leg*>& getLegs();

	// Steps the body forward
	void stepForward();

	// Steps the body backward
	void stepBackward();

	// Steps the body to the right
	void stepRight();

	// Steps the body to the left
	void stepLeft();

	// Turn the body to the right
	void turnRight();

	// Turn the body to the left
	void turnLeft();

private:
	// Vector storing the legs of the body
	std::vector<Leg*> legs;

	float delayTime = 5;

	float speed = 250; // mm/s

	// Lengths of the leg sections
	double coxaLength, femurLength, tibiaLength;

	double stepLength, stepHight;

	float getMaxDistancePerCall(float speed) const;

	// Moves a specific leg to a target position relative to its current position
	void moveLeg(Leg& leg, const Vector3& relativeTarget, float speed, bool relativeToDefaultPosition = false);

	void makeStep(Leg& leg, const Vector3& target, bool relativeToDefaultPosition);

	// Moves all legs to their target positions relative to their current positions
	void setTargetForAllLegs(const Vector3& relativeTarget);

	void moveAllLegs(float speed);

	// Raises a specific leg by a certain height
	void riseLeg(Leg& leg, float speed);

	// Lowers a specific leg by a certain height
	void lowerLeg(Leg& leg, float speed);

	// Waits until a specific leg has completed its movement
	void waitMovementCompletion(Leg& leg, int spleepDelay = 1, float angleTolerance = 0.01f);
};

#endif // BODY_H
