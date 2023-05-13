<?php
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";

function cambio_password_error($error)
{
    $_SESSION['cambio_password_error_message'] = $error;
    header("Location: /impostazioni.php");
    exit;
}


redirect_to_login_if_not_logged_in();

if (isset($_POST["current_password"]) && isset($_POST["new_password"]) && isset($_POST["confirm_password"])) {

    if ($_POST["new_password"] === $_POST["confirm_password"]) {
        $password = $_POST["new_password"];
        if (strlen($password) <= 6) {
            cambio_password_error("La nuova password deve essere più lunga di 6 caratteri.");
        } elseif (!preg_match('/[A-Z]/', $password)) {
            cambio_password_error("La nuova password deve contenere un carattere maiuscolo.");
        }
        $queryHash = $database->prepare("SELECT passwordhash FROM utente WHERE username = ?");
        $username = get_username();
        $queryHash->bind_param("s", $username);
        $queryHash->execute();
        $arrayHash = $queryHash->get_result()->fetch_assoc();
        if (password_verify($_POST["current_password"], $arrayHash["passwordhash"])) {
            try {
                $query = $database->prepare("UPDATE utente SET passwordhash = ? WHERE username = ?");
                $passhash = password_hash($password, PASSWORD_BCRYPT);
                $query->bind_param("ss", $passhash, $username);
                $query->execute();
                $query->close();
                $_SESSION['cambiata_password'] = true;
                header("Location: /impostazioni.php");
                exit;
            } catch (error $error) {
                cambio_password_error("Errore nel cambio della password. Riprovare più tardi.");
            }
        } else {
            cambio_password_error("Password corrente errata. Riprovare.");
        }
    } else {
        cambio_password_error("Le password non corrispondono.");
    }
} else {
    cambio_password_error("Compilare tutti i campi.");
}
?>