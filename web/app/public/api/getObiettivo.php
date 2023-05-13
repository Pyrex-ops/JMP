<?php
require_once("../db/dbconnessione.php");
header("Content-Type: application/json");


if (isset($_GET["id"])) {
    if (isset($database)) {
        $queryDispositivo = $database->prepare("SELECT IDDispositivo FROM dispositivo WHERE IDDispositivo = (?)");
        $queryDispositivo->bind_param("s", $_GET["id"]);
        $queryDispositivo->execute();
        if (!$queryDispositivo->get_result()->num_rows == 0) {
            //Se arriviamo qui allora il dispositivo è stato trovato
            $queryDispositivo->close();
            $queryObiettivo = $database->prepare("SELECT obiettivo.IDCategoria, obiettivo.parametro
                                                        FROM utente 
	                                                        JOIN dispositivo ON utente.IDUtente = dispositivo.IDUtente 
                                                            JOIN obiettivo ON utente.IDObiettivo = obiettivo.IDObiettivo
                                                        WHERE dispositivo.IDDispositivo = ?;");
            $queryObiettivo->bind_param("s", $_GET["id"]);
            $queryObiettivo->execute();
            $idObiettivo = $queryObiettivo->get_result();
            if ($idObiettivo->num_rows != 0) {
                //Può essere null se non c'è un obiettivo associato all'utente
//                $arrayObiettivo = array();
//                while ($riga = $idObiettivo->fetch_assoc()) {
//                    $arrayObiettivo[] = $riga;
//                }
                $risultato = $idObiettivo->fetch_assoc();
                http_response_code(200);
                echo json_encode(array("stato" => "ok", "idCategoria" => $risultato["IDCategoria"], "parametro" => $risultato["parametro"]));
                exit;
            } else {
                http_response_code(401);
                echo json_encode(array("stato" => "errore"));
            }
            $queryObiettivo->close();
            exit;
        } else {
            $queryDispositivo->close();
            http_response_code(401);
            echo json_encode(array("stato" => "errore"));
            exit;
        }
    }
}