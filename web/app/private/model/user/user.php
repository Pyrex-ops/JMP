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

function add_user($username,$password,$weight,$height,$dob,$gender) {
    global $database;
    $query = $database->prepare("INSERT INTO utente(username, passwordhash,peso,altezza,dataDiNascita,sesso) VALUES (?,?,?,?,?,?)");
    $passhash = password_hash($password, PASSWORD_BCRYPT);
    $query->bind_param("ssiiss",$username, $passhash,$weight,$height,$dob,$gender);
    $query->execute();
    $query->close();
}

?>