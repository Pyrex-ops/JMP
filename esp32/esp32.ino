#include "src/wifiPasswordGetter/WifiPasswordGetter.hpp"
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
  Serial.begin(115200);
  wifi_config = wifiPasswordGetter.getWifiConfiguration();
  Serial.println(wifi_config.password);
  Serial.println(wifi_config.SSID);
}

void loop() {
}