<?php require_once "/php/private/model/db/sessione.php";
require_once "/php/private/view/navbar.php";?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Registration Form</title>
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
    if (isset($_SESSION['error_message'])) {
        $error = $_SESSION['error_message'];
        unset($_SESSION['error_message']);
        echo '<div class="alert alert-danger">' . $error . '</div>';
    }
    ?>
    <form method="POST" action="php/register.php">
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
        <div class="form-group">
            <label for="height">Altezza (cm)</label>
            <input type="number" class="form-control" id="height" name="height" required>
        </div>
        <div class="form-group">
            <label for="dob">Data di nascita</label>
            <input type="date" class="form-control" id="dob" name="dob" required>
        </div>
        <div class="form-group">
            <label for="gender">Sesso</label>
            <select class="form-control" id="gender" name="gender" required>
                <option value="">Select</option>
                <option value="maschio">maschio</option>
                <option value="femmina">femmina</option>
            </select>
        </div>
        <button type="submit" class="btn button btn-primary">Register</button>
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
