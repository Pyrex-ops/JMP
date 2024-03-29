<?php

require_once("/php/private/model/db/dbconnessione.php");
header("Content-Type: application/json");

/*
 * Endpoint per l'ottenimento del moltiplicatore
 * Il moltiplicatore fornisce l'equivalente calorico di ogni salto
 * */
if (isset($_GET["id"])) {
    if (isset($database)) {
        $queryDispositivo = $database->prepare("SELECT IDDispositivo FROM dispositivo WHERE IDDispositivo = (?)");
        $queryDispositivo->bind_param("s", $_GET["id"]);
        $queryDispositivo->execute();
        if (!$queryDispositivo->get_result()->num_rows == 0) {
            //Se arriviamo qui allora il dispositivo è stato trovato
            $queryDispositivo->close();
            $queryUtente = $database->prepare("SELECT utente.peso FROM dispositivo JOIN utente on utente.IDUtente = dispositivo.IDUtente WHERE dispositivo.IDDispositivo = ?;");
            $queryUtente->bind_param("s", $_GET["id"]);
            $queryUtente->execute();
            $pesoUtente = $queryUtente->get_result()->fetch_column(0);
            $caloriaSingoloSalto = ($pesoUtente * 2.205 * 0.001);
            http_response_code(200);
            echo json_encode(array("stato" => "ok", "moltiplicatore" => round($caloriaSingoloSalto, 4, PHP_ROUND_HALF_EVEN)));
            exit;
        } else {
            $queryDispositivo->close();
            http_response_code(401);
            echo json_encode(array("stato" => "errore"));
            exit;
        }
    }
}