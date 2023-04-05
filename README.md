# JMP

Smart Jumping Rope - IoT

## Descrizione

---

Nella seguente descrizione resta da revisionare:

- [ ] la presenza degli esempi
- [ ] Definire le informazioni da mostrare sullo schermo

---

Si vuole sviluppare un’applicazione IoT per il supporto agli allenamenti di salto con la corda. 
L’applicazione fornisce due funzioni principali: 

1. Collezione e visualizzazione di statistiche sugli allenamenti quali: la velocità media di salto, il numero di salti, la durata dell’allenamento, il numero di calorie consumate. 
2. Feedback durante l’allenamento, fornito da un motorino vibrante, ovvero, l'utente può impostare un obiettivo da raggiungere durante il prossimo allenamento con il fine di migliorare le proprie prestazioni. Ad esempio, il dispositivo esegue 3 vibrazioni in rapida successione al raggiungimento dell'obiettivo impostato, come il numero di salti ecc.   

Dal piccolo schermo montato sul manico, l'utente ha una visualizzazione compatta delle informazioni relative all'allenamento in corso. Per visualizzare le statistiche complete l’utente dovrà registrare un profilo, sul portale web dedicato, a cui il dispositivo invierà i dati, fornendo una serie di dati personali quali l’altezza, il sesso e l’età che saranno utilizzati per il calcolo, da parte del server, delle calorie consumate.  
Ogni corda per saltare è identificata da un codice univoco che sarà utilizzato in fase di registrazione per associare la corda ad un solo profilo e per distinguere le corde nel sistema. Il codice verrà fornito insieme alla corda.  
L'utente, opzionalmente, può partecipare alla classifica globale, stilata in base alla velocità di salto media e tempo di allenamento.

## Requisiti

Di seguito sono riportati i requisiti che dovrà rispettare il progetto.  
I seguenti requisiti saranno rappresentati in **due** diagrammi dei casi d'uso, uno per il dispositivo fisico e un altro per la parte *cloud*.  
I casi d'uso saranno quindi racchiusi in un grande *riquadro* con l'apposita etichetta (dispositivo/server).  

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
* Il sistema permetterà all'utente di indicare i parametri necessari al calcolo delle calorie spese:
  * Peso
  * Età
  * Sesso
* Il sistema consentirà all'utente di eliminare i parametri personali forniti in precedenza.
* Il sistema non fornirà il calcolo delle calorie spese se l'utente non ha fornito i dati necessari per il calcolo.

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
