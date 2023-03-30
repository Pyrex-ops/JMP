#ifndef WIFI_PASSWORD_GETTER
#define WIFI_PASSWORD_GETTER

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

typedef enum {
    NO_INPUT_YET,
    INCORRECT_PASSWORD,
    MISSING_INPUT,
} mainpage_status_t;

class WifiPasswordGetter {
    private:
        const char* TEMPORARY_NETWORK_SSID;
        const char* TEMPORARY_NETWORK_PASSWORD;
        uint8_t MICROCONTROLLER_IP[4];
        uint8_t TEMPORARY_NETWORK_GATEWAY[4];
        uint8_t TEMPORARY_NETWORK_SUBNET_MASK[4];
        static const char* MAIN_PAGE;
        static const char* SUCCESS_PAGE;
        static const char* MAIN_PAGE_REDIRECTION;
        static mainpage_status_t mainpage_status;
        static String prepareAvailableWifiList(const String& var);
        static bool passwordCheck(const String& var);
        AsyncWebServer server;
    public:
        WifiPasswordGetter(
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
            const uint8_t temporary_network_subnet_mask_3
        );
        void start_wifi();
        void getWifiConfiguration(char* ssidBuffer, char* passwordBuffer);
        void stop_wifi();
};

#endif