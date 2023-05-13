<?php require_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/auth/auth.php";

function has_registered_device()
{
    global $database;
    $query = $database->prepare("SELECT IDDispositivo FROM dispositivo JOIN utente on dispositivo.IDUtente = utente.IDUtente WHERE username = ?");
    $username = get_username();
    $query->bind_param("s", $username);
    $query->execute();
    $result = $query->get_result();
    return $result->num_rows != 0;
}

function get_registered_device()
{
    global $database;
    $query = $database->prepare("SELECT IDDispositivo FROM dispositivo JOIN utente on dispositivo.IDUtente = utente.IDUtente WHERE username = ?");
    $username = get_username();
    $query->bind_param("s", $username);
    $query->execute();
    $result = $query->get_result();
    return $result->fetch_row()[0];
}

function unregister_device()
{
    global $database;
    $query = $database->prepare("DELETE FROM dispositivo WHERE IDDispositivo = ?");
    $IDCorda = get_registered_device();
    $query->bind_param("s", $IDCorda);
    $query->execute();
}

function add_device($IDCOrda)
{
    global $database;
    $query = $database->prepare("INSERT INTO dispositivo(IDDispositivo, IDUtente) VALUES (?,?)");
    $IDUtente = get_id(get_username());
    $query->bind_param("si", $IDCOrda, $IDUtente);
    $query->execute();
    $query->close();
}

?>