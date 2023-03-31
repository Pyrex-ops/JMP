#include "WifiPasswordGetter.hpp"

#include <WiFi.h>
#include <AsyncTCP.h>

mainpage_status_t WifiPasswordGetter::mainpage_status = NO_INPUT_YET;
wifi_configuration_t* WifiPasswordGetter::wifi_config = nullptr;

String WifiPasswordGetter::prepareAvailableWifiList(const String& var){
  if(var == "BUTTONPLACEHOLDER"){
    uint8_t n = WiFi.scanNetworks();
    if(n>0){
        String buttons = "";
        for(int i=0;i<n;i++){
            buttons += "<input type=\"radio\" name=\"SSID\" id=\""+ String(i) +"\" value=\""+ WiFi.SSID(i) +"\"";
            if(i==0) {
                buttons += " checked";
            }
            buttons += "><label for=\""+ String(i) +"\">"+WiFi.SSID(i) + "</label><br>";
        }
        return buttons;
    }
  }
  else if(var == "WARNINGPLACEHOLDER") {
    switch(WifiPasswordGetter::mainpage_status) {
        case OK:
            return "";
            break;
        case INCORRECT_PASSWORD:
            return "Password errata. Riprovare. <br>";
            break;
        case MISSING_INPUT:
            return "Compilare tutti i campi. <br>";
            break;
    }
  }
  return String();
}

bool WifiPasswordGetter::passwordCheck(const String& ssid,const String& password) {
    if(password.length() > 0)
        return true;
    return false;
}

const char* WifiPasswordGetter::MAIN_PAGE = R"rawliteral(
<!DOCTYPE html>
<html lang="it">
<head>
    <style>
        html, body { 
            font-family: Helvetica; 
            display: inline-block; 
            margin: 0px auto; 
            text-align: center;
            background-color: #181a1b;
            border-color: #736b5e;
            color: #e8e6e3;
        }
        .button { 
            background-color: #4CAF50; 
            border: none; 
            color: white; 
            padding: 8px 20px;
            text-decoration: none; 
            font-size: 25px; 
            margin: 2px; 
            cursor: pointer;
        }
        .button2 {
            background-color: #555555;
        }
        .centered{
            text-align: center;
        }
    </style>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Imposta Wi-Fi</title>
</head>
<body>
    <h1>Wi-Fi</h1>
    %WARNINGPLACEHOLDER%
    Seleziona la rete Wi-Fi a cui collegare la scheda.
    <div class="centered">
        <form action="/get">
            %BUTTONPLACEHOLDER%
            <br>
            inserisci la password:
            <br>
            <input type="text" name="password" id="password">
            <br>
            <input type="submit" value="OK">
        </form>
    </div>
</body>
</html>
)rawliteral";

const char* WifiPasswordGetter::SUCCESS_PAGE = R"rawliteral(
<!DOCTYPE html>
<html lang="it">
<head>
    <style>
        html, body { 
            font-family: Helvetica; 
            display: inline-block; 
            margin: 0px auto; 
            text-align: center;
            background-color: #181a1b;
            border-color: #736b5e;
            color: #e8e6e3;
        }
        .button { 
            background-color: #4CAF50; 
            border: none; 
            color: white; 
            padding: 8px 20px;
            text-decoration: none; 
            font-size: 25px; 
            margin: 2px; 
            cursor: pointer;
        }
        .button2 {
            background-color: #555555;
        }
        .centered{
            text-align: center;
        }
    </style>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Configurazione completata</title>
</head>
<body>
    <h1>Configurazione completata</h1>
    A breve verrai disconnesso dalla rete.
</body>
</html>
)rawliteral";

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
                server(80){
                
                    WifiPasswordGetter::mainpage_status = NO_INPUT_YET;
                    WifiPasswordGetter::wifi_config = nullptr;

                    MICROCONTROLLER_IP[0] = microcontroller_ip_0;
                    MICROCONTROLLER_IP[1] = microcontroller_ip_1;
                    MICROCONTROLLER_IP[2] = microcontroller_ip_2;
                    MICROCONTROLLER_IP[3] = microcontroller_ip_3;
                    TEMPORARY_NETWORK_GATEWAY[0] = temporary_network_gateway_0;
                    TEMPORARY_NETWORK_GATEWAY[1] = temporary_network_gateway_1;
                    TEMPORARY_NETWORK_GATEWAY[2] = temporary_network_gateway_2;
                    TEMPORARY_NETWORK_GATEWAY[3] = temporary_network_gateway_3;
                    TEMPORARY_NETWORK_SUBNET_MASK[0] = temporary_network_subnet_mask_0;
                    TEMPORARY_NETWORK_SUBNET_MASK[1] = temporary_network_subnet_mask_1;
                    TEMPORARY_NETWORK_SUBNET_MASK[2] = temporary_network_subnet_mask_2;
                    TEMPORARY_NETWORK_SUBNET_MASK[3] = temporary_network_subnet_mask_3;
}

void WifiPasswordGetter::start_wifi() {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    Serial.print("Setting AP (Access Point)");
    WiFi.softAP(TEMPORARY_NETWORK_SSID, TEMPORARY_NETWORK_PASSWORD);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", MAIN_PAGE, prepareAvailableWifiList);
    });

    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String password;
    String inputParam;
    String ssid;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam("password") && request->hasParam("SSID")) {
      password = request->getParam("password")->value();
      ssid = request->getParam("SSID")->value();
      if(passwordCheck(ssid,password)) {
        inputParam = "password";
        wifi_configuration_t* new_wifi_config;
        new_wifi_config = new wifi_configuration_t();
        new_wifi_config->password = password;
        new_wifi_config->SSID = ssid;
        wifi_config = new_wifi_config;
        request->send(200, "text/html", SUCCESS_PAGE);
      }
      else {
        WifiPasswordGetter::mainpage_status = INCORRECT_PASSWORD;
        request->redirect("/");
      }
    }
    else {
      WifiPasswordGetter::mainpage_status = MISSING_INPUT;
      request->redirect("/");
    }
    });

    server.begin();
}

wifi_configuration_t WifiPasswordGetter::getWifiConfiguration() {
    start_wifi();
    wifi_configuration_t wifi_conf;
    while(WifiPasswordGetter::wifi_config == nullptr) {
        delay(1000);
    }
    wifi_conf = *WifiPasswordGetter::wifi_config;
    delete(WifiPasswordGetter::wifi_config);
    stop_wifi();
    return wifi_conf;
}

void WifiPasswordGetter::stop_wifi(){
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
}