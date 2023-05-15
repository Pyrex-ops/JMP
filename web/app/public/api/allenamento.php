<?php

require_once("/php/private/model/db/dbconnessione.php");
header('Content-Type: application/json');

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
            $userID = $temp['IDUtente']; //TODO: Sarà unico. Trova un modo più pulito. Vedi se aggregare tutto in unica query (quella di sopra in questa qui sotto)
            $queryAllenamento = $database->query("INSERT INTO allenamento(IDUtente) VALUE ('$userID')");
            http_response_code(200);
            echo json_encode(['stato' => 'ok']);
            exit;
        } else {
            http_response_code(401);
            echo json_encode(['stato' => 'errore']);
            exit;
        }
    }
}