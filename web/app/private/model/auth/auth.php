<?php

include_once "/php/private/model/db/dbconnessione.php";
include_once "/php/private/model/auth/sessione.php";

function check_login()
{
    return $_SESSION["auth"] == true;
}

function login()
{
    $_SESSION["auth"] = true;
}

function logout()
{
    $_SESSION["auth"] = false;
}

function redirect_to_dashboard_if_logged_in()
{
    if (check_login()) {
        header("location: /dashboard");
        exit;
    }
}

function redirect_to_login_if_not_logged_in()
{
    if (!check_login()) {
        header("location: /login");
        exit;
    }
}

?>