# JMP

Smart Jumping Rope - IoT

- [JMP](#jmp)
  - [Descrizione](#descrizione)
  - [Requisiti](#requisiti)
    - [Requisiti funzionali](#requisiti-funzionali)
    - [Requisiti non funzionali](#requisiti-non-funzionali)
  - [Struttura cartelle](#struttura-cartelle)
  - [Schema circuitale](#schema-circuitale)


## Descrizione

Si vuole sviluppare un’applicazione IoT per il supporto agli allenamenti di salto con la corda. 
L’applicazione fornisce due funzioni principali: 

1. Collezione e visualizzazione di statistiche sugli allenamenti quali: il numero di salti, la durata dell’allenamento, il numero di calorie consumate. 
2. Feedback durante l’allenamento, fornito da un motorino vibrante e da un piccolo schermo disposto sul manico, ovvero, l'utente può impostare un obiettivo da raggiungere durante il prossimo allenamento con il fine di migliorare le proprie prestazioni e riceverà un feedback al raggiungimento di quest'ultimo.  

Dal piccolo schermo montato sul manico, l'utente ha una visualizzazione compatta delle informazioni relative all'allenamento in corso. Per visualizzare le statistiche complete l’utente dovrà registrare un profilo, sul portale web dedicato, a cui il dispositivo invierà i dati, fornendo la propria massa che sarà utilizzata per il calcolo, da parte del server, delle calorie consumate.  
Ogni corda per saltare è identificata da un codice univoco che sarà utilizzato per associare la corda ad un solo profilo e per distinguere le corde nel sistema. Il codice verrà fornito insieme alla corda.  
L'utente, opzionalmente, può partecipare alla classifica globale, stilata in base al numero di salti e tempo di allenamento.

## Requisiti

Di seguito sono riportati i requisiti che dovrà rispettare il progetto.  
I seguenti requisiti saranno rappresentati in **due** diagrammi dei casi d'uso, uno per il dispositivo fisico e un altro per la parte *cloud*.  
I casi d'uso saranno quindi racchiusi in un grande *riquadro* con l'apposita etichetta (dispositivo/server).  

### Requisiti funzionali

* Il sistema rileva l'inizio di un allenamento.
* Il sistema rileva la fine un allenamento.
* Il sistema permette all'utente di conoscere le calorie *spese* durante l'allenamento.
* Il sistema consente all'utente di conoscere la durata degli allenamenti.
* Il sistema consente all'utente di impostare i seguenti obiettivi:
  * Numero di salti.
  * Calorie spese.
  * Tempo di allenamento.
* Il dispositivo avvisa l'utente, tramite vibrazioni controllate e messaggio sullo schermo, del raggiungimento degli obiettivi.
* Il dispositivo mostra, in tempo reale:
  * Il numero di salti effettuati.
  * Il numero di calorie *spese*.
* Il dispositivo espone una rete WiFi e un'interfaccia web per consentire la prima configurazione del dispositivo.
* Il sistema consente all'utente di registrare un account.
* Il sistema consente all'utente di eliminare l'account registrato in precedenza.
* Il sistema consente all'utente di aggiungere un dispositivo al proprio account.
* Il sistema consente all'utente di rimuovere un dispositivo dal proprio account.
* Il sistema consente all'utente di visualizzare i dati raccolti.
* Il sistema elabora le seguenti statistiche:
  * Numero di salti medio eseguito durante gli allenamenti (salti/min).
  * Calorie spese in media negli allenamenti (calorie/min).
* Il sistema consente all'utente di visualizzare le statistiche elaborate.
* Il sistema stila una classifica degli utenti che vi vorranno partecipare, in base al numero di salti e tempo di allenamento.
* L'utente può ritirare la partecipazione alla classifica.
* Il sistema permette all'utente di indicare i parametri necessari al calcolo delle calorie spese:
  * Peso
* Il sistema consente all'utente di modificare i parametri personali forniti in precedenza.

### Requisiti non funzionali

* Il dispositivo salva nella memoria non volatile le credenziali della rete
* Il dispositivo, per garantire la confidenzialità delle comunicazioni, dovrà supportare reti wireless protette da password
* I dati elaborati dal sistema saranno consultati dall'utente mediante un'interfaccia web
* Il sistema conserva le credenziali degli account in sicurezza.

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
## Schema circuitale

![Circuito2](https://github.com/Pyrex-ops/JMP/assets/60523265/64de4bfe-8dbd-4a44-ad53-9c42c1aa7872)

