<?php

include_once "/php/private/model/db/dbconnessione.php";
include_once "/php/private/model/auth/sessione.php";

function check_login(): bool
{
    return $_SESSION["auth"] == true;
}

function login($username): void
{
    $_SESSION["auth"] = true;
    $_SESSION["username"] = $username;
}

function logout(): void
{
    $_SESSION["auth"] = false;
}

function get_username()
{
    return $_SESSION["username"];
}

function echo_username(): void
{
    echo $_SESSION["username"];
}

function get_profile_picture(): string
{
    return "https://api.multiavatar.com/" . get_username() . ".png";
}

function echo_profile_picture(): void
{
    echo get_profile_picture();
}

function redirect_to_dashboard_if_logged_in(): void
{
    if (check_login()) {
        header("location: /dashboard");
        exit;
    }
}

function redirect_to_login_if_not_logged_in(): void
{
    if (!check_login()) {
        header("location: /login");
        exit;
    }
}