<?php
include_once "/php/private/model/auth/sessione.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/auth/auth.php";

if (check_login()) {
    logout();
}
redirect_to_login_if_not_logged_in();

?>