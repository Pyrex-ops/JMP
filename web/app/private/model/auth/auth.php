<?php

include_once "/php/private/model/db/dbconnessione.php";
include_once "/php/private/model/auth/sessione.php";

/*
 * Funzione per controllare se l'utente è autenticato
 * */
function check_login(): bool
{
    return $_SESSION["auth"] == true;
}
/*
 * Funzione per salvare lo stato di login avvenuto con successo
 * */
function login($username): void
{
    $_SESSION["auth"] = true;
    $_SESSION["username"] = $username;
}

/*
 * Funzione per invalidare la sessione
 * */
function logout(): void
{
    $_SESSION["auth"] = false;
}

/*
 * Funzione per ottenere il nome utente
 * */
function get_username()
{
    return $_SESSION["username"];
}

/*
 * Funzione per stampare il nome utente
 * */
function echo_username(): void
{
    echo $_SESSION["username"];
}

/*
 * Funzione per ottenere l'immagine del profilo
 * */
function get_profile_picture(): string
{
    return "https://api.multiavatar.com/" . get_username() . ".png";
}

/*
 * Funzione per stampare l'url dell'immagine del profilo
 * */
function echo_profile_picture(): void
{
    echo get_profile_picture();
}

/*
 * Funzione per reindirizzare l'utente alla dashboard se già autenticato
 * */
function redirect_to_dashboard_if_logged_in(): void
{
    if (check_login()) {
        header("location: /dashboard");
        exit;
    }
}

/*
 * Funzione per reindirizzare l'utente alla pagina di login
 * se non autenticato
 * */
function redirect_to_login_if_not_logged_in(): void
{
    if (!check_login()) {
        header("location: /login");
        exit;
    }
}