
#include "CaptiveRequestHandler.hpp"

CaptiveRequestHandler::CaptiveRequestHandler() {}

CaptiveRequestHandler::~CaptiveRequestHandler() {}
bool CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request) {
	return true;
}
void CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request) {
	request->redirect("http://configurazione-JMPcorda/");
}