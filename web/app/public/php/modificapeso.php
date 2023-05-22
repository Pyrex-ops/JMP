<?php
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";

function cambio_peso_error($error): void
{
    $_SESSION['cambio_peso_error_message'] = $error;
    header("Location: /impostazioni.php");
    exit;
}


redirect_to_login_if_not_logged_in();

if (isset($_POST["current_peso"]) && isset($_POST["nuovo_peso"]) && isset($database)) {
    $peso = $_POST["nuovo_peso"];
    if ($peso <= 0) {
        cambio_peso_error("Il peso deve essere maggiore di zero.");
        $queryPeso = $database->prepare("SELECT peso FROM utente WHERE username = ?");
        $username = get_username();
        $queryPeso->bind_param("s", $username);
        $queryPeso->execute();
        $arrayPeso = $queryPeso->get_result()->fetch_assoc();
        try {
            $query = $database->prepare("UPDATE utente SET peso = ? WHERE username = ?");
            $query->bind_param("ss", $peso, $username);
            $query->execute();
            $query->close();
            $_SESSION['cambiato_peso'] = true;
            header("Location: /impostazioni.php");
            exit;
        } catch (error $error) {
            cambio_peso_error("Errore nel cambio del peso. Riprovare più tardi.");
        }
    } else {
        cambio_peso_error("Compilare tutti i campi.");
    }
}
?>
