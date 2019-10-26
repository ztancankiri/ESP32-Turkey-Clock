#include "apiParser.h"

String getWANIP() {
	HTTPClient http;
	http.begin("https://api.ipify.org/");
	if (http.GET() > 0) {
		String response = http.getString();
		response.trim();
		return response;
	}
	else {
		return "";
	}
}

String getCity(String IP) {
	HTTPClient http;
	http.begin("https://ipinfo.io/" + IP + "/region");
	if (http.GET() > 0) {
		String response = http.getString();
		response.trim();
		return response;
	}
	else {
		return "";
	}
}

String getTahminIst(String city) {
	HTTPClient http;
	http.begin("https://servis.mgm.gov.tr/web/merkezler?il=" + city);
	http.addHeader("Origin", "https://www.mgm.gov.tr");

	if (http.GET() > 0) {
		String response = http.getString();
		response.trim();
		return response;
	}
	else {
		return "";
	}
}

String getWeatherInfo(String tahminIstNo) {
	HTTPClient http;
	http.begin("https://servis.mgm.gov.tr/web/sondurumlar?merkezid=" + tahminIstNo);
	http.addHeader("Origin", "https://www.mgm.gov.tr");

	if (http.GET() > 0) {
		String response = http.getString();
		response.trim();
		return response;
	}
	else {
		return "";
	}
}

String getTime(String city) {
	HTTPClient http;
	http.begin("https://time.is/" + city);

	if (http.GET() > 0) {
		String response = http.getString();
		response.trim();

		String t = getMiddleText(response, "<div id=\"twd\">", "</div>");
		return t;
	} else {
		return "";
	}
}