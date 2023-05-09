<?php
require_once("/php/private/model/db/sessione.php");
require_once("/php/private/model/db/dbconnessione.php");
session_start();

// Server-side validation and database handling
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  // Retrieve form data
  $username = $_POST['username'];
  $password = $_POST['password'];
  $confirm_password = $_POST['confirm_password'];
  $height = $_POST['height'];
  $weight = $_POST['weight'];
  $dob = $_POST['dob'];
  $gender = $_POST['gender'];

  // Server-side validation
  if (strlen($password) < 6 || !preg_match('/[A-Z]/', $password)) {
    $_SESSION['alert'] = 'Password must be at least 6 characters long and contain an uppercase letter.';
    header("Location: register.php");
    exit();
  } elseif ($password !== $confirm_password) {
    $_SESSION['alert'] = 'Passwords do not match.';
    header("Location: register.php");
    exit();
  } elseif (!in_array($gender, ['male', 'female'])) {
    $_SESSION['alert'] = 'Please select a valid gender.';
    header("Location: register.php");
    exit();
  }

  // Database query and exception handling
  try {
    //TODO: Consentire solo username univoci
    //TODO: Aggiornare tabella e inserire tutti i campi
    $query = $database->prepare("INSERT INTO utente(username, passwordhash,peso,altezza,dataDiNascita,sesso) VALUES (?,?,?,?,?,?)");
    $passhash = password_hash($_POST["password"], PASSWORD_BCRYPT);
    $query->bind_param("ssssss",$_POST["username"], $passhash,$_POST["weigth"],$_POST["heigth"],$_POST["dob"],$_POST["gender"]);
    $query->execute();
    $query->close();

    // Redirect to login page on success
    header("Location: login.php");
    exit();
  } catch (Exception $e) {
    $_SESSION['alert'] = 'An error occurred. Please try again later.';
    header("Location: register.php");
    exit();
  }
} else {
  // Redirect to register page if accessed directly without a POST request
  header("Location: register.php");
  exit();
}
?>
