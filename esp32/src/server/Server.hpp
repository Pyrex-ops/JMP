#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <mutex>

/**
 * @brief Struct che contiene le informazioni della singola misura.
 *
 */
typedef struct {
	uint32_t jumps;
} training_sample_t;

/**
 * @brief Enum delle tipologie di obiettivo.
 *
 */
typedef enum {
	/**
	 * @brief Nessun obiettivo.
	 *
	 */
	NESSUNO = 0,
	/**
	 * @brief Numero di salti da raggiungere.
	 *
	 */
	NUMERO_SALTI = 1,
	/**
	 * @brief Calorie da spendere.
	 *
	 */
	CALORIE_SPESE = 2,
	/**
	 * @brief Tempo di allenamento da raggiungere in minuti.
	 *
	 */
	TEMPO_ALLENAMENTO_MINUTI = 3,
} tipologiaObiettivo_t;

/**
 * @brief Struct che contiene le informazioni sull'obiettivo.
 *
 */
typedef struct {
	tipologiaObiettivo_t tipologiaObiettivo;
	uint32_t valore;
} obiettivo_t;

/**
 * @brief Struct che contiene informazioni per l'upload delle misure sul server.
 *
 */
typedef struct {
	String serverName;
	uint32_t revolutions;
	bool* creatoAllenamento;
} upload_data_t;

/**
 * @brief Struct che contiene informazioni per la notifica di inizio allenamento
 * al server.
 *
 */
typedef struct {
	String serverName;
	bool* creatoAllenamento;
} start_training_data_t;

/**
 * @brief Struct che contiene informazioni per la richiesta dell'obiettivo al
 * server.
 *
 */
typedef struct {
	String serverName;
	obiettivo_t* obiettivo;
} get_obiettivo_data_t;

/**
 * @brief Struct che contiene informazioni per la richiesta del moltiplicatore
 * per le calorie al server.
 *
 */
typedef struct {
	String serverName;
	float* moltiplicatore;
} get_moltiplicatore_data_t;

/**
 * @brief Classe che permette la comunicazione con il server.
 *
 */
class BackendServer {
  private:
	/**
	 * @brief Flag che indica se la notifica di inizio allenamento è stata
	 * ricevuta dal server.
	 *
	 */
	bool creatoAllenamento;
	/**
	 * @brief Mutex che permette di evitare più comunicazioni di rete in
	 * contemporanea.
	 *
	 */
	static std::mutex mutexServer;
	/**
	 * @brief Permette di effettuare richieste HTTP.
	 *
	 */
	static HTTPClient http;
	/**
	 * @brief URL base del server remoto.
	 *
	 */
	String SERVER_NAME;
	/**
	 * @brief Invia misure al server in un thread separato.
	 *
	 * @param uploadData Informazioni per l'upload delle misure sul server.
	 */
	static void sendDataThreaded(void* uploadData);
	/**
	 * @brief Notifica l'inizio dell'allenamento al server in un thread
	 * separato.
	 *
	 * @param startTrainingData Informazioni per la notifica dell'inizio
	 * allenamento al server.
	 */
	static void startTrainingThreaded(void* startTrainingData);
	/**
	 * @brief Richiede l'obiettivo al server in un thread separato.
	 *
	 * @param getObiettivoData Informazioni per la richiesta dell'obiettivo al
	 * server.
	 */
	static void getObiettivoThreaded(void* getObiettivoData);
	/**
	 * @brief Richiede il moltiplicatore calorie al server in un thread
	 * separato.
	 *
	 * @param getMoltiplicatoreCalorieData Informazioni per la richiesta del
	 * moltiplicatore calorie al server.
	 */
	static void getMoltiplicatoreCalorieThreaded(void* getMoltiplicatoreCalorieData);
	/**
	 * @brief Handle per il task di invio dei dati.
	 *
	 */
	static TaskHandle_t taskSendData;
	/**
	 * @brief Handle per il task di inizio allenamento.
	 *
	 */
	static TaskHandle_t taskStartTraining;
	/**
	 * @brief Handle per il task di richiesta dell'obiettivo.
	 *
	 */
	static TaskHandle_t taskGetObiettivo;
	/**
	 * @brief Handle per il task di richiesta del moltiplicatore calorie.
	 *
	 */
	static TaskHandle_t taskGetMoltiplicatoreCalorie;
	/**
	 * @brief Certificato radice per il server.
	 *
	 */
	static const char* GIOCOMUNE_CA;
  public:
	/**
	 * @brief Costruisce un oggetto BackendServer.
	 *
	 * @param serverName L'URL base del server remoto.
	 */
	BackendServer(const char* serverName);
	/**
	 * @brief Notifica l'inizio dell'allenamento al server.
	 *
	 */
	void startTraining();
	/**
	 * @brief Invia una nuova misura al server.
	 *
	 * @param revolutions Numero di salti della misura.
	 */
	void sendData(uint32_t revolutions);
	/**
	 * @brief Richiede l'obiettivo al server,
	 *
	 * @param obiettivo Puntatore all'area di memoria dove verrà scritto
	 * l'obiettivo.
	 */
	void getObiettivo(obiettivo_t* obiettivo);
	/**
	 * @brief Richiede il moltiplicatore calorie al server.
	 *
	 * @param moltiplicatore Puntatore all'area di memoria dove verrà scritto il
	 * moltiplicatore calorie.
	 */
	void getMoltiplicatoreCalorie(float* moltiplicatore);
	/**
	 * @brief Controlla se il dispositivo è stato registrato.
	 *
	 * @return true Il dispositivo è registrato.
	 * @return false Il dispositivo non è registrato.
	 */
	bool checkRegistered();
	/**
	 * @brief Ripristina l'oggetto allo stato iniziale.
	 *
	 */
	void reset();
	/**
	 * @brief Connette il dispositivo al server remoto e mantiene la connessione
	 * per tutte le comunicazioni.
	 *
	 */
	void connect();
};

#endif