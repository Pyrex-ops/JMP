#include "src/wifiPasswordGetter/WifiPasswordGetter.hpp"
#include "src/credentialsManager/credentialsManager.hpp"
#include "constants.hpp"

WifiPasswordGetter wifiPasswordGetter(
                                        DEFAULT_TEMPORARY_NETWORK_SSID,
                                        DEFAULT_TEMPORARY_NETWORK_PASSWORD,
                                        DEFAULT_MICROCONTROLLER_IP,
                                        DEFAULT_TEMPORARY_NETWORK_GATEWAY,
                                        DEFAULT_TEMPORARY_NETWORK_SUBNET_MASK
                                      );


wifi_configuration_t wifi_config;

void setup() {
  credentialsManager manager("credenzialiWiFi");
  Serial.begin(115200);
  wifi_config = wifiPasswordGetter.getWifiConfiguration();
  Serial.println(wifi_config.password);
  Serial.println(wifi_config.SSID);
  /*
    CODICE DEMO
    Credo che la dimensione massima salvabile nella flash sia di 24 caratteri per il campo chiave
  */
  //Serial.print("size getrecord:");
  //Serial.println(manager.getRecord(wifi_config.SSID).length());
  //Serial.println(manager.getRecord(wifi_config.SSID));
  //manager.dropEveryNamespace();
  //Serial.print("Numero totali di chiavi: ");
  //Serial.println(manager.getSize());
  /*Serial.println("Ora eliminiamo tutto");
    manager.dropEveryNamespace();
    Serial.println("OK");*/
  if(manager.getSSID().length()!=0){
      Serial.println("In memoria ho trovato le seguenti credenziali: ");
      Serial.print(manager.getSSID());
      Serial.print(" - ");
      Serial.println(manager.getPassword());
  }else{
    Serial.println("Salviamo le credenziali nella memoria flash persistente");
    if(manager.newRecord(wifi_config.SSID,wifi_config.password)){
      Serial.println("Credenziali salvate con successo");
      Serial.print("Numero totali di chiavi: ");
      Serial.println(manager.getSize());
    }
    Serial.println("Ora proviamo a recuperare le credenziali");
    Serial.print("Per l'SSID ");
    Serial.print(manager.getSSID());
    Serial.print(" è stata ritrovata la chiave: ");
    Serial.print(manager.getPassword());
  }
}

void loop() {
}