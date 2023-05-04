<?php
require_once("../db/dbconnessione.php");
require_once("../db/sessione.php");


if (isset($_POST["username"]) && isset($_POST["password"]) && !isset($_SESSION["auth"])) {
    if (isset($database)) {
        $queryHash = $database->prepare("SELECT passwordhash FROM utente WHERE username = ?");
        $queryHash->bind_param("s", $_POST["username"]);
        $queryHash->execute();
        $arrayHash = $queryHash->get_result()->fetch_assoc();
        if (isset($arrayHash["passwordhash"])) {
            if (password_verify($_POST["password"], $arrayHash["passwordhash"])) {
                $_SESSION["auth"] = true;
                //echo "\nLogin eseguito con successo";
                header("location:../dashboard.php");
            } else {
                $_SESSION["auth"] = false;
                //echo "\nPassword errata";
            }
            $queryHash->close();
        }

    }

}
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Login | ConfigurazioneCorda</title>

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

    <!-- Login form -->
    <div class="container my-5">
      <div class="row justify-content-center">
        <div class="col-md-6 col-lg-4">
          <div class="card">
            <div class="card-body">
              <h3 class="card-title text-center mb-4">Login</h3>
              <form method="post" action="your-url-here">
                <div class="mb-3">
                  <label for="username" class="form-label">Username</label>
                  <input
                    type="text"
                    class="form-control"
                    id="username"
                    name="username"
                    required
                  />
                </div>
                <div class="mb-3">
                  <label for="password" class="form-label">Password</label>
                  <input
                    type="password"
                    class="form-control"
                    id="password"
                    name="password"
                    required
                  />
                </div>
                <div class="text-center">
                  <button type="submit" class="btn btn-primary">Submit</button>
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