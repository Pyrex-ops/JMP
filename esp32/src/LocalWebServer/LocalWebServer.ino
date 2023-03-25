#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "APTs";
const char* password = "SUGOMASUS";

IPAddress local_IP(192, 168, 4, 1);  //Set the IP address of ESP32 itself
IPAddress gateway(192, 168, 4, 1);   //Set the gateway of ESP32 itself
IPAddress subnet(255, 255, 255, 0);  //Set the subnet mask for ESP32 itself

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
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
    Seleziona la rete Wi-Fi a cui collegare la scheda.
    <div class="centered">
        %BUTTONPLACEHOLDER%
        <br>
        <input type="text" name="password" id="password">
    </div>
        <button class="button">OK</button>
</body>
</html>
)rawliteral";

// Sostituzione del placeholder contrassegnato con %BUTTONPLACEHOLDER%
// Gestione dei template fornita dalla libreria "ESPAsyncWebServer"
String processor(const String& var){
  if(var == "BUTTONPLACEHOLDER"){
    uint8_t n = WiFi.scanNetworks();
    if(n>0){
        String buttons = "";
        for(int i=0;i<n;i++){
            buttons += "<input type=\"radio\" id=\""+ String(i) +"\" value=\""+ WiFi.SSID(i) +"\"><label for=\""+ String(i) +"\">"+WiFi.SSID(i)+"</label><br>";
        }
        return buttons;
    }
  }
  return String();
}

void setup(){
  Serial.begin(115200);

  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  Serial.print("Setting AP (Access Point)");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.begin();
}

void loop() {

}
