#include "Telemetry/Monitoring.h"
#include <Arduino.h>
#include <WiFi.h>

extern "C" {
#include "esp_system.h"
}

Monitoring::Monitoring() {
}

void Monitoring::update() {
	checkMemoryUsage();
	checkRSSI();
}

void Monitoring::checkMemoryUsage() {
	uint32_t freeHeap = heap_caps_get_free_size(MALLOC_CAP_8BIT);
	Serial.print("Free heap memory: ");
	Serial.print(freeHeap);
	Serial.println(" bytes");
}

void Monitoring::checkRSSI() {
	long rssi = WiFi.RSSI();
	Serial.print("RSSI: ");
	Serial.print(rssi);
	Serial.println(" dBm");
	}

// void printRemainingStack(){
// 	UBaseType_t remainingStack = uxTaskGetStackHighWaterMark(NULL);
// 	uint32_t remainingStackBytes = remainingStack * 4;
// 	float remainingStackKB = remainingStackBytes / 1024.0f;

// 	Serial.print("Remaining stack: ");
// 	Serial.print(remainingStack);
// 	Serial.print(" words ");
// 	Serial.print(remainingStackBytes);
// 	Serial.print(" bytes (");
// 	Serial.print(remainingStackKB);
// 	Serial.println(" KB)");
// }