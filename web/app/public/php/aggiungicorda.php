<?php
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";
include_once "/php/private/model/dispositivo/dispositivo.php";

function aggiunta_corda_error($error)
{
  $_SESSION['aggiunta_corda_error_message'] = $error;
  header("Location: /impostazioni.php");
  exit;
}

function isValidMACAddress($string)
{
  $pattern = '/^([A-F0-9]{2}:){5}[A-F0-9]{2}$/';
  return preg_match($pattern, $string) === 1;
}


redirect_to_login_if_not_logged_in();

if (isset($_POST["IDCorda"])) {
  $IDCorda = $_POST["IDCorda"];

  if (isValidMACAddress($IDCorda)) {
    try {
      add_device($_POST["IDCorda"]);
      $_SESSION["aggiunta_nuova_corda"] = true;
      header("Location: /impostazioni.php");
      exit;
    } catch (exception $exception) {
      aggiunta_corda_error("Impossibile aggiungere la corda. Riprovare più tardi.");
    }
  } else {
    aggiunta_corda_error("Il codice della corda non è valido. Controllarlo e riprovare.");
  }

} else {
  aggiunta_corda_error("Impossibile aggiungere la corda. Riprovare più tardi.");
}
?>