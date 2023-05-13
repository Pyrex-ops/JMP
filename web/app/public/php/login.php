<?php
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";

function login_error($error)
{
    $_SESSION['login_error_message'] = $error;
    header("Location: /login");
    exit;
}

redirect_to_dashboard_if_logged_in();

if (isset($_POST["username"]) && isset($_POST["password"])) {
    if (isset($database)) {
        $queryHash = $database->prepare("SELECT passwordhash FROM utente WHERE username = ?");
        $queryHash->bind_param("s", $_POST["username"]);
        $queryHash->execute();
        $arrayHash = $queryHash->get_result()->fetch_assoc();
        if (isset($arrayHash["passwordhash"])) {
            if (password_verify($_POST["password"], $arrayHash["passwordhash"])) {
                login($_POST["username"]);
                header("location: /dashboard");
            } else {
                logout();
                login_error("Nome utente o password errati.");
            }
            $queryHash->close();
        } else {
            logout();
            login_error("Nome utente o password errati.");
        }

    } else {
        login_error("Errore interno. Riprovare più tardi.");
    }

} else {
    login_error("Compilare tutti i campi.");
}
?>