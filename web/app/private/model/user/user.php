<?php

include_once "/php/private/model/db/dbconnessione.php";

/*
 * Funzione per controllare se l'utente esiste
 * */
function does_user_exist($username): bool
{
    global $database;
    $query = $database->prepare("SELECT IDUtente FROM utente WHERE username = ?");
    $query->bind_param("s", $username);
    $query->execute();
    $result = $query->get_result();
    return $result->num_rows != 0;
}

/*
 * Funzione per aggiungere un utente al database
 * */
function add_user($username, $password, $weight): void
{
    global $database;
    $query = $database->prepare("INSERT INTO utente(username, passwordhash,peso) VALUES (?,?,?)");
    $passhash = password_hash($password, PASSWORD_BCRYPT);
    $query->bind_param("ssi", $username, $passhash, $weight);
    $query->execute();
    $query->close();
}

/*
 * Funzione per ottenere l'identificativo dell'utente
 * */
function get_id($username)
{
    global $database;
    $query = $database->prepare("SELECT IDUtente FROM utente WHERE username = ?");
    $query->bind_param("s", $username);
    $query->execute();
    $result = $query->get_result();
    return $result->fetch_row()[0];
}

/*
 * Funzione per rimuovere l'utente dal database
 * */
function remove_user(): void
{
    global $database;
    $query = $database->prepare("DELETE FROM utente WHERE username = ?");
    $username = get_username();
    $query->bind_param("s", $username);
    $query->execute();
}

/*
 * Funzione per l'ottenimento dei dati che popolano il grafico dell'andamento
 * */
