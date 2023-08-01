#include <WiFi.h>
#include "Telemetry/Telemetry.h"
#include "Spider/Body.h"
#include "Spider/BodyController.h"

const char* ssid = "############";
const char* password = "############";
const char* hostname = "ESP32 Client";

const char* telemetryHost = "192.168.45.215";
uint16_t telemetryPort = 8070;

Telemetry telemetry(telemetryHost, telemetryPort);


//Leg lengths
const double coxaLength = 27.5;
const double femurLength = 55;
const double tibiaLength = 80;

const float stepLength = 35;
const float stepHight = 40;

// Create an instance of the Body class
Body body(coxaLength, femurLength, tibiaLength, stepLength, stepHight);

BodyController bodyController(telemetry, body);

// Task function for processing commands
void dataExchangeTask(void *parameter) {
	telemetry.runDataExchange();
}

// Task function for controlling the body
void bodyControlTask(void *parameter) {
	bodyController.runBodyTelemetry();
}

void connectToWiFi(){
	Serial.print("Connecting to ");
	Serial.println(ssid);

	// Set the hostname
	WiFi.setHostname(hostname);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected.");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.print("Hostname: ");
	Serial.println(WiFi.getHostname());
}


void setup() {
	// Initialize serial communication
	Serial.begin(115200);

	// Connect to Wi-Fi
	connectToWiFi();

	delay(3000);

	body.addLeg(2, 4, 15, true, false, true, Vector3((coxaLength + femurLength) * 0.8, 0, tibiaLength* 0.8));
	body.addLeg(13, 14, 12, false, true, false, Vector3((coxaLength + femurLength) * 0.8, 0, tibiaLength * 0.8));
	body.addLeg(16, 17, 18, true, true, false, Vector3((coxaLength + femurLength) * 0.8, 0, tibiaLength * 0.8));
	body.addLeg(25, 26, 27, false, false, true, Vector3((coxaLength + femurLength) * 0.8, 0, tibiaLength * 0.8));

	xTaskCreatePinnedToCore(dataExchangeTask, "DataExchangeTask", 10240, NULL, 5, NULL, 0);
	xTaskCreatePinnedToCore(bodyControlTask, "BodyControlTask", 10240, NULL, 5, NULL, 1);

}

void loop() {
}