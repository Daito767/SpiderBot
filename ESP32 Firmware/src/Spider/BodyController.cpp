#include "Spider/BodyController.h"

// Constructor
BodyController::BodyController(Telemetry& telemetry, Body& body)
	: telemetry(telemetry), body(body) {
}

// Function to execute commands and move the body accordingly
void BodyController::runBodyTelemetry() {
	while (true) {
		Command cmd;

		if (telemetry.tryGetCommand(cmd))
		{
			processCommands(cmd);
		}

		delay(50);
	}
}

// Function to process the commands
void BodyController::processCommands(Command command) {
	
	if (command.type == "step_front")
	{
		body.stepForward();
	}
	else if (command.type == "step_back")
	{
		body.stepBackward();
	}
	else if (command.type == "step_right")
	{
		body.stepRight();
	}
	else if (command.type == "step_left")
	{
		body.stepLeft();
	}
	else if (command.type == "turn_right")
	{
		body.turnRight();
	}
	else if (command.type == "turn_left")
	{
		body.turnLeft();
	}
}
