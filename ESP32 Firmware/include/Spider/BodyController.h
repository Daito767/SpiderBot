#ifndef BODY_CONTROLLER_H
#define BODY_CONTROLLER_H

#include "Telemetry/Telemetry.h"
#include "Spider/Body.h"
#include "Telemetry/Command.h"

class BodyController {
public:
	// Constructor
	BodyController(Telemetry& telemetry, Body& body);

	// Function to execute commands and move the body accordingly
	void runBodyTelemetry();

private:
	Telemetry& telemetry;
	Body& body;

	// Function to process the commands
	void processCommands(Command command);
	void moveBody();
};

#endif // BODY_CONTROLLER_H
