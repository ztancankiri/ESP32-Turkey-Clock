#ifndef networkConnect_h
#define networkConnect_h

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

void connectWiFi(char* ssid, char* password);
int bilnetLogin(String username, String password);

#endif