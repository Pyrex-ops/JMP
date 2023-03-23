// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "APTs";
const char* password = "SUGOMASUS";

IPAddress local_IP(192, 168, 4, 1);  //Set the IP address of ESP32 itself
IPAddress gateway(192, 168, 4, 1);   //Set the gateway of ESP32 itself
IPAddress subnet(255, 255, 255, 0);  //Set the subnet mask for ESP32 itself

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin(80);
  Serial.println("OK");
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {                     // If a new client connects,
    Serial.println("New Client.");  // print a message out in the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Routing nelle pagine
            if (header.indexOf("GET /") >= 0) {
              Serial.println("/");
              //Codice della route qui
              client.println("<!DOCTYPE html> <html lang=\"it\"> <head> <style> html {font-family: Helvetica;display: inline-block;margin: 0px auto;text-align: center;}.button {background-color: #4CAF50;border: none;color: white;padding: 8px 20px;text-decoration: none;font-size: 25px;margin: 2px;cursor: pointer;}.button2 {background-color: #555555;}.centered{text-align: center;}</style> <meta charset=\"UTF-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Imposta Wi-Fi</title> </head> <body> <h1>Wi-Fi</h1> Seleziona la rete Wi-Fi a cui collegare la scheda.");
              client.println("<div class=\"centered\">");
              //client.println("<input type=\"radio\" id=\"UNO\" name=\"fav_language\" value=\"UNO\"> <label for=\"UNO\">UNO</label><br>");
              uint8_t n = WiFi.scanNetworks();
              Serial.println("scan done");
              if (n == 0) {
                Serial.println("no networks found");
              } else {
                Serial.print(n);
                Serial.println(" networks found");
                for (int i = 0; i < n; ++i) {
                  // Print SSID and RSSI for each network found
                  Serial.print(i + 1);
                  Serial.print(": ");
                  Serial.print(WiFi.SSID(i));
                  Serial.print(" (");
                  Serial.print(WiFi.RSSI(i));
                  Serial.print(")");
                  Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
                  //  mando al client
                  char buffer[200]; //TODO: RENDERE DINAMICO
                  char bufferSSID[50];
                  WiFi.SSID(i).toCharArray(bufferSSID, 50);
                  std::sprintf(buffer,"<input type=\"radio\" id=\"%d\" value=\"%s\"> <label for=\"%d\">%s</label><br>",i,bufferSSID,i,bufferSSID);
                  client.println(buffer);
                  delay(10);
                }
              }
              client.println("<br> <input type=\"text\" name=\"password\" id=\"password\"> </div> <button class=\"button\">OK</button> </body> </html>");
            }
            if (header.indexOf("GET /setPassword") >= 0) {
              Serial.println("/setPassoword");
              //Codice della route qui
              client.println("<!DOCTYPE html><html><h1>AMOGUS</h1></html>");
            }

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
