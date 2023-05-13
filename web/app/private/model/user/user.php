<?php

include_once "/php/private/model/db/dbconnessione.php";


function does_user_exist($username) {
    global $database;
    $query = $database->prepare("SELECT IDUtente FROM utente WHERE username = ?");
    $query->bind_param("s",$username);
    $query->execute();
    $result = $query->get_result();
    return $result->num_rows != 0;
}

function add_user($username,$password,$weight) {
    global $database;
    $query = $database->prepare("INSERT INTO utente(username, passwordhash,peso) VALUES (?,?,?)");
    $passhash = password_hash($password, PASSWORD_BCRYPT);
    $query->bind_param("ssi",$username, $passhash,$weight);
    $query->execute();
    $query->close();
}

function get_id($username) {
    global $database;
    $query = $database->prepare("SELECT IDUtente FROM utente WHERE username = ?");
    $query->bind_param("s",$username);
    $query->execute();
    $result = $query->get_result();
    return $result->fetch_row()[0];
}

?>