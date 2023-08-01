#include "Telemetry/Telemetry.h"

Telemetry::Telemetry(const char* host, uint16_t port) 
	: serverHost(host), serverPort(port), commandQueue(std::make_shared<CommandQueue>()) {}

void Telemetry::runDataExchange() {
	while(true){
		if (client.connected()){
			deserializeCommands(receiveData());
			sendData(getSerializedJsonBuffer());
			
			clearDataSets();
			delay(250);
		}
		else{
			connect();
			delay(1000);
		}
	}
}

void Telemetry::addLog(const String& logEntry) {
	logs.add(logEntry);
}

void Telemetry::addReport(const String& key, const String& value) {
	reports[key] = value;
}

bool Telemetry::isAvailableCommand(){
	return commandQueue->isAvailableCommand();
}

bool Telemetry::tryGetCommand(Command& cmd) {
	return commandQueue->tryGetCommand(cmd);
}

int Telemetry::connect() {
	bool result = client.connect(serverHost, serverPort);

	if (result) Serial.println("[SUCCES] The attempt to connect to the server succeeded.");
	else Serial.println("[ERROR] The attempt to connect to the server failed.");

	return result;
}

void Telemetry::disconnect() {
	client.stop();
}

void Telemetry::sendData(String data) {
	if (data.length() > 0)
	{
		client.print(data + '\n');
	}
}

String Telemetry::receiveData() {
	String data = "";
	while(client.available()) {
		data += char(client.read());
	}

	return data;
}

void Telemetry::deserializeCommands(String jsonData) {
	// Parse the received JSON data
	DynamicJsonDocument doc(1024);
	deserializeJson(doc, jsonData);

	JsonArray commands = doc["commands"];
	for(JsonVariant command : commands) {

		Command cmd;
		cmd.type = command["type"].as<String>();
		cmd.count = command["count"];
		cmd.speed = command["speed"];

		commandQueue->addCommand(cmd);
	}
}

String Telemetry::getSerializedJsonBuffer(){
	String data;

	if (logs.size() > 0 || reports.size() > 0)
	{
		serializeJson(jsonBuffer, data);
	}

	return data;
}

void Telemetry::clearDataSets(){
	jsonBuffer.clear();
	logs = jsonBuffer.createNestedArray("logs");
	reports = jsonBuffer.createNestedObject("monitoring_report");
}
