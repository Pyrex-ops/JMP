<?php
    include_once "/php/private/model/db/sessione.php";
    include_once "/php/private/model/user/user.php";

    function registration_error($error) {
      $_SESSION['error_message'] = $error;
      header("Location: /register.php");
      exit;
    }

    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        $username = $_POST["username"];
        if(strlen($username)==0) {
          registration_error("Inserisci l'username.");
        }
        $password = $_POST["password"];
        if(strlen($password)==0) {
          registration_error("Inserisci la password.");
        }
        $height = $_POST["height"];
        if(strlen($height)==0) {
          registration_error("Inserisci l'altezza.");
        }
        $weight = $_POST["weight"];
        if(strlen($weight)==0) {
          registration_error("Inserisci il peso.");
        }
        $dob = $_POST["dob"];
        if(strlen($dob)==0) {
          registration_error("Inserisci la data di nascita.");
        }
        $gender = $_POST["gender"];
        if(strlen($gender)==0) {
          registration_error("Inserisci il sesso.");
        }
        if (strlen($password) <= 6) {
            registration_error("La password deve essere più lunga di 6 caratteri.");
        } elseif (!preg_match('/[A-Z]/', $password)) {
          registration_error("La password deve contenere un carattere maiuscolo.");
        }

        if(does_user_exist($username)) {
          registration_error("Un utente con questo username è già registrato.");
        }

        try {
          add_user($_POST["username"],$_POST["password"],$_POST["weight"],$_POST["height"],$_POST["dob"],$_POST["gender"]);
          header("Location: /login.php");
        }
        catch(exception $exception) {
          registration_error("Dati non validi. Riprovare.");
        }
        exit;
    } else {
      registration_error("errore generico");
    }
?>
