#include "config.h"

#include "toolkit.h"
#include "apiParser.h"
#include "networkConnect.h"
//#include "eDisplay.h"

#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(15, 27, 26, 25));

void printText(String text);

void setup()
{
  Serial.begin(115200);
  delay(1000);

  connectWiFi(SSID, PASSWORD);
  int bilnet = bilnetLogin(BILNET_USERNAME, BILNET_PASSWORD);

  if (bilnet == 1)
  {
    Serial.println("Bil-Net Login Successful!");
  }
  else if (bilnet == 0)
  {
    Serial.println("Bil-Net Login Failed!");
  }
  else if (bilnet == -1)
  {
    Serial.println("Connection Error!");
  }

  display.init(115200);

  // *** special handling for Waveshare ESP32 Driver board *** //
  SPI.end(); // release standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  SPI.begin(13, 12, 14, 15); // map and init SPI pins SCK(13), MISO(12), MOSI(14), SS(15)
  // *** end of special handling for Waveshare ESP32 Driver board *** //

  // first update should be full refresh
  printText(String("EBS <3"));
  display.powerOff();
}

void loop()
{
  String WAN_IP = getWANIP();
  Serial.println("WAN IP: " + WAN_IP);

  String city = getCity(WAN_IP);
  Serial.println("City: " + city);

  String t = getTime(city);
  Serial.println("Time: " + t);

  String tahminIst = getTahminIst(fixTurkishLetters(city));
  String tahminIstNo = getMiddleText(tahminIst, "\"gunlukTahminIstNo\":", ",\"il\":");
  String tahmin = getWeatherInfo(tahminIstNo);

  String sicaklik = getMiddleText(tahmin, "\"sicaklik\":", ",\"veriZamani\":");
  Serial.println("Temperature: " + sicaklik + " °C");

  String hadiseKodu = getMiddleText(tahmin, "\"hadiseKodu\":", ",\"istNo\":");
  Serial.println("Event: " + eventLookup(hadiseKodu));

  String nem = getMiddleText(tahmin, "\"nem\":", ",\"rasatMetar\":");
  Serial.println("Humidity: %" + nem);

  String denizeIndirgenmisBasinc = getMiddleText(tahmin, "\"denizeIndirgenmisBasinc\":", ",\"gorus\":");
  Serial.println("Pressure: " + denizeIndirgenmisBasinc + " hPa");

  String ruzgarHiz = getMiddleText(tahmin, "\"ruzgarHiz\":", ",\"ruzgarYon\":");
  float hiz = atof(ruzgarHiz.c_str());
  Serial.println("Wind Speed: " + String(round(hiz)) + " km/h");

  String ruzgarYon = getMiddleText(tahmin, "\"ruzgarYon\":", ",\"sicaklik\":");
  Serial.println("Wind Direction: " + ruzgarYon);

  Serial.println();

  printText("Time: " + t + "\nCity: " + city + "\nTemp: " + sicaklik + "\nEvent: " + fixTurkishLetters(eventLookup(hadiseKodu)) + "\nHumidity: " + nem + "\nPressure: " + denizeIndirgenmisBasinc + "\nW. Speed: " + String(round(hiz)) + "\nW. Direction: " + ruzgarYon);

  delay(10000);
}

void printText(String text) {
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);

  const char* text_ptr = text.c_str();
  
  int16_t tbx, tby; 
  uint16_t tbw, tbh;
  display.getTextBounds(text_ptr, 0, 0, &tbx, &tby, &tbw, &tbh);
  
  //uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, y);
    display.print(text_ptr);
  }
  while (display.nextPage());
}