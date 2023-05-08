<?php require_once "/php/private/model/db/sessione.php";
require_once "/php/private/view/navbar.php";?>

<!DOCTYPE html>
<html lang="it">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Login Page</title>
  <!-- Bootstrap CSS -->
  <link rel="stylesheet" href="/bootstrap.css">
  <style>
    body {
      background-color: #f8f9fa;
      margin: 0;
    }
    
    .container {
      max-width: 400px;
      width: 100%;
      background-color: #ffffff;
      padding: 20px;
      margin-top: 50px;
      margin-bottom: 50px;
      border-radius: 5px;
      border: 1px solid #ccc;
    }
    
    
    .form-group label {
      font-weight: bold;
      margin-bottom: 20px;
    }
    .form-group {
      margin-top: 20px;
      margin-bottom: 20px;
    }
    .button {
  display: inline-block;
  width: 100%;
  padding: 12px;
  background-color: #198754;
  margin-top: 40px;
  color: #ffffff;
  border-radius: 6px;
  border: none;
  font-size: 16px;
  font-weight: bold;
  text-align: center;
  text-decoration: none;
  cursor: pointer;
  transition: background-color 0.3s ease;
}

.button:hover {
  background-color: #198000;
}

.button:focus {
  outline: none;
}

.button:active {
  transform: translateY(1px);
}

.error {
  background-color: #f8d7da;
  color: #721c24;
  padding: 10px;
  margin-bottom: 10px;
  border: 1px solid #f5c6cb;
  border-radius: 4px;
}
  </style>
</head>

<body>
<?php echo_navbar() ?>
  <div class="container">
        <?php
        // Check if login error is set
        if (isset($_SESSION["login_error"])) {
          // Display error message in a Bootstrap alert
          echo '<div class="alert alert-danger" role="alert">' . $_SESSION["login_error"] . '</div>';
          // Unset the login error variable
          unset($_SESSION["login_error"]);
        }
        ?>
        <form method="POST" action="login.php">
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
        <p class="mt-3">Non sei registrato? Registrati cliccando <a href="register.php">qui</a></p>
      </div>

  <!-- Bootstrap JS -->
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
</body>

</html>
