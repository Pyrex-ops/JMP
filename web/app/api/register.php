<?php
require_once("../db/dbconnessione.php");
require_once("../db/sessione.php");
//Registrazione
/**
 * Username: stringa
 * Password: stringa
 * TODO: Aggiungere tutti gli altri campi
 */
if (isset($_POST["username"]) && isset($_POST["password"]) && !$_SESSION["auth"]) {
    if (isset($database)) {
        $query = $database->prepare("INSERT INTO utente(username, passwordhash) VALUES (?,?)");
        $passhash = password_hash($_POST["password"], PASSWORD_BCRYPT);
        $query->bind_param("ss", $_POST["username"], $passhash);
        $query->execute();
        $query->close();
    }
}
