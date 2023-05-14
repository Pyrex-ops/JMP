#include "WifiPasswordGetter.hpp"
#include "CaptiveRequestHandler.hpp"

#include "AsyncJson.h"
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#include <WiFi.h>

#define DEFAULT_MICROCONTROLLER_IP \
	{ 8, 8, 8, 8 }
#define DEFAULT_TEMPORARY_NETWORK_GATEWAY \
	{ 8, 8, 8, 8 }
#define DEFAULT_TEMPORARY_NETWORK_SUBNET_MASK \
	{ 255, 255, 255, 0 }

DNSServer dnsServer;

wifi_configuration_t* WifiPasswordGetter::wifi_config = nullptr;
uint16_t WifiPasswordGetter::numberOfWifiNetworks	  = 0;
String* WifiPasswordGetter::candidateSSID;
String* WifiPasswordGetter::candidatePassword;

WifiPasswordGetter::WifiPasswordGetter(
	const char* temporary_network_ssid, const char* temporary_network_password)
	: TEMPORARY_NETWORK_SSID(temporary_network_ssid),
	  TEMPORARY_NETWORK_PASSWORD(temporary_network_password), server(80) {

	WifiPasswordGetter::wifi_config = nullptr;
}

void WifiPasswordGetter::start_wifi() {
	WiFi.disconnect(true, true);
	WiFi.mode(WIFI_AP_STA);
	WiFi.softAP(TEMPORARY_NETWORK_SSID, TEMPORARY_NETWORK_PASSWORD);
	WiFi.softAPConfig(DEFAULT_MICROCONTROLLER_IP, DEFAULT_MICROCONTROLLER_IP,
					  DEFAULT_TEMPORARY_NETWORK_SUBNET_MASK);
	IPAddress IP = WiFi.softAPIP();
	dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
	dnsServer.start(53, "*", IP);

	// Route for root / web page
	server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send_P(200, "text/html", MAIN_PAGE);
	});

	server.on("/api/get-ssids", HTTP_GET, [](AsyncWebServerRequest* request) {
		DynamicJsonDocument doc(250);
		char buffer[250];
		JsonArray ssids = doc.createNestedArray("ssids");
		for (int i = 0; i < WifiPasswordGetter::getNumberOfWifiNetworks(); i++) {
			ssids.add(WiFi.SSID(i));
		}
		serializeJson(doc, buffer);
		request->send_P(200, "text/json", buffer);
	});

	server.on("/api/refresh-ssids", HTTP_GET, [](AsyncWebServerRequest* request) {
		numberOfWifiNetworks = WiFi.scanNetworks(true);
		request->send(200, "application/json", "{}");
	});

	server.on("/api/get-wifi-scan-status", HTTP_GET, [](AsyncWebServerRequest* request) {
		if (WiFi.scanComplete() != -1 && WiFi.scanComplete() != -2) {
			request->send(200, "application/json", "{\"status\": \"completed\"}");
		} else {
			request->send(200, "application/json", "{\"status\": \"uncompleted\"}");
		}
	});

	AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler(
		"/api/connect", [](AsyncWebServerRequest* request, JsonVariant& json) {
			DynamicJsonDocument doc(250);
			StaticJsonDocument<200> data;
			if (json.is<JsonArray>()) {
				data = json.as<JsonArray>();
			} else if (json.is<JsonObject>()) {
				data = json.as<JsonObject>();
			}
			const char* ssid	 = data["ssid"];
			const char* password = data["password"];
			if (strlen(ssid) == 0 || strlen(password) == 0) {
				request->send(400, "application/json", "{}");
			} else {
				candidateSSID	  = new String(ssid);
				candidatePassword = new String(password);
				WiFi.begin(ssid, password);
				request->send(200, "application/json", "{}");
			}
		});
	server.addHandler(handler);
	server.on("/api/check-status", HTTP_GET, [](AsyncWebServerRequest* request) {
		switch (WiFi.status()) {
			case WL_IDLE_STATUS:
				request->send(200, "application/json", "{\"status\": \"trying\"}");
				break;
			case WL_DISCONNECTED:
				WiFi.disconnect();
				request->send(200, "application/json", "{\"status\": \"wrong credentials\"}");
				break;
			case WL_CONNECTED:
				wifi_configuration_t* new_wifi_config;
				new_wifi_config			  = new wifi_configuration_t();
				new_wifi_config->password = *candidatePassword;
				new_wifi_config->SSID	  = *candidateSSID;
				wifi_config				  = new_wifi_config;
				request->send(200, "application/json", "{\"status\": \"connected\"}");
				break;
			case WL_CONNECT_FAILED:
				WiFi.disconnect();
				request->send(200, "application/json", "{\"status\": \"wrong credentials\"}");
				break;
			default:
				WiFi.disconnect();
				request->send(200, "application/json", "{\"status\": \"wrong credentials\"}");
				break;
		}
	});

	server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);	 //only when requested from AP
	server.begin();
}

uint16_t WifiPasswordGetter::getNumberOfWifiNetworks() {
	return numberOfWifiNetworks;
}

wifi_configuration_t WifiPasswordGetter::getWifiConfiguration() {
	start_wifi();
	wifi_configuration_t wifi_conf;
	numberOfWifiNetworks = WiFi.scanNetworks();
	while (WifiPasswordGetter::wifi_config == nullptr) {
		dnsServer.processNextRequest();
		delay(500);
	}
	wifi_conf = *WifiPasswordGetter::wifi_config;
	delete (WifiPasswordGetter::wifi_config);
	stop_wifi();
	return wifi_conf;
}

void WifiPasswordGetter::stop_wifi() {
	delay(500);
	WiFi.disconnect();
	WiFi.mode(WIFI_STA);
	server.end();  //Interrompiamo il Web Server
}