<?php require_once "/php/private/model/auth/sessione.php";
require_once "/php/private/view/navbar.php";
include_once "/php/private/model/auth/auth.php";
redirect_to_dashboard_if_logged_in(); ?>

<!DOCTYPE html>
<html lang="it">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Login Page</title>
  <!-- Bootstrap CSS -->
  <link rel="stylesheet" href="/style/bootstrap.css">
  <link rel="stylesheet" href="/style/jmpit.css">
</head>

<body>
  <?php echo_navbar("login") ?>
  <div class="container container-login">
    <h1 class="text-center"> Login </h1>
    <hr />
    <?php
    // Check if login error is set
    if (isset($_SESSION["login_error_message"])) {
      // Display error message in a Bootstrap alert
      echo '<div class="alert alert-danger" role="alert">' . $_SESSION["login_error_message"] . '</div>';
      // Unset the login error variable
      unset($_SESSION["login_error_message"]);
    }
    ?>
    <form method="POST" action="php/login.php">
      <div class="mb-3 form-group">
        <label for="username" class="form-label">Username</label>
        <input type="text" class="form-control" id="username" name="username" required>
      </div>
      <div class="mb-3 form-group">
        <label for="password" class="form-label">Password</label>
        <input type="password" class="form-control" id="password" name="password" required>
      </div>
      <button type="submit" class="btn button btn-primary">Login</button>
    </form>
    <p class="mt-5 text-center">Non sei registrato? Registrati cliccando <a href="registrazione">qui</a></p>
  </div>

  <!-- Bootstrap JS -->
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
</body>

</html>