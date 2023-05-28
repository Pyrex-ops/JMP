<?php
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";

/*
 * Funzione per mostrare il messaggio di errore
 * sorto durante la modifica delle impostazioni
 * */
function modifica_impostazioni_error($error): void
{
    $_SESSION['modifica_impostazioni_error_message'] = $error;
    header("Location: /impostazioni.php");
    exit;
}


redirect_to_login_if_not_logged_in();

if (isset($_POST["peso"]) && isset($database)) {
    $peso = $_POST["peso"];
    if ($peso <= 0) {
        modifica_impostazioni_error("Il peso deve essere maggiore di zero.");
    }
    if(isset($_POST["consenso_classifica"]) && $_POST["consenso_classifica"] === "on") {
        $consensoClassifica = true;
    }
    else {
        $consensoClassifica = false;   
    }
    $username = get_username();
    try {
        $query = $database->prepare("UPDATE utente SET peso = ?,partecipazioneClassifica = ? WHERE username = ?");
        $query->bind_param("iis", $peso, $consensoClassifica, $username);
        $query->execute();
        $query->close();
        $_SESSION['cambiate_impostazioni'] = true;
        header("Location: /impostazioni.php");
        exit;
    } catch (error $error) {
        modifica_impostazioni_error("Errore nel cambio del peso. Riprovare più tardi.");
    }
} else {
    modifica_impostazioni_error("Compilare tutti i campi.");
}
?>