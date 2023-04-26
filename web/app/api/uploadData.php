<?php
//Connessione al database
require_once("../db/dbconnessione.php");
//Check se scheda esiste (fare query)
if ($_POST["id"] === "dispositivoGiusto") {
    echo "OK scheda";
}
//Check se dati sono validi
if ($_POST["data"] >= 0) {
    echo "OK dati";
}
?>