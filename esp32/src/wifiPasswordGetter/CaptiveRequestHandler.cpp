
#include "CaptiveRequestHandler.hpp"

CaptiveRequestHandler::CaptiveRequestHandler() {

}

CaptiveRequestHandler::~CaptiveRequestHandler() {}
bool CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request){
  //request->addInterestingHeader("ANY");
  return true;
}
void CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request) {
  request->redirect("http://smart.rope/");
}