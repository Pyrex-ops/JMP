# ESP32

## Pinout

Il chip utilizzato, esp32, è montato su diverse schede che di seguito saranno trattate come equivalenti:

* esp32-wrover
* esp32-wrover-dev
* esp32-wrover-cam

Queste schede seguono questo pinout

![ESP32_Pinout](https://user-images.githubusercontent.com/60523265/223776226-cc2bbbba-6fa4-40ba-87e2-3c9410aefb5b.png)

## Local Web Server

Per consentire all'utente di inserire le credenziali della propria rete Wi-fi che sarà utilizzata dalla ESP32 per poter accedere alla rete internet, è esposta una rete Wi-Fi gestita dalla ESP32 con un Web Server che fornisce un'interfaccia all'utente per fornire le credenziali richieste.
