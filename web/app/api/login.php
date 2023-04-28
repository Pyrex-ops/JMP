<?php
require_once("../db/dbconnessione.php");
require_once("../db/sessione.php");


if(isset($_POST["username"]) && isset($_POST["password"]) && !$_SESSION["auth"]){
    if (isset($database)) {
        $queryHash = $database->prepare("SELECT passwordhash FROM utente WHERE username = (?)");
        $queryHash->bind_param("s",$_POST["username"]);
        $queryHash->execute();
        $arrayHash = $queryHash->get_result()->fetch_assoc();
        if(password_verify($_POST["password"],$arrayHash["passwordhash"])){
            $_SESSION["auth"] = true;
            echo "\nLogin eseguito con successo";
        }
        else{
            echo "\nPassword errata";
        }
        $queryHash->close();

    }

}
