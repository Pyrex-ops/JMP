#include "WifiPasswordGetter.hpp"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

DNSServer dnsServer;

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
    uint32_t TIMEOUT_CONNECTION_ATTEMPT_MILLIS = 3000;
    bool connected = false;
    uint32_t time_passed_milliseconds = 0;
    WiFi.begin(ssid.c_str(), password.c_str());
    /*
        A volte il wifi status resta WL_DISCONNECTED indefinitamente. 
        Il timeout impedisce un loop infinito in questo caso.
    */
    while(WiFi.status()==WL_DISCONNECTED && time_passed_milliseconds<TIMEOUT_CONNECTION_ATTEMPT_MILLIS) {
        /*
            Alimento il watchdog. Very bad, ma necessario perché 
            async_tcp proibisce l'utilizzo di delay nelle callback.
        */
        TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
        TIMERG0.wdt_feed=1;
        TIMERG0.wdt_wprotect=0;
        delay(500);
        time_passed_milliseconds += 500;
    }
    while (WiFi.status()!=WL_CONNECT_FAILED && WiFi.status()!=WL_DISCONNECTED && WiFi.status()!=WL_CONNECTED) {
        delay(500);
        /*
            Vedi sopra.
        */
        TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
        TIMERG0.wdt_feed=1;
        TIMERG0.wdt_wprotect=0;

    }
    if(WiFi.status()==WL_CONNECTED) {
        connected = true;
    }
    WiFi.disconnect(false, false);
    return connected;
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
            <input type="password" name="password" id="password">
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

const char CAPTIVE_PAGE[] PROGMEM = R"rawliteral(
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
    <h1>Pagina non trovata</h1>
    Per connettere la corda al wifi visita <a href='http:///8.8.8.8'>questa pagina</a>.</p>
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

    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
    server.begin();
}

wifi_configuration_t WifiPasswordGetter::getWifiConfiguration() {
    start_wifi();
    wifi_configuration_t wifi_conf;
    while(WifiPasswordGetter::wifi_config == nullptr) {
        dnsServer.processNextRequest(); 
        delay(100);
    }
    wifi_conf = *WifiPasswordGetter::wifi_config;
    delete(WifiPasswordGetter::wifi_config);
    stop_wifi();
    return wifi_conf;
}

void WifiPasswordGetter::stop_wifi(){
    delay(500);
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    server.end(); //Interrompiamo il Web Server
}

CaptiveRequestHandler::CaptiveRequestHandler() {}

CaptiveRequestHandler::~CaptiveRequestHandler() {}
bool CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request){
  //request->addInterestingHeader("ANY");
  return true;
}
void CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request) {
  request->redirect("http://smart.rope/");
}