#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <queue>
#include "Command.h"
#include "Telemetry/CommandQueue.h"

class Telemetry {
public:
	Telemetry(const char* host, uint16_t port); // pass CommandQueue as a parameter

	// Run data exchange with the server
	void runDataExchange();

	// Add a log entry to the logs list
	void addLog(const String& logEntry);

	// Add a report to the reports list
	void addReport(const String& key, const String& value);

	// Returns true if there is at least one command in the queue, false otherwise.
	bool isAvailableCommand();

	// Returns the next command in the list
	bool tryGetCommand(Command& cmd);

private:
	WiFiClient client;

	const char* serverHost;
	uint16_t serverPort;

	std::shared_ptr<CommandQueue> commandQueue;

	JsonArray logs;
	JsonObject reports;

	StaticJsonDocument<512> jsonBuffer;

	// Connect to the server
	int connect();

	// Disconnect from the server
	void disconnect();

	// Send data to the server
	void sendData(String data);

	// Receive data from the server
	String receiveData();

	// eserialize incoming commands
	void deserializeCommands(String jsonData);

	// Get the serialized JSON buffer
	String getSerializedJsonBuffer();

	// Clear datasets
	void clearDataSets();
};

#endif // TELEMETRY_H