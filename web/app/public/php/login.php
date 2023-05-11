<?php
include_once "/php/private/model/db/sessione.php";
include_once "/php/private/model/user/user.php";

function login_error($error)
{
    $_SESSION['login_error_message'] = $error;
    header("Location: /login.php");
    exit;
}

if (isset($_POST["username"]) && isset($_POST["password"]) && $_SESSION["auth"] == "false") {
    if (isset($database)) {
        $queryHash = $database->prepare("SELECT passwordhash FROM utente WHERE username = ?");
        $queryHash->bind_param("s", $_POST["username"]);
        $queryHash->execute();
        $arrayHash = $queryHash->get_result()->fetch_assoc();
        if (isset($arrayHash["passwordhash"])) {
            if (password_verify($_POST["password"], $arrayHash["passwordhash"])) {
                $_SESSION["auth"] = true;
                header("location: /dashboard.php");
            } else {
                $_SESSION["auth"] = false;
                login_error("Nome utente o password errati.");
            }
            $queryHash->close();
        } else {
            login_error("Nome utente o password errati.");
        }

    } else {
        login_error("Errore interno. Riprovare più tardi.");
    }

} else {
    login_error("Compilare tutti i campi.");
}
?>