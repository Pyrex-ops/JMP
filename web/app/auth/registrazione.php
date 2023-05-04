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

 function myErrorHandler($errno, $errstr, $errfile, $errline)
{
  header('location:"../registrazione.php"'); 
}

set_error_handler('myErrorHandler');

if (isset($_POST["username"]) && isset($_POST["password"]) && isset($_POST["peso"]) && isset($_POST["altezza"]) && isset($_POST["datanascita"]) && isset($_POST["sesso"])) {
    $_SESSION["erroreRegistrazione"] = "Errore generico. Riprova più tardi.";
    echo $_POST["username"];
    try {
      if (isset($database)) {
        //TODO: Consentire solo username univoci
        //TODO: Aggiornare tabella e inserire tutti i campi
        $query = $database->prepare("INSERT INTO utente(username, passwordhash,peso,altezza,dataDiNascita,sesso) VALUES (?,?,?,?,?,?)");
        $passhash = password_hash($_POST["password"], PASSWORD_BCRYPT);
        $query->bind_param("ssssss",$_POST["username"], $passhash,$_POST["peso"],$_POST["altezza"],$_POST["datanascita"],$_POST["sesso"]);
        $query->execute();
        $query->close();
        $_SESSION["erroreRegistrazione"] = false; //Tutto ok, se falso mostriamo errore all'utente
        //header('location:"../registrazione.php"');
    }
    }
    catch(error) {
      header('location:"../registrazione.php"');
    }
}
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Registrazione | ConfigurazioneCorda</title>

    <!-- Bootstrap CSS -->
    <link
      rel="stylesheet"
      href="/bootstrap.css"
      crossorigin="anonymous"
    />
  </head>
  <body class="bg-light d-flex flex-column min-vh-100">
    <!-- Navbar -->
    <nav class="navbar navbar-expand-md navbar-dark bg-primary">
      <div class="container-fluid">
        <a class="navbar-brand" href="#">ConfigurazioneCorda.it</a>
      </div>
    </nav>

    <!-- Register form -->
    <div class="container my-5">
      <div class="row justify-content-center">
        <div class="col-md-6 col-lg-4">
          <div class="card">
            <div class="card-body">
              <h3 class="card-title text-center mb-4">Registrati</h3>

              <?php
                // Start the session

                // Check if the session variable "error" is set
                if (isset($_SESSION['erroreRegistrazione'])) {
                  // Display an alert with the error message
                  echo '<div class="alert alert-danger">' . $_SESSION['erroreRegistrazione'] . '</div>';
                
                  // Unset the session variable "error" to prevent it from being displayed again
                  unset($_SESSION['error']);
                }
                ?>

              <form method="POST" action="">
      <div class="mb-3">
        <label for="username" class="form-label">Username</label>
        <input type="text" class="form-control" id="username" name="username" required>
      </div>
      <div class="mb-3">
        <label for="password" class="form-label">Password</label>
        <input type="password" class="form-control" id="password" name="password" required>
      </div>
      <div class="mb-3">
        <label for="peso" class="form-label">Peso</label>
        <input type="number" class="form-control" id="peso" name="peso" min="0" step="0.01" required>
      </div>
      <div class="mb-3">
        <label for="altezza" class="form-label">Altezza</label>
        <input type="number" class="form-control" id="altezza" name="altezza" min="0" step="0.01" required>
      </div>
      <div class="mb-3">
        <label for="datanascita" class="form-label">Data di nascita</label>
        <input type="date" class="form-control" id="datanascita" name="datanascita" required>
      </div>
      <div class="mb-3">
        <label for="sesso" class="form-label">Sesso</label>
        <div>
          <div class="form-check">
            <input class="form-check-input" type="radio" name="sesso" id="maschio" value="maschio" required>
            <label class="form-check-label" for="maschio">
              Maschio
            </label>
          </div>
          <div class="form-check">
            <input class="form-check-input" type="radio" name="sesso" id="femmina" value="femmina" required>
            <label class="form-check-label" for="femmina">
              Femmina
            </label>
          </div>
      </div>
    </div>
      <div class="d-grid gap-2 col-6 mx-auto">
        <button type="submit" class="btn btn-primary">Invia</button>
      </div>
    </form>
            </div>
          </div>
        </div>
      </div>
    </div>

    <div class="wrapper flex-grow-1"></div>
    <!-- Footer -->
    <footer class="bg-primary mt-auto py-3">
      <div class="container text-center">
        &copy; ConfigurazioneCorda 2023
      </div>
    </footer>

    <!-- Bootstrap JS -->
    <script
      src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"
      crossorigin="anonymous"
    ></script>
  </body>
</html>