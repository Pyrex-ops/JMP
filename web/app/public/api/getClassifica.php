<?php

require_once '../db/dbconnessione.php';
header('Content-Type: application/json');

if (isset($database)) {
    if (isset($_GET['tipo'])) {
        if ($_GET['tipo'] == 1) {
            //Numero salti utente
            //TODO: Prendi i dati dalle view
            $numSalti = $database->query("SELECT * FROM classificanumsalti");
            $arraySalti = array();
            while ($riga = $numSalti->fetch_assoc()) {
                $arraySalti[] = $riga;
            }
            http_response_code(200);
            echo json_encode(['stato' => 'ok', 'classificaSalti' => $arraySalti]);
            exit;
        } elseif ($_GET['tipo'] == 2) {
            //Durata allenamento
            $durataAllenamenti = $database->query("SELECT * FROM classificadurata");
            $arrayDurata = array();
            while ($riga = $durataAllenamenti->fetch_assoc()) {
                $arrayDurata[] = $riga;
            }
            http_response_code(200);
            echo json_encode(['stato' => 'ok', 'classificaDurata' => $arrayDurata]);
            exit;
        } else {
            http_response_code(401);
            echo json_encode(['stato' => 'errore']);
            exit;
        }
    }
} else {
    http_response_code(401);
    echo json_encode(['stato' => 'errore']);
    exit;
}
