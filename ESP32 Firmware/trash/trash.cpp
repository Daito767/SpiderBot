// void Body::moveInDirection(const Vector3& direction) {
// 	moveTripod(0, stepSize, direction);
// 	moveTripod(2, stepSize, direction);
// 	moveTripod(1, stepSize, direction);
// 	moveTripod(3, stepSize, direction);
// }

// void Body::moveTripodLeg(int legIndex, float stepSize, const Vector3& direction) {
// 	Serial.print("Leg ");
// 	Serial.println(legIndex);

// 	Leg& leg = *legs[legIndex];

// 	setLegTargetDirection(leg, direction);

// 	while(leg.getDistanceToTarget() > 0)
// 	{
// 		leg.move(stepSize);
// 	}
// }