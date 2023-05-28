<?php require_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/auth/auth.php";

/*
 * Funzione per controllare se l'utente ha un dispositivo associato
 * */
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

/*
 * Funzione per ottenere il dispositivo associato
 * */
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

/*
 * Funzione per dissociare il dispositivo dall'account
 * */
function unregister_device()
{
    global $database;
    $query = $database->prepare("DELETE FROM dispositivo WHERE IDDispositivo = ?");
    $IDCorda = get_registered_device();
    $query->bind_param("s", $IDCorda);
    $query->execute();
}

/*
 * Funzione per eseguire l'associazione di un dispositivo all'account
 * */
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