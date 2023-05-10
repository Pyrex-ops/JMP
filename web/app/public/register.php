<?php require_once '/php/private/view/navbar.php'?>


<!DOCTYPE html>
<html>
<head>
  <title>Registrazione</title>
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
  padding: 12px 60px;
  background-color: #198754;
  margin-top: 20px;
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
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <?php echo_navbar() ?>
  <div class="container">
    <h2 class="text-center">Registrazione</h2>
    <div id="error-container"></div>
    <form method="post" action="/php/register.php">
      <div class="form-group">
        <label for="username">Username:</label>
        <input type="text" class="form-control" id="username" name="username" required>
      </div>
      <div class="form-group">
        <label for="password">Password:</label>
        <input type="password" class="form-control" id="password" name="password" required>
      </div>
      <div class="form-group">
        <label for="confirm_password">Reinserisci la password:</label>
        <input type="password" class="form-control" id="confirm_password" name="confirm_password" required>
      </div>
      <div class="form-group">
        <label for="height">Altezza:</label>
        <input type="number" class="form-control" id="height" name="height" required>
      </div>
      <div class="form-group">
        <label for="weight">Peso:</label>
        <input type="number" class="form-control" id="weight" name="weight" required>
      </div>
      <div class="form-group">
        <label for="dob">Data di nascita:</label>
        <input type="date" class="form-control" id="dob" name="dob" required>
      </div> 
      <div class="form-group">
    <label for="gender">Sesso:</label>
    <select class="form-control" id="gender" name="gender" required>
      <option value="" disabled selected>Seleziona il sesso</option>
      <option value="male">Maschio</option>
      <option value="female">Femmina</option>
    </select>
  </div>
      <div class="text-center">
        <button type="submit" class="btn btn-primary button">Registrati</button>
      </div>
    </form>
  </div>

  <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
  <script>
    // Client-side validation
    // Client-side validation
document.querySelector('form').addEventListener('submit', function(event) {
  var password = document.getElementById('password').value;
  var confirm_password = document.getElementById('confirm_password').value;
  var height = document.getElementById('height').value;
  var weight = document.getElementById('weight').value;

  var errorMessages = [];

  if (password.length < 6 || !/[A-Z]/.test(password)) {
    errorMessages.push('La password deve essere lunga almeno 6 caratteri e contenere un carattere maiuscolo.');
  }

  if (password !== confirm_password) {
    errorMessages.push('Le password non corrispondono.');
  }

  if (isNaN(height)) {
    errorMessages.push('Inserisci l'altezza.');
  }

  if (isNaN(weight)) {
    errorMessages.push('Inserisci il peso.');
  }

  var errorContainer = document.getElementById('error-container');
  errorContainer.innerHTML = '';

  if (errorMessages.length > 0) {
    event.preventDefault();
    errorMessages.forEach(function(message) {
      var errorElement = document.createElement('div');
      errorElement.classList.add('error');
      errorElement.textContent = message;
      errorContainer.appendChild(errorElement);
    });
  }
});

  </script>
</body>
</html>
