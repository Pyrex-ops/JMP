<?php
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";

if (check_login()) {
    logout();
}
header("location: /");
exit;
?>