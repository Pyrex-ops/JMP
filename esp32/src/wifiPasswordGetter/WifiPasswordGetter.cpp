#include "WifiPasswordGetter.hpp"
#include "CaptiveRequestHandler.hpp"

#include <WiFi.h>
#include <AsyncTCP.h>
#include "AsyncJson.h"
#include <DNSServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

DNSServer dnsServer;

mainpage_status_t WifiPasswordGetter::mainpage_status = NO_INPUT_YET;
wifi_configuration_t* WifiPasswordGetter::wifi_config = nullptr;
uint16_t WifiPasswordGetter::numberOfWifiNetworks = 0;
String* WifiPasswordGetter::candidateSSID;
String* WifiPasswordGetter::candeidatePassword;

WifiPasswordGetter::WifiPasswordGetter(
            const char* temporary_network_ssid,
            const char* temporary_network_password,
            const uint8_t microcontroller_ip_0,
            const uint8_t microcontroller_ip_1,
            const uint8_t microcontroller_ip_2,
            const uint8_t microcontroller_ip_3,
            const uint8_t temporary_network_gateway_0,
            const uint8_t temporary_network_gateway_1,
            const uint8_t temporary_network_gateway_2,
            const uint8_t temporary_network_gateway_3,
            const uint8_t temporary_network_subnet_mask_0,
            const uint8_t temporary_network_subnet_mask_1,
            const uint8_t temporary_network_subnet_mask_2,
            const uint8_t temporary_network_subnet_mask_3) :
                TEMPORARY_NETWORK_SSID(temporary_network_ssid) ,
                TEMPORARY_NETWORK_PASSWORD(temporary_network_password) ,
                MICROCONTROLLER_IP(microcontroller_ip_0,
                                    microcontroller_ip_1,
                                    microcontroller_ip_2,
                                    microcontroller_ip_3),
                TEMPORARY_NETWORK_SUBNET_MASK(temporary_network_subnet_mask_0,
                                                temporary_network_subnet_mask_1,
                                                temporary_network_subnet_mask_2,
                                                temporary_network_subnet_mask_3) ,
                    server(80){
                
                    WifiPasswordGetter::mainpage_status = NO_INPUT_YET;
                    WifiPasswordGetter::wifi_config = nullptr;

                    //MICROCONTROLLER_IP[0] = microcontroller_ip_0;
                    //MICROCONTROLLER_IP[1] = microcontroller_ip_1;
                    //MICROCONTROLLER_IP[2] = microcontroller_ip_2;
                    //MICROCONTROLLER_IP[3] = microcontroller_ip_3;
                    TEMPORARY_NETWORK_GATEWAY[0] = temporary_network_gateway_0;
                    TEMPORARY_NETWORK_GATEWAY[1] = temporary_network_gateway_1;
                    TEMPORARY_NETWORK_GATEWAY[2] = temporary_network_gateway_2;
                    TEMPORARY_NETWORK_GATEWAY[3] = temporary_network_gateway_3;
                    //TEMPORARY_NETWORK_SUBNET_MASK[0] = temporary_network_subnet_mask_0;
                    //TEMPORARY_NETWORK_SUBNET_MASK[1] = temporary_network_subnet_mask_1;
                    //TEMPORARY_NETWORK_SUBNET_MASK[2] = temporary_network_subnet_mask_2;
                    //TEMPORARY_NETWORK_SUBNET_MASK[3] = temporary_network_subnet_mask_3;
}

void WifiPasswordGetter::start_wifi() {
    WiFi.disconnect(true,true);
    WiFi.mode(WIFI_AP_STA);
    Serial.print("Setting AP (Access Point)");
    WiFi.softAP(TEMPORARY_NETWORK_SSID, TEMPORARY_NETWORK_PASSWORD);
    WiFi.softAPConfig(MICROCONTROLLER_IP, MICROCONTROLLER_IP, TEMPORARY_NETWORK_SUBNET_MASK);
    IPAddress IP = WiFi.softAPIP();
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError); 
    dnsServer.start(53, "*", IP);
    Serial.print("AP IP address: ");
    Serial.println(IP);

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", MAIN_PAGE);
    });

    server.on("/api/get-ssids", HTTP_GET, [](AsyncWebServerRequest *request){
      DynamicJsonDocument doc(250);
      char buffer[250];
        JsonArray ssids = doc.createNestedArray("ssids");
        for(int i=0;i<WifiPasswordGetter::getNumberOfWifiNetworks();i++){
            ssids.add(WiFi.SSID(i));
        }
        serializeJson(doc, buffer);
        request->send_P(200, "text/json", buffer);
    });

    server.on("/api/refresh-ssids", HTTP_GET, [](AsyncWebServerRequest *request){
        numberOfWifiNetworks = WiFi.scanNetworks();
        request->send(200, "application/json", "{\"status\": \"trying\"}");
    });

    AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/api/connect",
        [](AsyncWebServerRequest *request, JsonVariant &json){
    DynamicJsonDocument doc(250);
      StaticJsonDocument<200> data;
        if (json.is<JsonArray>())
        {
          data = json.as<JsonArray>();
        }
        else if (json.is<JsonObject>())
        {
          data = json.as<JsonObject>();
        }
        const char* ssid = data["ssid"];
        Serial.println(ssid);
        const char* password = data["password"];
        Serial.println(password);
        if(strlen(ssid)==0 || strlen(password)==0) {
            request->send(400, "application/json", "{}");
        }
        else {
            candidateSSID = new String(ssid);
            candeidatePassword = new String(password);
            WiFi.begin(ssid, password);
            request->send(200, "application/json", "{}");
        }
    });
    server.addHandler(handler);
    server.on("/api/check-status", HTTP_GET, [](AsyncWebServerRequest *request){
        switch(WiFi.status()) {
            case WL_IDLE_STATUS:
                    request->send(200, "application/json", "{\"status\": \"trying\"}");
            case WL_DISCONNECTED:
                    request->send(200, "application/json", "{\"status\": \"wrong credentials\"}");
                break;
            case WL_CONNECTED:
                    wifi_configuration_t* new_wifi_config;
                    new_wifi_config = new wifi_configuration_t();
                    new_wifi_config->password = *candidateSSID;
                    new_wifi_config->SSID = *candeidatePassword;
                    wifi_config = new_wifi_config;
                    request->send(200, "application/json", "{\"status\": \"connected\"}");
                break;
            case WL_CONNECT_FAILED:
                    request->send(200, "application/json", "{\"status\": \"wrong credentials\"}");
                break;
            default:
                    request->send(200, "application/json", "{\"status\": \"wrong credentials\"}");
                break;
        }
    });

    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
    server.begin();
}

uint16_t WifiPasswordGetter::getNumberOfWifiNetworks() {
    return numberOfWifiNetworks;
}

wifi_configuration_t WifiPasswordGetter::getWifiConfiguration() {
    start_wifi();
    wifi_configuration_t wifi_conf;
    numberOfWifiNetworks = WiFi.scanNetworks();
    while(WifiPasswordGetter::wifi_config == nullptr) {
        dnsServer.processNextRequest(); 
        delay(500);
    }
    wifi_conf = *WifiPasswordGetter::wifi_config;
    delete(WifiPasswordGetter::wifi_config);
    stop_wifi();
    Serial.println(wifi_conf.SSID);
    Serial.println(wifi_conf.password);
    return wifi_conf;
}

void WifiPasswordGetter::stop_wifi(){
    delay(500);
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    server.end(); //Interrompiamo il Web Server
}