function duration_graph(): void
{
    global $database;
    //Prendiamo il vettore con le durate degli allenamenti e data d'inizio
    //(data allenamento, durata)
    $idUtente = get_id(get_username());
    $query = $database->prepare("SELECT DATE_FORMAT(MIN(misura.timestamp),'%d-%m') AS 'dataAllenamento' ,(unix_timestamp(max(misura.timestamp)) - unix_timestamp(min(misura.timestamp)))/60 AS `durataAllenamento`
FROM allenamento JOIN misura ON allenamento.IDAllenamento = misura.IDAllenamento JOIN utente ON allenamento.IDUtente = utente.IDUtente
WHERE utente.IDUtente = ? AND misura.timestamp >= NOW() - INTERVAL 12 MONTH
GROUP BY allenamento.IDAllenamento;");
    $query->bind_param("i", $idUtente);
    $query->execute();
    $arrayDate = [];
    $arrayDurata = [];
    $result = $query->get_result();
    while ($riga = $result->fetch_assoc()) {
        $arrayDate[] = $riga["dataAllenamento"];
        $arrayDurata[] = $riga["durataAllenamento"];
    }
    echo "let arrayDate = " . json_encode($arrayDate) . ";";
    echo "let arrayDurata = " . json_encode($arrayDurata) . ";";
}

/*
 * Funzione per ottenere i dati che popolano il componente che mostra
 * gli ultimi 3 allenamenti eseguiti
 * */
function last_trainings(): void
{
    global $database;
    //Prendiamo gli ultimi 3 allenamenti (che hanno un obiettivo associato) dell'utente e il relativo superamento dell'obiettivo fissato
    $idUtente = get_id(get_username());
    $query = $database->prepare("SELECT DATE(MIN(misura.timestamp)) AS 'dataAllenamento' ,(unix_timestamp(max(misura.timestamp)) - unix_timestamp(min(misura.timestamp))) AS `durataAllenamento`,allenamento.IDAllenamento AS 'IdAllenam', obiettivo.IDCategoria,
(
    CASE
    	WHEN obiettivo.IDCategoria = 1 THEN (
        	SELECT IF(SUM(misura.numeroSalti)>=obiettivo.parametro, 1, 0)
            FROM misura JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
            JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
            JOIN utente ON allenamento.IDUtente = utente.IDUtente
            WHERE allenamento.IDAllenamento = IdAllenam
            GROUP BY allenamento.IDAllenamento
        	)
    	WHEN obiettivo.IDCategoria = 2 THEN (
        	SELECT IF(SUM(misura.numeroSalti)*utente.peso*2.205*0.001>=obiettivo.parametro, 1, 0)
            FROM misura JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
            JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
            JOIN utente ON allenamento.IDUtente = utente.IDUtente
            WHERE allenamento.IDAllenamento = IdAllenam
            GROUP BY allenamento.IDAllenamento
        	)
    	WHEN obiettivo.IDCategoria = 3 THEN (
        	SELECT IF((unix_timestamp(max(misura.timestamp)) - unix_timestamp(min(misura.timestamp)))/60>=obiettivo.parametro, 1, 0)
            FROM misura JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
            JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
            JOIN utente ON allenamento.IDUtente = utente.IDUtente
            WHERE allenamento.IDAllenamento = IdAllenam
            GROUP BY allenamento.IDAllenamento)
        ELSE 0
    END
) AS superamento
FROM allenamento LEFT OUTER JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
JOIN utente ON utente.IDUtente = allenamento.IDUtente
JOIN misura ON misura.IDAllenamento = allenamento.IDAllenamento
WHERE utente.IDUtente=?
GROUP BY allenamento.IDAllenamento
ORDER BY IDAllenam DESC
LIMIT 3;");
    $query->bind_param("i", $idUtente);
    $query->execute();
    $risultato = $query->get_result();
    $arrayDati3allenamenti = [];
    while ($riga = $risultato->fetch_assoc()) {
        $arrayDati3allenamenti[] = ["id" => $riga["IdAllenam"], "name" => substr($riga["dataAllenamento"], 5), "duration" => (int) ($riga["durataAllenamento"] / 60) . "m", "goalReached" => (bool) $riga["superamento"]];
    }
    echo json_encode($arrayDati3allenamenti);
}

/*
 * Funzione per ottenere la lista degli allenamenti
 * */
function all_trainings(): void
{
    global $database;
    $idUtente = get_id(get_username());
    $query = $database->prepare("SELECT DATE(MIN(misura.timestamp)) AS 'dataAllenamento' ,(unix_timestamp(max(misura.timestamp)) - unix_timestamp(min(misura.timestamp))) AS `durataAllenamento`,allenamento.IDAllenamento AS 'IdAllenam', obiettivo.IDCategoria,
(
    CASE
    	WHEN obiettivo.IDCategoria = 1 THEN (
        	SELECT IF(SUM(misura.numeroSalti)>=obiettivo.parametro, 1, 0)
            FROM misura JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
            JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
            JOIN utente ON allenamento.IDUtente = utente.IDUtente
            WHERE allenamento.IDAllenamento = IdAllenam
            GROUP BY allenamento.IDAllenamento
        	)
    	WHEN obiettivo.IDCategoria = 2 THEN (
        	SELECT IF(SUM(misura.numeroSalti)*utente.peso*2.205*0.001>=obiettivo.parametro, 1, 0)
            FROM misura JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
            JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
            JOIN utente ON allenamento.IDUtente = utente.IDUtente
            WHERE allenamento.IDAllenamento = IdAllenam
            GROUP BY allenamento.IDAllenamento
        	)
    	WHEN obiettivo.IDCategoria = 3 THEN (
        	SELECT IF((unix_timestamp(max(misura.timestamp)) - unix_timestamp(min(misura.timestamp)))/60>=obiettivo.parametro, 1, 0)
            FROM misura JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
            JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
            JOIN utente ON allenamento.IDUtente = utente.IDUtente
            WHERE allenamento.IDAllenamento = IdAllenam
            GROUP BY allenamento.IDAllenamento)
        ELSE 0
    END
) AS superamento
FROM allenamento LEFT OUTER JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
JOIN utente ON utente.IDUtente = allenamento.IDUtente
JOIN misura ON misura.IDAllenamento = allenamento.IDAllenamento
WHERE utente.IDUtente=?
GROUP BY allenamento.IDAllenamento
ORDER BY IDAllenam DESC;");
    $query->bind_param("i", $idUtente);
    $query->execute();
    $risultato = $query->get_result();
    $arrayDatiallenamenti = [];
    while ($riga = $risultato->fetch_assoc()) {
        $arrayDatiallenamenti[] = ["id" => $riga["IdAllenam"], "name" => substr($riga["dataAllenamento"], 5), "duration" => (int) ($riga["durataAllenamento"] / 60) . "m", "goalReached" => (bool) $riga["superamento"]];
    }
    echo json_encode($arrayDatiallenamenti);
}

/*
 * Funzione che ritorna i giorni della settimana in cui si è svolto
 * un allenamento
 * */
function successful_days_of_week(): void
{
    global $database;
    $idUtente = get_id(get_username());
    $query = $database->prepare("SELECT ELT(WEEKDAY(DATE(MIN(misura.timestamp)))+1,'Lunedì','Martedì','Mercoledì','Giovedì','Venerdì','Sabato','Domenica') AS 'giorno',
     DATE(MIN(misura.timestamp)) AS 'dataAllenamento' FROM allenamento LEFT OUTER JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
JOIN utente ON utente.IDUtente = allenamento.IDUtente
JOIN misura ON misura.IDAllenamento = allenamento.IDAllenamento
WHERE utente.IDUtente=?
GROUP BY allenamento.IDAllenamento
HAVING dataAllenamento >= NOW() + INTERVAL -7 DAY AND dataAllenamento < NOW() + INTERVAL 0 DAY");
    $query->bind_param("i", $idUtente);
    $query->execute();
    $risultato = $query->get_result();
    $arraySettimana = [];
    while ($riga = $risultato->fetch_assoc()) {
        $arraySettimana[] = $riga["giorno"];
    }
    echo "const selectedDays = " . json_encode($arraySettimana) . ";";
}

/*
 * Funzione per ottenere le impostazioni dell'account utente
 * */
function echo_impostazioni($user)
{
    global $database;
    $username = get_username();
    $query = $database->prepare("SELECT peso,partecipazioneClassifica AS consensoClassifica FROM utente WHERE username = ?");
    $query->bind_param("s", $username);
    $query->execute();
    $result = $query->get_result();
    echo(json_encode($result->fetch_assoc()));
}