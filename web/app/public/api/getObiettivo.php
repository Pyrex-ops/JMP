<?php

require_once '../db/dbconnessione.php';
header('Content-Type: application/json');

if (isset($_GET['id'])) {
    if (isset($database)) {
        $queryDispositivo = $database->prepare('SELECT IDDispositivo FROM dispositivo WHERE IDDispositivo = (?)');
        $queryDispositivo->bind_param('i', $_GET['id']);
        $queryDispositivo->execute();
        if (! $queryDispositivo->get_result()->num_rows == 0) {
            //Se arriviamo qui allora il dispositivo è stato trovato
            $queryDispositivo->close();
            $queryObiettivo = $database->prepare('SELECT utente.IDObiettivo FROM utente JOIN dispositivo ON utente.IDUtente = dispositivo.IDUtente WHERE dispositivo.IDDispositivo = ?');
            $queryObiettivo->bind_param('s', $_GET['id']);
            $queryObiettivo->execute();
            $idObiettivo = $queryObiettivo->get_result();
            if ($idObiettivo->num_rows != 0) {
                //Può essere null se non c'è un obiettivo associato all'utente
                http_response_code(200);
                echo json_encode(['stato' => 'ok', 'idObiettivo' => $idObiettivo->fetch_row()[0]]);
            } else {
                http_response_code(401);
                echo json_encode(['stato' => 'errore']);
            }
            $queryObiettivo->close();
            exit;
        } else {
            $queryDispositivo->close();
            http_response_code(401);
            echo json_encode(['stato' => 'errore']);
            exit;
        }
    }
}
