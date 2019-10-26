#include "toolkit.h"
#include "apiParser.h"
#include "networkConnect.h"
#include "config.h"

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

  delay(10000);
}