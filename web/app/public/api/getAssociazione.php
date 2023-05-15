<?php
require_once("../../private/model/db/dbconnessione.php"); //
header("Content-Type: application/json");


if (isset($_GET["id"])) {
    if (isset($database)) {
        $queryDispositivo = $database->prepare("SELECT IDDispositivo FROM dispositivo WHERE IDDispositivo = (?)");
        $queryDispositivo->bind_param("s", $_GET["id"]);
        $queryDispositivo->execute();
        if (!$queryDispositivo->get_result()->num_rows == 0) {
            //Se arriviamo qui allora il dispositivo è stato trovato
            $queryDispositivo->close();
            $queryAssociazione = $database->prepare("SELECT utente.IDUtente, dispositivo.IDDispositivo FROM dispositivo JOIN utente ON dispositivo.IDUtente = utente.IDUtente WHERE dispositivo.IDDispositivo = ?");
            $queryAssociazione->bind_param("s", $_GET["id"]);
            $queryAssociazione->execute();
            $risultatoQueryAssociazione = $queryAssociazione->get_result()->num_rows;
            if ($risultatoQueryAssociazione != 0) {
                http_response_code(200);
                echo json_encode(["stato" => "ok", "associato" => true]);
                exit;
            } else {
                http_response_code(401);
                echo json_encode(["stato" => "errore", "associato" => false]);
                exit;
            }
        }
        http_response_code(401);
        echo json_encode(["stato" => "errore"]);
        exit;
    }
}