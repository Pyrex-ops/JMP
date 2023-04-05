# JMP
Smart Jumping Rope - IoT

## Requisiti

Di seguito sono riportati i requisiti che dovrà rispettare il progetto

### Requisiti funzionali

* Il sistema consentirà all'utente di iniziare un allenamento.
* Il sistema consentirà all'utente di terminare un allenamento.
* Il sistema permetterà all'utente di conoscere le calorie *spese* durante l'allenamento.
* Il sistema consentirà all'utente di conoscere la durata degli allenamenti.
* Il sistema consentirà all'utente di impostare i seguenti obiettivi:
  * Numero di salti.
  * Frequenza di salto.
  * Calorie spese.
  * Tempo di allenamento.
* Il dispositivo avviserà l'utente, tramite vibrazioni controllate, del raggiungimento degli obiettivi.
* Il dispositivo mostrerà, in tempo reale:
  * Il numero di salti effettuati.
  * Il numero di calorie *spese*.
* Il dispositivo esporrà una rete WiFi e un'interfaccia web per consentire la prima configurazione del dispositivo.
* Il sistema consentirà all'utente di registrare un account.
* Il sistema consentirà all'utente di eliminare l'account registrato in precedenza.
* Il sistema consentirà all'utente di aggiungere un dispositivo al proprio account.
* Il sistema consentirà all'utente di rimuovere un dispositivo dal proprio account.
* Il sistema consentirà all'utente di visualizzare i dati raccolti.
* Il sistema elaborerà le seguenti statistiche:
  * Velocità di salto media: $\frac{\text{Numero di salti}}{\text{Tempo di allenamento}}$.
  * Calorie spese in media negli allenamenti.
* Il sistema consentirà all'utente di visualizzare le statistiche elaborate.
* Il sistema consentirà all'utente di eliminare di dati raccolti.
* Il sistema comporrà una classifica degli utenti che vi vorranno partecipare, in base alla velocità di salto media e tempo di allenamento.
* L'utente potrà ritirare la partecipazione alla classifica.

### Requisiti non funzionali

* Il dispositivo dovrà salvare nella memoria non volatile le credenziali della rete
* Il dispositivo, per garantire la confidenzialità delle comunicazioni, dovrà supportare reti wireless protette da password
* I dati elaborati dal sistema saranno consultati dall'utente mediante un'interfaccia web
* Il sistema conserverà le credenziali sotto forma di hash

## Struttura cartelle

```
.
├── README.md
├── esp32/
│   ├── src/
│   ├── test/
│   ├── asset/ (png, svg, ecc.)
│   └── README.md
└── web/
    ├── src/
    ├── test/
    ├── asset/ (png, svg, ecc.)
    └── README.md
```
