<?php
//Connessione al database
require_once("../db/dbconnessione.php");
header("Content-Type: application/json");

if (isset($_GET["id"]) && isset($_GET["valore"])) {
    if (isset($database)) {
        $queryDispositivo = $database->prepare("SELECT IDDispositivo FROM dispositivo WHERE IDDispositivo = (?)");
        $queryDispositivo->bind_param("s", $_GET["id"]);
        $queryDispositivo->execute();
        if (!$queryDispositivo->get_result()->num_rows == 0) {
            $queryDispositivo->close();
            $queryAllenamento = $database->prepare("SELECT IDAllenamento FROM allenamento JOIN dispositivo on allenamento.IDUtente = dispositivo.IDUtente WHERE IDDispositivo = ? ORDER BY IDAllenamento DESC LIMIT 1");
            $queryAllenamento->bind_param("s", $_GET["id"]);
            $queryAllenamento->execute();
            $tempAllenamento = $queryAllenamento->get_result();
            if ($tempAllenamento->num_rows != 0) {
                $allenamentoID = $tempAllenamento->fetch_row()[0];
            } else {
                http_response_code(401);
                echo json_encode(array("stato" => "errore"));
                exit();
            }
            //In teoria se stiamo qui allora la scheda ha già comunicato l'inizio dell'allenamento però è sempre meglio controllare
            $queryInserimento = $database->prepare("INSERT INTO misura(IDAllenamento, numeroSalti) VALUE (?,?)");
            $queryInserimento->bind_param("si", $allenamentoID, $_GET["valore"]);
            $queryInserimento->execute();
            http_response_code(200);
            echo json_encode(array("stato" => "ok"));
            exit();
        } else {
            http_response_code(401);
            echo json_encode(array("stato" => "errore"));
            exit();
        }
    }
}