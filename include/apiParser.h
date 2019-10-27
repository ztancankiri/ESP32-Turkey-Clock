#ifndef apiParser_h
#define apiParser_h

#include <Arduino.h>
#include <HTTPClient.h>

#include "toolkit.h"

String getWANIP();
String getCity(String IP);
String getTahminIst(String city);
String getWeatherInfo(String tahminIstNo);
String getTime(String city);

#endif