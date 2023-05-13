<?php
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";
include_once "/php/private/model/dispositivo/dispositivo.php";

function rimozione_corda_error($error)
{
    $_SESSION['rimozione_corda_error_message'] = $error;
    header("Location: /impostazioni.php");
    exit;
}

redirect_to_login_if_not_logged_in();
  try {
    unregister_device();
    header("Location: /impostazioni.php");
    exit;
  }
  catch(error $error) {
    rimozione_corda_error("Errore nella rimozione della corda. Riprovare più tardi.");
  }
?>
