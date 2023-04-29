<?php
require_once("../db/dbconnessione.php");
require_once("../db/sessione.php");


if (isset($_POST["username"]) && isset($_POST["password"]) && !$_SESSION["auth"]) {
    if (isset($database)) {
        //TODO: indice su username
        $queryHash = $database->prepare("SELECT passwordhash FROM utente WHERE username = ?");
        $queryHash->bind_param("s", $_POST["username"]);
        $queryHash->execute();
        $arrayHash = $queryHash->get_result()->fetch_assoc();
        if (isset($arrayHash["passwordhash"])) {
            if (password_verify($_POST["password"], $arrayHash["passwordhash"])) {
                $_SESSION["auth"] = true;
                $_SESSION["erroreLogin"] = false;
                //echo "\nLogin eseguito con successo";
                header("location:../dashboard.php");
            } else {
                $_SESSION["auth"] = false;
                $_SESSION["erroreLogin"] = true;
                //echo "\nPassword errata";
            }
            $queryHash->close();
        }

    }

}
?>
<!doctype html>
<html lang="it">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/@picocss/pico@1/css/pico.min.css">
    <title>Login</title>
</head>
<body>
<main class="container">
    <h1>Login</h1>
    <form action="" method="post">
        <div class="grid">
            <label for="username">
                Username
                <input type="text" id="username" name="username" placeholder="Username" required>
            </label>
            <label for="password">
                Password
                <input type="password" id="password" name="password" placeholder="Password" required>
            </label>
        </div>
        <button type="submit">Login</button>
        <?php
        if (isset($_SESSION["auth"])) {
            if (isset($_SESSION["erroreLogin"]) && $_SESSION["erroreLogin"]) {
                echo "Errore";
            }
        }
        ?>
    </form>
</main>
</body>
</html>
