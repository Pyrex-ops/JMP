<?php
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";

/*
 * Funzione per mostrare il messaggio di errore
 * sorto durante la registrazione
 * */
function registration_error($error)
{
  $_SESSION['error_message'] = $error;
  header("Location: /registrazione.php");
  exit;
}

redirect_to_dashboard_if_logged_in();

if (isset($_POST["username"]) && isset($_POST["password"]) && isset($_POST["weight"])) {
  $username = $_POST["username"];
  if (strlen($username) == 0) {
    registration_error("Inserisci l'username.");
  }
  $password = $_POST["password"];
  if (strlen($password) == 0) {
    registration_error("Inserisci la password.");
  }
  $weight = $_POST["weight"];
  if (strlen($weight) == 0) {
    registration_error("Inserisci il peso.");
  }
  if (strlen($password) <= 6) {
    registration_error("La password deve essere più lunga di 6 caratteri.");
  } elseif (!preg_match('/[A-Z]/', $password)) {
    registration_error("La password deve contenere un carattere maiuscolo.");
  }
  if ($_POST["weight"] <= 0) {
    registration_error("Il peso deve essere maggiore di zero.");
  }

  if (does_user_exist($username)) {
    registration_error("Un utente con questo username è già registrato.");
  }


  add_user($_POST["username"], $_POST["password"], $_POST["weight"]);
  $_SESSION["login_success_message"] = "Registrazione completata con successo. Ora puoi effettuare il login.";
  header("Location: /login.php");
  exit;
} else {
  registration_error("errore generico");
}
?>