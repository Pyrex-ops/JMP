#ifndef CAPTIVE_REQUEST_HANDLER_H
#define CAPTIVE_REQUEST_HANDLER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

/**
 * @brief Classe utilizzata per reindirizzare tutte le richieste al web server ad 
 * un captive portal.
 * 
 * Eredita la classe AsyncWebHandler e ha il compito di indicare tutte le richieste come soddisfabili
 * e soddisfarle tramite la redirezione al captive portal.
 */
class CaptiveRequestHandler : public AsyncWebHandler {
public:
  /**
   * @brief Costruisce un oggetto CaptiveRequestHandler.
   * 
   */
  CaptiveRequestHandler();
  /**
   * @brief Distrugge un oggetto CaptiveRequestHandler.
   * 
   */
  virtual ~CaptiveRequestHandler();

  /**
   * @brief Determina se la richiesta può essere soddisfatta.
   * 
   * @param request La richiesta all'AP.
   * @return true La richiesta può essere soddisfatta.
   * @return false La richiesta non può essere soddisfatta.
   */
  bool canHandle(AsyncWebServerRequest *request);

  /**
   * @brief Soddisfa la richiesta al web server.
   * 
   * @param request 
   */
  void handleRequest(AsyncWebServerRequest *request);
};

#endif