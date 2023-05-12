<?php require_once "/php/private/model/auth/sessione.php";
require_once "/php/private/view/navbar.php";
include_once "/php/private/model/auth/auth.php";
redirect_to_dashboard_if_logged_in(); ?>

<!DOCTYPE html>
<html lang="it">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Registration Form</title>
  <link rel="stylesheet" href="/style/bootstrap.css">
  <link rel="stylesheet" href="/style/jmpit.css">
</head>

<body>
  <?php echo_navbar("registrazione") ?>

  <div class="container container-login">
    <h1 class="text-center"> Registrazione </h1>
    <hr />
    <?php
    if (isset($_SESSION['error_message'])) {
      $error = $_SESSION['error_message'];
      unset($_SESSION['error_message']);
      echo '<div class="alert alert-danger">' . $error . '</div>';
    }
    ?>
    <form method="POST" action="php/registrazione.php">
      <div class="form-group">
        <label for="username">Username</label>
        <input type="text" class="form-control" id="username" name="username" required>
      </div>
      <div class="form-group">
        <label for="password">Password</label>
        <input type="password" class="form-control" id="password" name="password" required>
        <small class="text-muted">La password deve essere lunga 6 caratteri e contenere una lettera maiuscola.</small>
      </div>
      <div class="form-group">
        <label for="weight">Peso (kg)</label>
        <input type="number" class="form-control" id="weight" name="weight" required>
      </div>
      <button type="submit" class="btn button btn-primary">Registrati</button>
    </form>
  </div>

  <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
  <script>
    $(document).ready(function () {
      $('#password').keyup(function () {
        var password = $(this).val();
        var uppercaseRegex = /[A-Z]/;
        var isValid = password.length >= 6 && uppercaseRegex.test(password);
        if (isValid) {
          $(this).removeClass('is-invalid').addClass('is-valid');
        } else {
          $(this).removeClass('is-valid').addClass('is-invalid');
        }
      });
    });
  </script>
</body>

</html>