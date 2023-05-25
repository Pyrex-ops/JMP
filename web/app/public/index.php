<?php require_once "/php/private/model/auth/sessione.php";
require_once "/php/private/view/navbar.php";
include_once "/php/private/model/auth/auth.php";
include_once "/php/private/model/user/user.php";
redirect_to_dashboard_if_logged_in() ?>

<!DOCTYPE html>
<html lang="it">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>JMPit</title>
  <!-- Bootstrap CSS -->
  <link rel="stylesheet" href="/style/bootstrap.css">
    <link rel="stylesheet" href="/style/jmpit.css">
  <style>
    body {
      background-color: bg-light;
      color: black;
    }

    .logo {
      height: 50px;
      margin-top: 10px;
    }

    .center {
      text-align: center;
      font-size: 1.7rem;
    }

    .register-button {

      margin-top: 100px;
      display: block;
      margin: 0 auto;
    }

    .vertical-center {
      min-height: 80vh;
      display: flex;
      align-items: center;
      justify-content: center;
    }

    .text-lg {
      font-size: 3.5rem;
    }

    .rainbow-gradient {
      background: linear-gradient(135deg,#00FF00,#198820,#198754);
      background-clip: text;
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
    }
  </style>
</head>

<body>
  <!-- Navbar -->
  <?php echo_navbar("dashboard") ?>

  <!-- Main Content -->
  <div class="container vertical-center" syle="margin-left:20px;margin-right:20px;">
    <div class="row justify-content-center">
      <div class="col-md-6">
        <h1 class="center text-lg">
          Mantieniti in forma con <span class="rainbow-gradient">JMPit</span>
        </h1>
        <p class="center">Scopri i benefici del fitness con la corda per saltare e raggiungi i tuoi obiettivi di fitness!
        </p>
        <a href="/registrazione" class="btn btn-primary btn-lg register-button" style="margin-top:40px">Registrati</a>
        <a href="/login" class="btn btn-primary btn-lg register-button" style="margin-top:20px">Login</a>
      </div>
    </div>
  </div>

  <!-- Bootstrap JS -->
  <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
</body>

</html>