<?php
include_once "/php/private/model/db/dbconnessione.php";
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";

/*
 * Funzione per mostrare l'eventuale errore
 * sorto durante il cambio dell'obiettivo
 * */
function cambio_obiettivo_error($error)
{
    $_SESSION['cambio_obiettivo_error_message'] = $error;
    header("Location: /allenamenti.php");
    exit;
}

redirect_to_login_if_not_logged_in();
if (isset($_POST["goalType"]) && isset($_POST["goalValue"])) {
    global $database;
    $userID = get_id(get_username());
    if (!($_POST["goalType"] === "Nessuno")) {
        $queryIDCategoria = $database->prepare("SELECT categoriaObiettivo.IDCategoria FROM categoriaObiettivo JOIN obiettivo o on categoriaObiettivo.IDCategoria = o.IDCategoria WHERE Descrizione = ? LIMIT 1");
        $queryIDCategoria->bind_param("s", $_POST["goalType"]);
        $queryIDCategoria->execute();
        $queryIDCategoria = $queryIDCategoria->get_result();
        $idCategoria = $queryIDCategoria->fetch_assoc()["IDCategoria"];
        $queryProssimoIDObiettivo = $database->query("SELECT IDObiettivo FROM obiettivo ORDER BY IDObiettivo DESC LIMIT 1;");
        $prossimoIDObiettivo = $queryProssimoIDObiettivo->fetch_assoc()["IDObiettivo"];
        $prossimoIDObiettivo++;
        $queryCreazioneObiettivo = $database->prepare("INSERT INTO obiettivo(IDObiettivo, IDCategoria, parametro) VALUES (?,?,?)");
        $queryCreazioneObiettivo->bind_param("iii", $prossimoIDObiettivo, $idCategoria, $_POST["goalValue"]);
        $queryCreazioneObiettivo->execute();
        $querySetObiettivo = $database->prepare("UPDATE utente SET IDObiettivo = ? WHERE IDUtente = ?");
        $querySetObiettivo->bind_param("ii", $prossimoIDObiettivo, $userID);
        $querySetObiettivo->execute();
    } else {
        $querySetObiettivo = $database->prepare("UPDATE utente SET IDObiettivo = NULL WHERE IDUtente = ?");
        $querySetObiettivo->bind_param("i", $userID);
        $querySetObiettivo->execute();
    }
    $_SESSION['cambiato_obiettivo'] = "Obiettivo impostato con successo!";
    header("Location: /allenamenti.php");
    exit;

} else {
    cambio_obiettivo_error("Errore nella modifica dell'obiettivo. Riprovare.");
}