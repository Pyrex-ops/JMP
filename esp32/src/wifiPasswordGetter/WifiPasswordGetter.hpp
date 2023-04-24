#ifndef WIFI_PASSWORD_GETTER
#define WIFI_PASSWORD_GETTER

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

/**
 * @brief Tutti gli stati possibili del processo di configurazione del wifi.
 * 
 * Lo stato è utilizzato per determinare eventuali messaggi di errore.
 * 
 */
typedef enum {
    NO_INPUT_YET,
    INCORRECT_PASSWORD,
    MISSING_INPUT,
} mainpage_status_t;

/**
 * @brief Credenziali per la connessione ad una rete wifi.
 * 
 */
typedef struct {
    String SSID;
    String password;
} wifi_configuration_t;

class WifiPasswordGetter {
    private:
        const char* TEMPORARY_NETWORK_SSID;
        const char* TEMPORARY_NETWORK_PASSWORD;
        //uint8_t MICROCONTROLLER_IP[4];
        IPAddress MICROCONTROLLER_IP;
        uint8_t TEMPORARY_NETWORK_GATEWAY[4];
        IPAddress  TEMPORARY_NETWORK_SUBNET_MASK;
        static const char* SUCCESS_PAGE;
        static const char* MAIN_PAGE_REDIRECTION;
        static mainpage_status_t mainpage_status;
        static String prepareAvailableWifiList(const String& var);
        static bool passwordCheck(const String& ssid,const String& password);
        static wifi_configuration_t* wifi_config;
        AsyncWebServer server;
        friend wifi_configuration_t getWifiConfiguration();
        void start_wifi();
        void stop_wifi();
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
        static const char* MAIN_PAGE;
        wifi_configuration_t getWifiConfiguration();
};

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler();
  virtual ~CaptiveRequestHandler();

  bool canHandle(AsyncWebServerRequest *request);

  void handleRequest(AsyncWebServerRequest *request);
};
#endif