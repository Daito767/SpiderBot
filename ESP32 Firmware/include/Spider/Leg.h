#ifndef LEG_H
#define LEG_H

#include <Servo.h>
#include <Arduino.h>
#include <vector>
#include <cmath>
#include "Vector3.h"
#include "Servo.h"

class Leg {
public:
	Leg(double coxaLength, double femurLength, double tibiaLength);

	void attach(int coxaPin, int femurPin, int tibiaPin);
	
	void detach();

	void setInversions(bool invertCoxa, bool invertFemur, bool invertTiba);
	
	/**
	 * Sets the angles of the servos.
	 * This function will directly set the angles of the servos without any calculations.
	 * This function should be used with caution because it bypasses the foot position.
	 *
	 * @param coxaAngle The angle to set the coxa servo.
	 * @param femurAngle The angle to set the femur servo.
	 * @param tibiaAngle The angle to set the tibia servo.
	 */
	void setAngles(int coxaAngle, int femurAngle, int tibiaAngle);

	/**
	 * Gets the current angles of the servos.
	 * This function will directly read the angles of the servos.
	 *
	 * @param coxaAngle A reference to an integer where the coxa angle will be stored.
	 * @param femurAngle A reference to an integer where the femur angle will be stored.
	 * @param tibiaAngle A reference to an integer where the tibia angle will be stored.
	 */
	void getAngles(int& coxaAngle, int& femurAngle, int& tibiaAngle);

	/**
	 * Sets the default position of the foot.
	 * This position is used as a reference point for relative movements.
	 *
	 * @param pos The position to set as the default.
	 */
	void setDefaultPosition(const Vector3& position);

	/**
	 * Gets the default position of the foot.
	 *
	 * @return The default position of the foot.
	 */
	Vector3 getDefaultPosition() const;

	/**
	 * Sets the current position of the foot.
	 * It is important to note that after setting the position, the function calls `updateAngles()`. This ensures that whenever 
	 * the leg's position is updated, the joint angles are recalculated, and the leg's physical state is updated accordingly.
	 *
	 * @param pos The position to move the foot to.
	 */
	void setPosition(const Vector3& position);

	/**
	 * Gets the current position of the foot.
	 *
	 * @return The current position of the foot.
	 */
	Vector3 getPosition() const;

	/**
	 * Sets the target position of the foot for the next movement.
	 * This function will not move the foot. To move the foot, call one of the movement functions after setting the target.
	 *
	 * @param targetPosition The target position to set.
	 */
	void setTargetPosition(const Vector3& targetPosition);

	/**
	 * Sets the target position of the foot relative to the current or default position.
	 * This function will not move the foot. To move the foot, call one of the movement functions after setting the target.
	 *
	 * @param direction The direction and distance to move.
	 * @param relativeToDefaultPosition If true, the target will be relative to the default position. If false, the target will be relative to the current position.
	 */
	void setRelativeTargetPosition(const Vector3& direction, bool relativeToDefaultPosition = false);

	/**
	 * Sets the target position of the foot relative to the current or default position by a certain step size.
	 * This function will not move the foot. To move the foot, call one of the movement functions after setting the target.
	 *
	 * @param stepSize The size of the step in the direction.
	 * @param direction The direction to move.
	 * @param relativeToDefaultPosition If true, the target will be relative to the default position. If false, the target will be relative to the current position.
	 */
	void setRelativeTargetPositionByDirection(float stepSize, const Vector3& direction, bool relativeToDefaultPosition = true);

	/**
	 * Gets the current target position of the foot.
	 *
	 * @return The current target position of the foot.
	 */	
	Vector3 getTargetPosition() const;

	/**
	 * Gets the distance from the current position to the target position.
	 * 
	 * @return The distance from the current position to the target position.
	 */
	float getDistanceToTarget() const;

	bool isAtTargetPosition(float tolerance = 1) const;
	
	bool isAtDefaultPosition(float tolerance = 1) const;

	/**
	 * Sets the target position and moves the leg directly to the target.
	 *
	 * @param target A Vector3 object representing the target position.
	 */
	void moveTo(const Vector3& target);

	/**
	 * Moves the leg directly to the pre-set target position.
	 * The target position should be set beforehand using setTargetPosition() or moveTo().
	 */
	void moveToTarget();

	/**
	 * Moves the leg towards the pre-set target position by a certain distance.
	 * This function is useful for incremental movements towards the target.
	 *
	 * @param distance The distance to move towards the target.
	 */
	void moveTowardsTarget(float distance);

	/**
	 * @brief Move the leg towards the target position smoothly.
	 *
	 * This function moves the leg closer to its target position in a non-blocking manner. 
	 * It calculates the direction to the target and the total distance, and moves the leg by
	 * either the maximum distance specified or the total remaining distance, whichever is smaller.
	 * To create a smooth movement, this function should be called repeatedly in the main loop or 
	 * update function of the program. Each call will move the leg a little bit closer to the target,
	 * creating the illusion of smooth motion.
	 *
	 * @param maxDistancePerCall The maximum distance that the leg will move towards the target 
	 * per call to this function. This distance should be a small positive number.
	 */
	void moveTowardsTargetSmoothly(float maxDistancePerCall);

	/**
	 * Raises the foot by a certain height.
	 * This function changes the z-coordinate of the foot's position, and then calls updateAngles()
	 * to ensure the servos move to the correct positions.
	 *
	 * @param height The height to raise the foot by. Should be a positive value.
	 */
	//void raise(float height);

	/**
	 * Lowers the foot by a certain height.
	 * This function changes the z-coordinate of the foot's position, and then calls updateAngles()
	 * to ensure the servos move to the correct positions.
	 *
	 * @param height The height to lower the foot by. Should be a positive value.
	 */
	//void lower(float height);

private:
	int coxaPin;
	int femurPin;
	int tibiaPin;

	int targetCoxaAngle; 
	int targetFemurAngle; 
	int targetTibiaAngle;

	double coxaLength;
	double femurLength;
	double tibiaLength;

	bool invertCoxa;
	bool invertFemur;
	bool invertTiba;

	Servo coxaServo;
	Servo femurServo;
	Servo tibiaServo;

	// Position vector to store leg default position (x, y, z)
	Vector3 defaultPosition;

	// Position vector to store leg position (x, y, z)
	Vector3 position;

	// Position vector to store leg target position (x, y, z)
	Vector3 targetPosition;

	/**
	 * Updates the angles of the servos based on the current position of the foot.
	 * This function involves complex trigonometric calculations to convert the foot position
	 * in Cartesian coordinates to the appropriate angles for the servos.
	 * This function should be called whenever the foot position changes.
	 */
	void updateAngles();

	/**
	 * @brief Calculate the angles for the leg's coxa, femur, and tibia based on the input position.
	 * 
	 * This function uses the lengths of the leg's segments and the input position to calculate the necessary
	 * angles for the coxa, femur, and tibia to reach that position. The calculations take into account the 
	 * physical constraints of the leg and are based on inverse kinematics.
	 * 
	 * @param pos A Vector3 representing the target position for the leg's foot. The x, y, and z components of the
	 * vector correspond to the x, y, and z coordinates in the leg's coordinate system.
	 * 
	 * @return A std::tuple<int, int, int> containing the calculated angles for the coxa, femur, and tibia, 
	 * respectively. The angles are in degrees.
	 */
	std::tuple<int, int, int> calculateAngles(const Vector3& pos);
};

#endif // LEG_H
