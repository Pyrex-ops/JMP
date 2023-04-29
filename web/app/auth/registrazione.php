<?php
require_once("../db/sessione.php");
require_once("../db/dbconnessione.php");
//Registrazione
/**
 * Username: stringa
 * Password: stringa
 * Email: stringa
 * peso: intero
 * datanascita: data (gg/mm/aaaa)
 * sesso: stringa
 */
if (isset($_POST["username"]) && isset($_POST["password"]) && isset($_POST["email"]) && isset($_POST["peso"]) && isset($_POST["datanascita"]) && isset($_POST["sesso"])) {
    $_SESSION["erroreRegistrazione"] = true;
    if (isset($database)) {
        //TODO: Consentire solo username univoci
        //TODO: Aggiornare tabella e inserire tutti i campi
        $query = $database->prepare("INSERT INTO utente(username, passwordhash) VALUES (?,?)");
        $passhash = password_hash($_POST["password"], PASSWORD_BCRYPT);
        $query->bind_param("ss", $_POST["username"], $passhash);
        $query->execute();
        $query->close();
        $_SESSION["erroreRegistrazione"] = false; //Tutto ok, se falso mostriamo errore all'utente
        //header('location:"../registrazione.php"');
    }
}
?>
<!doctype html>
<html lang="it">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/@picocss/pico@1/css/pico.min.css">
    <title>Registrazione</title>
</head>
<body>
<main class="container">
    <h1>Registrazione</h1>
    <form action="" method="post">
        <div class="grid">
            <label for="username">
                Username
                <input type="text" id="username" name="username" placeholder="Username" required>
                <small>Verrà richiesto per il login</small>
            </label>
            <label for="password">
                Password
                <input type="password" id="password" name="password" placeholder="Password" required>
                <small>Raccomandazione: Scegli una password forte!</small>
            </label>
        </div>
        <label for="email">
            Indirizzo Email
            <input type="email" id="email" name="email" placeholder="Indirizzo Email" required>
            <small>Non ti invieremo spam. Promesso.</small>
        </label>
        <div class="grid">
            <label for="peso">
                <em data-tooltip="Per il calcolo delle calorie">Peso</em>
                <input type="text" id="peso" name="peso" placeholder="Peso" required>
            </label>
            <label for="datanascita">
                <em data-tooltip="Per il calcolo delle calorie">Data di nascita</em>
                <input type="date" id="datanascita" name="datanascita" placeholder="Data di nascita" required>
            </label>
            <label for="sesso">
                <em data-tooltip="Per il calcolo delle calorie">Sesso anagrafico</em>
                <select id="sesso" name="sesso" required>
                    <option value="" selected>Seleziona</option>
                    <option>M</option>
                    <option>F</option>
                </select>
            </label>
        </div>
        <button type="submit">Invia</button>
    </form>
    <?php
    if (isset($_SESSION["erroreRegistrazione"])) {
        if ($_SESSION["erroreRegistrazione"]) {
            echo "Errore";
        }
    }
    ?>
</main>
</body>
</html>