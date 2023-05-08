<?php

include_once "/php/private/model/db/dbconnessione.php";
include_once "/php/private/model/db/sessione.php";

function check_login() {
    return isset($_SESSION["username"]);
}

?>