<?php
require_once("../db/dbconnessione.php");
//Registrazione
/**
 * Username: stringa
 * Password: stringa
 * TODO: Check con query
 */
if ($_POST["username"] != null && strlen($_POST["username"]) > 3) {
    echo "usernameOK";
}
if ($_POST["password"] != null && strlen($_POST["password"]) > 3) {
    echo "passwordOK";
}
?>