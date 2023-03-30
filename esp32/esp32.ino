#include "src/wifiPasswordGetter/WifiPasswordGetter.hpp"
#include "constants.hpp"

WifiPasswordGetter wifiPasswordGetter(
                                        DEFAULT_TEMPORARY_NETWORK_SSID,
                                        DEFAULT_TEMPORARY_NETWORK_PASSWORD,
                                        DEFAULT_MICROCONTROLLER_IP,
                                        DEFAULT_TEMPORARY_NETWORK_GATEWAY,
                                        DEFAULT_TEMPORARY_NETWORK_SUBNET_MASK
                                      );

void setup() {
  Serial.begin(115200);
  wifiPasswordGetter.start_wifi();
}

void loop() {
}