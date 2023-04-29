<?php
//Connessione al database
require_once("../db/dbconnessione.php");

if (isset($_POST["id"]) && isset($_POST["valore"])) {
    if (isset($database)) {
        $queryDispositivo = $database->prepare("SELECT IDDispositivo FROM dispositivo WHERE IDDispositivo = (?)");
        $queryDispositivo->bind_param("i", $_POST["id"]);
        $queryDispositivo->execute();
        if (!$queryDispositivo->get_result()->num_rows == 0) {
            $queryDispositivo->close();
            $queryUtente = $database->prepare("SELECT utente.IDUtente FROM utente JOIN dispositivo ON utente.IDUtente = dispositivo.IDDispositivo WHERE IDDispositivo = (?) LIMIT 1");
            $queryUtente->bind_param("s", $_POST["id"]);
            $queryUtente->execute();
            $temp = $queryUtente->get_result()->fetch_assoc();
            $userID = $temp["IDUtente"]; //TODO: Sarà unico. Trova un modo più pulito.
            $queryAllenamento = $database->query("SELECT IDAllenamento FROM allenamento WHERE IDUtente = '$userID' ORDER BY IDAllenamento DESC LIMIT 1");
            $temp2 = $queryAllenamento->fetch_assoc();
            $allenamentoID = $temp2["IDAllenamento"]; //TODO: AGGIUNGI CONTROLLO, SE ALLENAMENTO NON C'è, QUESTO è NULL e l'inserimento non avviene!
            //In teoria se stiamo qui allora la scheda ha già comunicato l'inizio dell'allenamento però è sempre meglio controllare
            $queryInserimento = $database->prepare("INSERT INTO misura(IDAllenamento, valore) VALUE (?,?)");
            $queryInserimento->bind_param("si", $allenamentoID, $_POST["valore"]);
            $queryInserimento->execute();
            echo "\nScheda riconosciuta e dato inserito";
        } else {
            echo "\nScheda non riconosciuta";
        }
    }
}
