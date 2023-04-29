<?php
require_once("../db/dbconnessione.php");

if (isset($_GET["id"])) {
    //Da id dispositivo ricavare utente e aggiungere un nuovo allenamento
    if (isset($database)) {
        $queryDispositivo = $database->prepare("SELECT IDDispositivo FROM dispositivo WHERE IDDispositivo = (?)");
        $queryDispositivo->bind_param("i", $_GET["id"]);
        $queryDispositivo->execute();
        if (!$queryDispositivo->get_result()->num_rows == 0) {
            $queryDispositivo->close();
            $queryUtente = $database->prepare("SELECT utente.IDUtente FROM utente JOIN dispositivo ON utente.IDUtente = dispositivo.IDDispositivo WHERE IDDispositivo = (?) LIMIT 1");
            $queryUtente->bind_param("s", $_GET["id"]);
            $queryUtente->execute();
            $temp = $queryUtente->get_result()->fetch_assoc();
            $userID = $temp["IDUtente"]; //TODO: Sarà unico. Trova un modo più pulito.
            $queryAllenamento = $database->query("INSERT INTO allenamento(IDUtente) VALUE ('$userID')");

            echo "\nScheda riconosciuta e allenamento inserito";
        } else {
            echo "\nScheda non riconosciuta";
        }
    }
}
