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
<html>

<head>
  <title>User Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="/bootstrap.css">
  <style>
    body {
      background-color: #f5f5f5;
    }

    .card {
      margin-bottom: 20px;
    }

    .circle {
      width: 30px;
      height: 30px;
      border-radius: 50%;
      display: inline-block;
      text-align: center;
      line-height: 30px;
      font-weight: bold;
      color: #fff;
    }

    .green {
      background-color: green;
    }

    .gray {
      background-color: gray;
    }

    .graph {
      height: 300px;
    }

    .training-box {
      padding: 10px;
      margin-bottom: 10px;
      border: 1px solid #ccc;
    }

    .goal-reached {
      color: gold;
    }

    .navbar {
      margin-bottom: 20px;
    }

    .username-card {
      width: fit-content;
      margin: 0 auto;
    }

    .first-card {
      margin-bottom: 20px;
    }
  </style>
</head>

<body>
  <nav class="navbar navbar-expand-md navbar-dark bg-primary">
    <div class="container-fluid">
      <a class="navbar-brand" href="#">JMPCorda.com</a>
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
                <input type="text" class="form-control" id="username" name="username" required />
              </div>
              <div class="mb-3">
                <label for="password" class="form-label">Password</label>
                <input type="password" class="form-control" id="password" name="password" required />
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
  <!-- Bootstrap JS -->
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"
    crossorigin="anonymous"></script>
</body>

</html>