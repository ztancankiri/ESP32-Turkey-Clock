#include "networkConnect.h"

void connectWiFi(char* ssid, char* password) {
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println();
	Serial.print("WiFi connected: ");
	Serial.println(ssid);

	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}

int bilnetLogin(String username, String password) {
	HTTPClient http;
	http.begin("https://auth.bilkent.edu.tr/auth/status");
	const char * cookieKey[] = { "Set-Cookie" };
	http.collectHeaders(cookieKey, 1);

	if (http.GET() > 0) {
		String cookie = http.header("Set-Cookie");

		http.begin("https://auth.bilkent.edu.tr/auth/login");

		const char * locationKey[] = { "Location" };
		http.collectHeaders(locationKey, 1);

		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		http.addHeader("Cookie", cookie);

		int resCode = http.POST("next=%2Fauth%2Fstatus&UserName=" + username + "&Password=" + password + "&agree=on");
		if (resCode > 0) {
			String location = http.header("Location");
			return location.equals("/auth/status") ? 1 : 0;
		}
		else
			return -1;
	}
	else
		return -1;
		
	return -1;
}