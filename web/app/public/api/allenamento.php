<?php

require_once("/php/private/model/db/dbconnessione.php");
header('Content-Type: application/json');
/*
 * Endpoint per l'avvio dell'allenamento
 * */
if (isset($_GET['id'])) {
    //Da id dispositivo ricavare utente e aggiungere un nuovo allenamento
    if (isset($database)) {
        $queryDispositivo = $database->prepare('SELECT IDDispositivo FROM dispositivo WHERE IDDispositivo = (?)');
        $queryDispositivo->bind_param('s', $_GET['id']);
        $queryDispositivo->execute();
        if (!$queryDispositivo->get_result()->num_rows == 0) {
            $queryDispositivo->close();
            $queryUtente = $database->prepare('SELECT utente.IDUtente FROM utente JOIN dispositivo ON utente.IDUtente = dispositivo.IDUtente WHERE IDDispositivo = (?) LIMIT 1');
            $queryUtente->bind_param('s', $_GET['id']);
            $queryUtente->execute();
            $temp = $queryUtente->get_result()->fetch_assoc();
            if (isset($temp)) {
                $userID = $temp['IDUtente'];
                //Controlliamo il timestamp dell'ultimo allenamento, se è troppo recente allora non inseriamo un nuovo allenamento
                $queryControllo = $database->query("SELECT timestamp FROM misura JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento WHERE allenamento.IDUtente = $userID AND TIMESTAMPDIFF(SECOND, timestamp, NOW()) < 5 ORDER BY timestamp DESC LIMIT 1;");
                $queryControlloAllenamentoVuoto = $database->query("SELECT COUNT(misura.IDMisura) as c
FROM misura
WHERE misura.IDAllenamento IN (SELECT MAX(allenamento.IDAllenamento)
                                FROM allenamento JOIN utente ON allenamento.IDUtente = utente.IDUtente
                                    
                                WHERE utente.IDUtente = $userID
                                ORDER BY allenamento.IDAllenamento DESC);");
                $risultatoQueryControllo = $queryControllo->fetch_assoc();
                $risultatoQueryAllenamentoVuoto = $queryControlloAllenamentoVuoto->fetch_assoc();
                //Alternativa: inserire allenamento alla creazione dell'utente
                //Se l'utente non ha allenamenti, facciamo inserire un allenamento.
                $queryAllenamentiVuoti = $database->query("SELECT allenamento.IDAllenamento FROM allenamento JOIN utente ON allenamento.IDUtente = utente.IDUtente WHERE allenamento.IDUtente = $userID ORDER BY allenamento.IDAllenamento DESC LIMIT 1;");
                $queryObiettivoAssociato = $database->query("SELECT IDObiettivo,peso FROM utente WHERE IDUtente=$userID");
                $tempArray = $queryObiettivoAssociato->fetch_assoc();
                $idObiettivo = $tempArray["IDObiettivo"];
                $pesoUtente = $tempArray["peso"];
                if ($queryAllenamentiVuoti->num_rows == 0) {
                    if (isset($idObiettivo)) {
                        $queryAllenamento = $database->query("INSERT INTO allenamento(IDUtente,IDObiettivo,peso) VALUES ('$userID','$idObiettivo',$pesoUtente)");
                    } else {
                        $queryAllenamento = $database->query("INSERT INTO allenamento(IDUtente,IDObiettivo,peso) VALUES ('$userID',NULL,$pesoUtente)");
                    }
                    http_response_code(200);
                    echo json_encode(['stato' => 'ok']);
                    exit;
                }
                if (!isset($risultatoQueryControllo["timestamp"]) && $risultatoQueryAllenamentoVuoto["c"] != 0) {
                    if (isset($idObiettivo)) {
                        $queryAllenamento = $database->query("INSERT INTO allenamento(IDUtente,IDObiettivo,peso) VALUES ('$userID','$idObiettivo',$pesoUtente)");
                    } else {
                        $queryAllenamento = $database->query("INSERT INTO allenamento(IDUtente,IDObiettivo,peso) VALUES ('$userID',NULL,$pesoUtente)");
                    }
                    http_response_code(200);
                    echo json_encode(['stato' => 'ok']);
                    exit;
                } else {
                    //Assoceremo le nuove misure ad un allenamento precedente che era vuoto
                    http_response_code(200);
                    echo json_encode(['stato' => 'ok']);
                    exit;
                }
            } else {
                http_response_code(401);
                echo json_encode(['stato' => 'errore']);
                exit;
            }
        } else {
            http_response_code(401);
            echo json_encode(['stato' => 'errore']);
            exit;
        }
    }
}