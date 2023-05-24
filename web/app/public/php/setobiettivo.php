<?php
include_once "/php/private/model/db/dbconnessione.php";
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";

function cambio_obiettivo_error($error)
{
    $_SESSION['cambio_obiettivo_error_message'] = $error;
    header("Location: /allenamenti.php");
    exit;
}
redirect_to_login_if_not_logged_in();
if(isset($_POST["goalType"]) && isset($_POST["goalValue"])){
    global $database;
    $userID = get_id(get_username());
    //ATTENZIONE VVV
    $idObiettivo = 10;
    //ATTENZIONE AAA - Incompleto
    $querySetObiettivo = $database->prepare("UPDATE utente SET IDObiettivo = ? WHERE IDUtente = ?");
    $querySetObiettivo->bind_param("ii",$idObiettivo,$userID);
}